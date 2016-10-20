/**
*
*	texture atlas script writer.cpp
*
**/


#include"../auden/auden.hpp"
#include"../events/events.hpp"
#include"../game/game.hpp"
#include"../input/input.hpp"
#include"../maths/maths.hpp"
#include"../time/time.hpp"
#include"../types/types.hpp"
#include"../visen/visen.hpp"
#include"../test/test.hpp"
#include"pugixml.hpp"
#include<fstream>
#include<sstream>
#include<boost/filesystem.hpp>
#include<exception>
#include<iostream>
#include<vector>
#include<set>
#include<utility>
#include<sstream>

namespace bfile = boost::filesystem;

bool diagp = false;


class sprawler_t
{
    typedef std::pair<int,int> int_pair_t;
    
    aab::visen::Image image;
    aab::visen::Pixel matchpixel;
    std::set<int_pair_t> found_set;
    aab::visen::FrameDefinition frame;
    aab::visen::Pixel suggested_mask;
    
    public:
    
    static std::ostream & out;
    
    std::vector<aab::visen::FrameDefinition> frames;
    typedef std::vector<aab::visen::FrameDefinition>::iterator FrameItr;
    typedef std::vector<aab::visen::FrameDefinition>::reverse_iterator ReverseFrameItr;
    
    
    explicit sprawler_t(aab::visen::Image imageIn) // throw (std::logic_error&)
    : image(imageIn)
    {
        image->lockPixels();
        
        // find matchpixel
        
        matchpixel = image->readPixel(0,0);
        
        aab::visen::Pixel pixel_10 = image->readPixel(1,0);
        aab::visen::Pixel pixel_01 = image->readPixel(0,1);
        aab::visen::Pixel pixel_11 = image->readPixel(1,1);
        
        if( pixel_10 == matchpixel || pixel_01 == matchpixel || pixel_11 == matchpixel)
        {
            throw std::logic_error ("Potentially invalid Texture Atlas: no well defined top left corner pixel");
        }
        
        if (pixel_10 == pixel_01 || pixel_10 == pixel_11)
        {
            suggested_mask = pixel_10;
        }
        else if (pixel_01 == pixel_11)
        {
            suggested_mask = pixel_01;
        }
        else
        {
            suggested_mask.red = suggested_mask.blue = 255;
            suggested_mask.green = 0;
        }

        image->unlockPixels();
        
        if(diagp)
        out << "Match Pixel is "
            << (int)matchpixel.red << " "
            << (int)matchpixel.green << " "
            << (int)matchpixel.blue << " "
            << std::endl;
    }
    
    void run_sprawl()
    {
        if(diagp) out << "Beginning Sprawl\n";
        image->lockPixels();
        sprawl(0,0);
        image->unlockPixels();
    }
    
    // current x,y defines a just discovered pixel of the right color
    void sprawl (int x, int y)
    {
        using std::make_pair;
        found_set.insert(make_pair(x,y));
        
        if(diagp)
            out << "sprawl(" << x << "," << y << ")\n";
        
        //seek down to find a pixel					
        int down = 0;
        if (seek_down(x,y, down))
        {
            if(diagp)
                out << "\tfound height " << down + 1;
            
            const int checky = y + (++down);
            if (checky < image->getHeight() && matchpixel == image->readPixel(x,checky))
            {
                if(diagp)
                    out << "\tfound corner" << x << "," << checky;
                if (found_set.find(make_pair(x,checky)) == found_set.end() )
                {
                    if(diagp)
                        out << " => new\n";
                    sprawl(x, checky);
                }
            }
            if(diagp)
                out << "\n";
        }
        
        //seek right to find a pixel					
        int right = 0;
        if (seek_right(x, y, right))
        {
            if(diagp)
                out << "\tfound width " << right+1;
            
            // found width of this, now check next pixel for a marker
            const int checkx = x + (++right);
            if (checkx < image->getWidth() && matchpixel == image->readPixel(checkx,y))
            {
                if(diagp)
                    out << "\tfound corner " << checkx << "," << y;
                if (found_set.find(make_pair(checkx,y)) == found_set.end())
                {
                    if(diagp)
                        out << " => new\n";
                    sprawl(checkx, y);
                }
            }
            if(diagp)
                out << "\n";
        }
        
        //out << "adding frame: " << x <<' '<< y <<' '<< right <<' '<< down <<std::endl;
        frame.x = x;
        frame.y = y;
        frame.w = right;
        frame.h = down;
        frames.push_back(frame);
    }
    
