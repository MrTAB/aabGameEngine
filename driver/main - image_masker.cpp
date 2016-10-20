/**
*
*	batch pixel processor.cpp
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
#include<list>
#include<forward_list>
#include<unordered_set>
#include<utility>
#include<sstream>

/*

Interesting Bug: All images are considered invalid when passed to the shortcut
as an argumebnt, but not the the final program.

Turns out: When you pass a list of files to a program directly using Windows
Windows explorer (dragging and dropping into the parents directory), the input
files directory is used as the initial directory. When you do the same with a 
shortcut, by default, the programs directory is used instead, meaning relative
file paths described within any input files mentioning relative paths, are not
resolvable unless compared against their input file. In this case, each .xml
file would have to have the xml path added onto the front of the string.

However, another solution is to delete the "startup" value in the shortcut.
This is problematic if several files are included as input from various sources,
and so the prior solution is better, albiet slower.


*/


namespace bfile = boost::filesystem;

bool diagp = true;

namespace global{
const char * program_description =
"imagemasker\n \
Creates black and white mask for .png images, transforming all pixels matching \
the mask color into black pixels, and outputting all other pixels as white.\
\n\n\
See the file 'imagemasker.config' to change the mask colour. Popular choices\
are black (0,0,0) and magenta (255,0,255).\
\n\n\
Masks are output as .png images in a subfolder made in the source files \
directories. Pre-existing masks will be overwritten. See 'imagemasker.config' \
to change the name of the sub folder into which masks will be put.\
\n\n\
Input can be a combination of image files, Texture Atlas .xml definitions \
(from GoGo-Robot game's Texture Atlas Generator) and exemption files. Images \
and Sprites mentioned in the texture atlas definition will be added to a list \
of images to make masks of. Images listed in an exemption file will then be \
removed from this source list, based on a match of their exact path strings. An\
exemption file is just a list of strings seperated by lines. These will be \
used in order to prevent the overwrite of custom masks. Any .txt files will be \
treated as exemption files. Note: keeping a backup is advised.\n";

}


struct pixel_masking_operation_t : public aab::visen::PixelWriteOperation
{   typedef aab::visen::Pixel Pixel;

    Pixel mask_pixel;
    
    virtual void operator()(Pixel * pixel)
    {
        
        if (*pixel == mask_pixel)
        {
            pixel->red = pixel->green = pixel->blue = 0;
        }
        else
        {
            pixel->red = pixel->green = pixel->blue = 255;
        }

    }
};