    bool seek_right (int x, int y, int&result)
    {
        aab::visen::Pixel * pixel = image->accessPixel(x,y);
        aab::visen::Pixel * end = pixel + image->getWidth() - x;
        
        while(++pixel != end)
        {
            ++result;
            if (*pixel == matchpixel)
            {
                return true;
            }
        }
        
        return false;
    }
    
    bool seek_down (int x, int y, int&result)
    {
        aab::visen::Pixel * pixel = image->accessPixel(x,y);
        aab::visen::Pixel * end = pixel + image->getWidth()*(image->getHeight() - y);
        unsigned int width = image->getWidth();
        
        while(pixel != end)
        {
            pixel += width;
            ++result;
            if (*pixel == matchpixel)
            {
                return true;
            }
        }
        
        return false;
    }
    
    aab::visen::Pixel get_suggested_mask() const { return suggested_mask; }
};
std::ostream & sprawler_t::out = std::cout;		

class FocusPauser
{
	bool focus_lost;

	protected:

		void notifyFocusLost () { focus_lost = true; }
		void notifyFocusGained () { focus_lost = false; }

	public:

	friend class MyWindowFocusGainedHandler;
	friend class MyWindowFocusLostHandler;

	FocusPauser () : focus_lost(false)
	{	// blank //
	}

	bool isFocusLost() const
	{
		return focus_lost;
	}

};

class MyWindowFocusGainedHandler : public aab::events::KeyboardFocusGainedHandler
{
	FocusPauser * focusPauser;

	public:

	explicit MyWindowFocusGainedHandler (FocusPauser * focusPauserIn): focusPauser(focusPauserIn)
	{	// blank //
	}

	void handleEvent (const EventData)
	{
	    if(diagp)
            std::cout << "window focus gained\n";
		focusPauser-> notifyFocusGained();
	}
};

class MyWindowFocusLostHandler : public aab::events::KeyboardFocusLostHandler
{
	FocusPauser * focusPauser;

	public:

	explicit MyWindowFocusLostHandler (FocusPauser * focusPauserIn): focusPauser(focusPauserIn)
	{	// blank //
	}

	void handleEvent (const EventData)
	{
	    if(diagp)
            std::cout << "window focus lost\n";
		focusPauser-> notifyFocusLost();
	}
};

class FocusMethod
{
	FocusPauser * focusPauser;
	aab::events::EventQueue eventQueue;

	public:

	explicit FocusMethod (FocusPauser * focusPauserIn, aab::events::EventQueue eventQueue): focusPauser(focusPauserIn), eventQueue(eventQueue)
	{	// blank //
	}

	void checkFocus()
	{
		while (focusPauser->isFocusLost())
		{
			eventQueue-> poll ();
			this-> run ();
		}
	}

	virtual void run() = 0;

};

class MyFocusMethod : public FocusMethod
{
	aab::visen::Screen screen;

	public:
	MyFocusMethod (FocusPauser * focusPauserIn, aab::visen::Screen screen, aab::events::EventQueue eventQueue):
		FocusMethod (focusPauserIn, eventQueue), screen (screen)
	{	// blank //
	}

	virtual void run ()
	{
		//screen-> clear ();
		aab::time::delay(10);
		//screen-> update ();
	}
};


//bfile::exists(mask_filename)

struct OutputPixelsOp : public aab::visen::PixelWriteXYOperation
{
    static std::ostream&out;
    
    unsigned int count;
    
    OutputPixelsOp()
    {
        count = 0;
    }
    
    void operator()(Pixel* p, const int x, const int y)
    {
        
       // out << "[" << (int)red << ' ' << (int)green << ' ' << (int)blue << ' ' << (int)alpha << "]";
       
       if (p->red == 255 && p->green == 0 && p->blue == 255)
       {
           if(diagp)
            out << "magenta pixel " << x << " " << y << "\n";
       }
       ++count;
    }
};
std::ostream & OutputPixelsOp::out = std::cout;