void parse_config_file(std::string filename, std::string&mask_subfolder, pixel_masking_operation_t&pixel_masking_operation)
{
    std::ifstream configfile (filename.c_str());
    
    int use_cout = 1;
    int config_version = 0;
    int mask_red;
    int mask_green;
    int mask_blue;
    
    if (configfile)
    {
        std::string variable_name;
        
        configfile >> variable_name;
        configfile >> config_version;
        
        switch (config_version)
        {
            case 0:
            {
                configfile >> variable_name;
                configfile >> use_cout;
                diagp = static_cast<bool>(use_cout);
                if (use_cout)
                {std::cout << "Diagnostic printing enabled\n"; }
                else  
                {std::cout << "Diagnostic printing disabled\n";}
                
                configfile >> variable_name;
                configfile >> mask_red;
                configfile >> variable_name;
                configfile >> mask_green;
                configfile >> variable_name;
                configfile >> mask_blue;
                configfile >> variable_name;
                configfile >> mask_subfolder;
            }
            break;
            default:
            {
                std::string error;
                error.append("mask script has invalid/unsupported version")
                += config_version;
                error += '\n';
                throw std::runtime_error (error.c_str()); 
            }
        }

    }
    else
    {
        std::string error;
        error.append("unable to open mask script ")
        .append(filename).append("\n");
        throw std::runtime_error (error.c_str());  
    }
    
    pixel_masking_operation.mask_pixel.red = mask_red;
    pixel_masking_operation.mask_pixel.green = mask_green;
    pixel_masking_operation.mask_pixel.blue = mask_blue;
    configfile.close();
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
        cout << global::program_description << endl;
	    return 0;
	}
	else if (diagp)
	{
	    cout << "Arguments given:\n\t";
	    for (int t = 0; t < argc; ++t)
	    {
	        cout << argv[t] << "\n\t";
	    }
	    cout << "\n\nCurrent Working directory:\t" << bfile::initial_path().string() << endl;	    
	}
	
	
	

	//string image_filename (argv[1]);
	//string numberimage_filename;

	try
	{
        if (argc < 2)
        {
            std::string error;
            error += " Noy enough arguments to run program.\n\n";
            error += global::program_description;
            throw std::runtime_error (error.c_str());
        }

        using std::string;
		using namespace aab::visen;
		using namespace aab::input;
		using namespace aab::time;
		using namespace aab::auden;
		using namespace aab::game;
		using namespace aab::events;
		using std::stringstream;
		using std::unordered_set;
		using std::forward_list;
		
		string mask_subfolder("mask");
        pixel_masking_operation_t pixel_write_operation;
        pixel_write_operation.mask_pixel.red = 255;
        pixel_write_operation.mask_pixel.green = 0;
        pixel_write_operation.mask_pixel.blue = 255;
        pixel_write_operation.mask_pixel.alpha = 255;
        
        bfile::path program_path(argv[0]);
        std::string global_config_filename (program_path.parent_path().string());
        global_config_filename += "/imagemasker.config";
        parse_config_file(global_config_filename, mask_subfolder, pixel_write_operation);
        
        forward_list<string> image_filenames;
        unordered_set<string> exemption_image_filenames;

        
        
        for (int argn = 1; argn < argc; ++ argn) // each image
        {
            string file_type = bfile::path(argv[argn]).extension().string();
            
            if (file_type == ".xml")
            {
                //parse xml file looking for node SpritePaths and check each child string.
                // add each child string into image_filenames list.
                // each is expected to be an image! No nesting of xml files.
                
                if(diagp)  
                    cout << "Reading xml file\t" << argv[argn] << endl;
                    
                pugi::xml_document document;
                pugi::xml_parse_result result = document.load_file(argv[argn]);
                                

                if (! result)
                {
                    stringstream error;
                    error   << "Error parsing xml document "
                            << argv[argn] << ": attribute " << document.child("node").attribute("attr").value()
                            <<"\nDescription: "<<result.description()
                            <<"\nError offset: "<<result.offset << std::endl;                    
                    
                    throw std::runtime_error (error.str());                    
                }
                
                pugi::xml_node doc_definition = document.child("TextureAtlasDefinition");
                pugi::xml_node sprite_paths = doc_definition.child("SpritePaths");
                
                if (! sprite_paths)
                {
                    std::string errorstr ("No SpritePaths node found in file ");
                    errorstr += argv[argn] += '\n';                    
                    throw std::runtime_error(errorstr);                                 
                }
                
                bfile::path xml_path(argv[argn]);
                string xml_parent_path ( xml_path.parent_path().string());
                xml_parent_path+='/';
                
                for (pugi::xml_node_iterator sprite_path = sprite_paths.begin(); sprite_path != sprite_paths.end(); ++sprite_path)
                {
                    string sprite_full_path(xml_parent_path);
                    sprite_full_path += sprite_path->child_value();
                    image_filenames.push_front(sprite_full_path);
                    
                    if(diagp)  
                        cout << "Added image file name\t" << sprite_full_path << endl;
                        
                }
                
                if(diagp)  
                    cout << "Finished reading xml file." << endl;
            }
            else if (file_type == ".txt")
            {
                if(diagp)  
                    cout << "Reading exemption file\t" << argv[argn] << endl;
                   
                bfile::path exemption_path(argv[argn]);
                string exemption_parent_path ( exemption_path.parent_path().string());
                exemption_parent_path+='/';
                std::ifstream exemption_file (argv[argn]);
                
                std::string file_name;
                while (exemption_file)
                {
                    std::getline(exemption_file, file_name);
                    string sprite_full_path(exemption_parent_path);
                    sprite_full_path += file_name;
                    if(diagp)  
                        cout << "Adding exemption file\t" << sprite_full_path << endl;
                    exemption_image_filenames.insert(sprite_full_path);
                }                

                exemption_file .close();
                if(diagp)  
                    cout << "Finished reading exemption file\t" << argv[argn] << endl;
  
            }
            else if (file_type == ".png" || file_type == ".bmp")
            {                
                image_filenames.push_front(argv[argn]);
                if(diagp)  
                    cout << "Added image file name\t" << argv[argn] << endl;
            }
            else if (file_type == ".config")
            {
                std::string config_filename (argv[argn]);
                parse_config_file(config_filename, mask_subfolder, pixel_write_operation);
            }
            else
            {
                string error;
                error.append("invalid file type\t")
                .append(argv[argn]).append("\n");
                throw std::runtime_error (error.c_str()); 
            }
        }

        {
            if(diagp)  
                cout << "Opening loading screen" << endl;
        

            
            using aab::visen::Image;
            
            if(diagp)  
                cout << "beginning argument loop" << endl;
            
            Screen screen = startScreen (screen_width, screen_height, windowed_mode);
            screen-> setCaption ("Batch Image Masker");
                        
            for (forward_list<string>::iterator
                    image_filename = image_filenames.begin();
                image_filename!=image_filenames.end();
                ++image_filename)
            {
             
                // skip if in exemption list:
                
                /*if(std::find(exemption_image_filenames.begin(),
                             exemption_image_filenames.end(),
                             *image_filename) != exemption_image_filenames.end())
                             */
                if(exemption_image_filenames.count(*image_filename))
                {
                    if(diagp) 
                    { 
                        cout << "Skipping exemption image\t" << *image_filename <<  endl;
                    }
                    continue;
                }
                
                if(diagp) 
                { 
                    cout << "Working on image\t" << *image_filename <<  endl;
                }
                
                if (! bfile::exists(*image_filename))
                {
                    cout << "Invalid image:\t" << *image_filename << "\nMoving onto next image\n";
                }
                else
                {                    
                      
                    bfile::path image_path(*image_filename);
                
                            // need to create a temporary screen just to load images etc
                    
                    Image image;   
                    /*                 
                    {
                        Screen screen = startScreen (screen_width, screen_height, windowed_mode);
                        screen-> setCaption ("Batch Image Masker");
                
                        image = makeImage(screen, image_filename);
                        screen_width = image->getWidth();
                        screen_height = image->getHeight();
                    
                    }
                    */
                    image = makeImage(screen, *image_filename);
                    
                    {
                        //Screen screen =    startScreen (screen_width, screen_height, windowed_mode);
                        //screen-> setCaption ("Batch Image Masker");
                        
                        bfile::path parent_path (image_path.parent_path());
                        parent_path /= mask_subfolder;                        
                        
                        if (! bfile::is_directory(parent_path))
                        {
                            bfile::create_directory(parent_path);
                        }
                        std::string maskfilename(parent_path.string());//image_path.parent_path().string());
                        //maskfilename += "\\mask\\";
                        
                        maskfilename += '\\';
                        
                        maskfilename.append(image_path.stem().string()).append(image_path.extension().string());
                        
                        // modify image
                        
                        if(diagp)  
                            cout << "transforming pixels..." << endl;

                        image->transformPixels(pixel_write_operation);
                        
                        if(diagp)  
                            cout << "pixels transformed" << endl;
                        
                        // create and render texture to screen (todo - change to skip this step and save image directly to file (as PNG)
                        
                        /*TexturePtr texture = makeTexture(screen, image);
                        
                        if(diagp)  
                            cout << "texture made" << endl;
                        
                        screen-> clear ();
                           
                        aab::visen::VisualTranslator translater;             
                        translater.setPosition(texture->getOutputWidth()/2,texture->getOutputHeight()/2);
                        translater.push();
                        texture->render();
                        translater.pop();

                        screen-> update ();
                        
                        if(diagp)  
                            cout << "texture rendered" << endl;
                            */
                            
                        if(diagp)  
                            cout << "attempting to save image to file\t" <<maskfilename<< endl;
                
                        //if (!screen->saveScreenShotPNG(maskfilename))
                        if (!image->savePng(maskfilename))
                        {
                            if (diagp)
                            {
                                cout << "FAILED to save png\t" << maskfilename << endl;
                            }
                        }
                        else if (diagp)
                        {
                            cout << "Saved png\t" << maskfilename << endl;
                        }
                    }
                    
                    
                }
                
                
                // load image
                //make new image copying width and height
                
                //access each pixel and set outputs version accordingly
            }
            
            if(diagp) 
            { 
                cout << "No more images.\n";
            }
                        
 
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