void render_number (aab::visen::AnimatedTexturePtr numbers, unsigned int number)
{
    aab::visen::VisualTranslator translator;
    
    std::stringstream ss;
    ss << number;
    std::string s(ss.str());

    translator.setPosition(numbers->getEnvelopeWidth()*(0.5-s.length()/2),0);
    translator.push();
    
    translator.setPosition(numbers->getEnvelopeWidth()*5.0/8.0,0);
    
    for(std::string::iterator i = s.begin();i!=s.end();++i)
    {
        numbers->setFrame(*i - '0');
        numbers->render();
        translator.commit();
    }
    
    translator.pop();
    
}



int main (int argc, char ** argv)
{
	using std::cout;
	using std::endl;
	using std::cin;
	
	
	int screen_width = 640;
	int screen_height = 480;

    if(diagp)  
        cout << "beginning main()" << endl;
	
	if (! argc)
	{
        cout << "atlasscripter imagefile\n" << "Provide an image: the first pixel (top left) will be used to find all the atlas frames in the image. A script file defining the atlas frames will be generated as an xml file of the same name." << endl;
	    return 0;
	}
	else if (diagp)
	{
	    if(diagp)
            cout << "Arguments given:\n\t";
	    for (int t = 0; t < argc; ++t)
	    {
	        if(diagp)
                cout << argv[t] << "\n\t";
	    }
	    if(diagp)
            cout << endl;
	}
	
	using std::string;
	
	if (argc < 2)
	{
	    cout << "Insufficient arguments given.\n";
	    cout << "atlasscripter imagefile\n" << "Provide an image: the first pixel (top left) will be used to find all the atlas frames in the image. A script file defining the atlas frames will be generated as an xml file of the same name." << endl;
	    return 0;
	}
	
	string image_filename (argv[1]);
	string numberimage_filename;
    sprawler_t * sprawler = 0;

	try
	{
	    
	    

		using namespace aab::visen;
		using namespace aab::input;
		using namespace aab::time;
		using namespace aab::auden;
		using namespace aab::game;
		using namespace aab::events;

        {
            // need to create a temporary screen just to load images etc
            Screen screen = startScreen (screen_width, screen_height, windowed_mode);
            screen-> setCaption ("Texture Atlas Script Writer");
            
            using aab::visen::Image;
            
            bfile::path image_path(image_filename);
            
            Image image = makeImage(screen, image_filename);
            screen_width = image->getWidth();
            screen_height = image->getHeight();
            
            //cout << "Attempting to operate on image\n";

            sprawler = new sprawler_t(image);
            
            sprawler->run_sprawl();
            
            pugi::xml_document xmldocument;
            
            pugi::xml_node textureinfo = xmldocument.append_child("textureinfo");
            textureinfo.append_attribute("type") = "atlas";
            
            pugi::xml_node mask_node = textureinfo.append_child("mask");
            
            
            std::string maskfilename(image_path.parent_path().string());
            maskfilename += '/';
            maskfilename.append(image_path.stem().string()).append(".mask").append(image_path.extension().string());

            
            if (bfile::exists(maskfilename))
            {
                std::string maskfilename_stemext(image_path.stem().string());
                maskfilename_stemext.append(".mask").append(image_path.extension().string());
                mask_node.append_attribute("filename") = maskfilename_stemext.c_str();
            }
            else
            {
                //IGNORING SUGGESTED MASK FOR NOW
                mask_node.append_attribute("red") = 255;
                mask_node.append_attribute("green") = 0;
                mask_node.append_attribute("blue") = 255;
            }
            
            std::string image_filename_stemext(image_path.stem().string());
            image_filename_stemext.append(image_path.extension().string());
            textureinfo.append_child("image").append_attribute("filename") = image_filename_stemext.c_str(); 
            
            pugi::xml_node frames_node = textureinfo.append_child("frames");
            
            {
                int index = 0;
                for(sprawler_t::ReverseFrameItr itr = sprawler->frames.rbegin(); itr!=sprawler->frames.rend();++itr)
                {
                    if(diagp)
                        cout << "[" << itr->x << " " << itr->y << " " << itr->w << " " << itr->h << "]\n";
                    
                    pugi::xml_node frame_node = frames_node.append_child("frame");
                    frame_node.append_attribute("x") = itr->x;
                    frame_node.append_attribute("y") = itr->y;
                    frame_node.append_attribute("w") = itr->w;
                    frame_node.append_attribute("h") = itr->h;
                    frame_node.append_attribute("n") = index++;
                }
            }
            
            
            
            
            std::string xmlfilename(image_path.parent_path().string());
            xmlfilename += '/';
            xmlfilename.append(image_path.stem().string()).append(".xml");
            numberimage_filename = xmlfilename;
            numberimage_filename.append(".numbers.png");

            if (! xmldocument.save_file(xmlfilename.c_str()))
            {
                throw std::runtime_error ("xml document failed to save");
            }
        }
        
        {
            
            //new screen
            Screen screen = startScreen (screen_width, screen_height, windowed_mode);
            screen-> setCaption ("Texture Atlas Script Writer");
            EventQueue eventQueue = makeEventQueue (screen);
            Dispatcher dispatcher = makeDispatcher ();
            Mouse mouse = makeMouse (screen);
            Keyboard keys = makeKeyboard ();
            //Gamepad pad = makeGamepad (padPorts);
            //EventHandler::Ptr padsHandler (new GamepadsAutoHandler (pad));
            CloseHandler::Ptr closeHandler (new CloseHandler());
            EventHandler::Ptr keyboardHandler (new KeyboardAutoHandler (keys));
            FocusPauser focusPauser;
            EventHandler::Ptr windowFocusGainedHandler (new MyWindowFocusGainedHandler(&focusPauser));
            EventHandler::Ptr windowFocusLostHandler (new MyWindowFocusLostHandler(&focusPauser));
            dispatcher-> addHandler (closeHandler);
            dispatcher-> addHandler (keyboardHandler);
            dispatcher-> addHandler (windowFocusGainedHandler);
            dispatcher-> addHandler (windowFocusLostHandler);
            eventQueue-> addDispatcher (dispatcher);
            MyFocusMethod myFocusMethod (&focusPauser, screen, eventQueue);

            Cap cap (5);
            cap.setMaximumFPS (60);
            cap.setSleepInterval (10);

            screen-> setClearColor (255, 0, 255);
            
            TexturePtr texture = makeTexture(screen,image_filename);
            
            TexturePtr numbers_texture = makeTexture(screen,"numbers.png",0,0,0);
            AnimatedTexturePtr numbers = makeAnimatedTexture(numbers_texture,8,8);
            
            aab::visen::VisualTranslator translater;
            //aab::visen::VisualScaler scaler;
            //scaler.setScale(0.5,0.5);
            
                                   
           // while (! closeHandler-> hasClosed () && ! keys->isHit(key_escape))
            {
                myFocusMethod.checkFocus();

                screen-> clear ();
                
                translater.setPosition(texture->getOutputWidth()/2,texture->getOutputHeight()/2);
                translater.push();
                texture->render();
                translater.pop();

                int index = 0;
                for(sprawler_t::ReverseFrameItr itr = sprawler->frames.rbegin(); itr!=sprawler->frames.rend();++itr)
                {        
                    translater.setPosition(itr->x+itr->w/2, itr->y+itr->h/2);
                    translater.push();
                    //scaler.push();
                    render_number(numbers, index++);
                    //scaler.pop();
                    translater.pop();
                }
   
                screen-> update ();
                
                //while (! keys->isHit(key_escape))
                {
                    //cap.wait ();
                    eventQueue-> wait ();
                    keys-> update ();
                    
                }

                /*
                if (keys-> isHit (key_m))
                {
                    screen-> minimise ();
                }
                */

                
                //cap.wait ();
            }
            
            if (!screen->saveScreenShotPNG(numberimage_filename))
            {
                if (diagp)
                {
                    cout << "failed to save png" << endl;
                }
            }

            if(diagp)
                cout << "ending main loop" << endl;

            delete sprawler;
        
        }
	}
	catch (std::exception &e)
	{
		std::cout << "error occurred:\t" << e.what () << std::endl;
	}

    if(diagp)
    {
        std::cout << "end: press return\t";
        std::cin.get ();
    }


	return 0;
}



