/**
*
*	driver.cpp
*
**/


//#include <cstdlib>
#include"../engine/gameengine.hpp"
#include"../geometry/vector.hpp"
#include<exception>
#include<iostream>
//#include<sdl.H>

//Next step : code gamepad subprogram to not crash simply because there is no gamepad:
//It should throw an exception to be caught.
//Then, add in controls for good behaviour around the object.

// Note that ina  final game, each input will have a backup command, but either command may be a key or gamepad or both etc. mixed.
//

namespace icode = aab::input::universal;

class MyGame : public aab::engine::GameEngine
{
	public:

	MyGame () : GameEngine (640,480,aab::visen::windowed_mode)
	{
		// todo //
	}

	void run ()
	{
		using namespace aab::visen;
		using namespace aab::game;
		using namespace aab::time;
		using namespace aab::input;
		using namespace aab::auden;		
		using std::cout;
		using std::endl;
		using std::cin;

		window->setCaption("My Game");


		//Music music (mixer, "../auden/media/Lttp_Sanctuary.ogg");
		//music.play (Music::forever);
		//music.setMusicVolume (128);

		//Sound bushSound (mixer, "../auden/media/Lttp_Boing_Bush.wav");
		//Sound hitSound (mixer, "../auden/media/Lttp_GhutHit.wav");
		//Sound badTones (mixer, "../auden/media/Dash.wav");


        
        
        TexturePtr ironGiantTexture = makeTexture (window, "../visen/media/iron_giant.PNG");
		TexturePtr puppetTexture = makeTexture (window, "../visen/media/puppet.PNG", "../visen/media/puppet_mask.PNG");



		Sprite * darknutA      = loadSprite ("../visen/media/darknut.PNG", Colorf::magenta, 64, 64);
		Sprite * darknutChildA = loadSprite ("../visen/media/darknut.PNG", Colorf::magenta, 64, 64);
		
		FrameTicker::Ptr darknutTickerA (new FrameTicker (deltaTime, deltaTime-> getExpectedFps()/10, 0, 10));
		FrameTicker::Ptr darknutTickerB (new FrameTicker (deltaTime, deltaTime-> getExpectedFps()/8, 0, darknutChildA->getMaximumFrame()));
		
		//darknutTickerA->update();
		//darknutA->setFrame(darknutTickerA->getFrame());
		
		Sprite * ironGiant     = new Sprite (ironGiantTexture);

		DisplayListNode * displayList = new  DisplayListNode();

        //Gamepad gamepad_test = makeGamepad();
        //Gamepad gamepad_test2 = makeGamepad();
        
		SceneNode * sceneGraph = makeSceneNode ();
		ColorNode * colorNode = new ColorNode ();

		sceneGraph-> addChild (darknutA);
		darknutA-> addChild (displayList);
		displayList-> addChild (colorNode);
		darknutChildA-> addChild (ironGiant);
		colorNode-> addChild (darknutChildA);

		colorNode-> accessColor().set(0, 128, 255, 255);

		//darknutA-> move (100, 100);
		darknutChildA-> move (100, 200);
		ironGiant-> move (-100, 200);
		ironGiant-> scale (0.5, 0.5);

		double x, y, speed = 4.0;
		double x2, y2;

		x = x2 = window-> getScaledWidth()/2;
		y = y2 = window-> getScaledHeight()/2;

		Cap cap (5);
		cap.setMaximumFPS (60);
		cap.setMinimumSleepInterval (10);

		window->setClearColor (255, 0, 0);
		
		
		//
		
		/*
		struct gamepad_t
		{
		    SDL_Joystick *joystick;
		    bool opened;
		};
		
		gamepad_t gamepad;
		
		
		
        SDL_JoystickEventState(SDL_ENABLE);
        
        if (SDL_NumJoysticks() >0)
        {
            gamepad.joystick = SDL_JoystickOpen(0);
            gamepad.opened = true;
        }
        else
        {
            gamepad.joystick = 0;
            gamepad.opened = false;
        }
        
        if (gamepad->opened)
        {
            SDL_JoystickClose(SDL_JoystickIndex(gamepad->joystick));
        }
        */
        
		// gamepad details:
		
		std::cout << "Gamepads connected:\t" << input->countGamepads() << std::endl;
		
		for (int t = 0; t  < input->countGamepads();++t)
		{
            std::cout << "Gamepad details:\n"
            <<"id:\t"<< t
            <<"\nname:\t"<< input->getGamepadName(t)
            <<"\naxes:\t"<< input->getGamepadAxesCount(t)
            <<"\nballs:\t"<< input->getGamepadBallCount(t)
            <<"\nhats:\t"<< input->getGamepadHatCount(t) 
            <<"\nbuttons:\t"<< input->getGamepadButtonCount(t) << std::endl;
		}
		
		/*
		std::cout << "Gamepad details:\n"
		<<"id:\t"<< gamepad_test->getId()
		<<"\nname:\t"<< gamepad_test->getName()
		<<"\naxes:\t"<< gamepad_test->getAxesCount()
		<<"\nballs:\t"<< gamepad_test->getBallCount()
		<<"\nhats:\t"<< gamepad_test->getHatCount() 
		<<"\nbuttons:\t"<< gamepad_test->getButtonCount() << std::endl;
		*/
		
		
        enum
        {
            CLOSE_KEY,
            RIGHT_KEY,
            LEFT_KEY,
            DOWN_KEY,
            UP_KEY,
            ACTION_KEY,
            CURSOR_X,
            CURSOR_Y,
            CURSOR_X_CHANGE,
            CURSOR_Y_CHANGE,
            
            TEST_ISDOWN,
            TEST_ISTOGGLED,
            TEST_ISHIT,
            TEST_ISRELEASED,
            TEST_ISHELDLONGERTHAN,
            TEST_ISHELDLONGERTHANA,
            TEST_ISHELDLONGERTHANB,
            TEST_GETREST,
            TEST_GETLASTMODIFIED,
            TEST_HASREAD,
            TEST_HASJUSTMODIFIED
        };

        //todo - add a WASD movement version which returns -1 and 1, same with arrow keys, D-pads and
        //hats?
        
        input->setControl(CLOSE_KEY, icode::key_escape);
        input->setSecondControl(CLOSE_KEY, icode::mouse_button_6);
        
        input->setControl(RIGHT_KEY, icode::gamepad_0_axis_0_right);
        input->setControl(LEFT_KEY, icode::gamepad_0_axis_0_left);
        input->setControl(UP_KEY, icode::gamepad_0_axis_1_up);
        input->setControl(DOWN_KEY, icode::gamepad_0_axis_1_down);
    
        input->setSecondControl(RIGHT_KEY, icode::key_d);
        input->setSecondControl(LEFT_KEY, icode::key_a);
        input->setSecondControl(UP_KEY, icode::key_w);
        input->setSecondControl(DOWN_KEY, icode::key_s);
        
        input->setControl(CURSOR_X, icode::mouse_x);
        input->setControl(CURSOR_Y, icode::mouse_y);
 
        input->setControl(CURSOR_X_CHANGE, icode::mouse_x_change);
        input->setControl(CURSOR_Y_CHANGE, icode::mouse_y_change);
        
        input->setControl(TEST_ISDOWN,icode::key_z);
        input->setControl(TEST_ISTOGGLED,icode::key_x);
        input->setControl(TEST_ISHIT,icode::key_c);
        input->setControl(TEST_ISRELEASED,icode::key_v);
        input->setControl(TEST_ISHELDLONGERTHAN,icode::key_b);
        input->setControl(TEST_ISHELDLONGERTHANA,icode::key_n);
        input->setControl(TEST_ISHELDLONGERTHANB,icode::key_m);
        input->setControl(TEST_GETREST,icode::key_1);
        input->setControl(TEST_GETLASTMODIFIED,icode::key_2);
        input->setControl(TEST_HASREAD,icode::key_3);
        input->setControl(TEST_HASJUSTMODIFIED,icode::key_4);
    
		double dt = 0;
		while (running())
		{		    
			//window-> clear ();
			//gamepad_test-> update ();
			//mouse-> update ();
			//keyboard-> update ();
			//eventQueue-> poll ();
			updateEngine();
			checkForLostFocus();
			
			//input->radialDeadZoneXYAxes(0,3000);//,5000);

			dt = deltaTime-> getChange () ;
			
			//darknutA-> setPosition (mouse-> getX ()-window-> getWidth()/2, mouse-> getY ()-window-> getHeight()/2);
						
			
			//darknutA-> setPosition (input->getValue(CURSOR_X),
            //               input->getValue(CURSOR_Y));
			
			darknutA-> setPosition (x2,y2);


        
            
            //if (keyboard-> isHit (key_escape) || input->getCodeValue (icode::gamepad_button_1))
            if(//input->getCodeValue (icode::key_escape) ||
               //input->getCodeValue (icode::gamepad_button_1) ||
               //input->getCodeValue (universal::gamepadButtonCode(0,0)) ||
               input->getValue (CLOSE_KEY)
               //||input->getCodeValue (icode::mouse_button_6)
               )
            {
                closeGame();
                cout << "close"; 
            }
            
			if (input-> isKeyHit (icode::key_u))
			{
				displayList-> setDisplayListAs (darknutChildA);
			}



			if (input-> getValue (RIGHT_KEY))
			{
				cout << "[right]";
				//if (! bushSound.isPlaying()) bushSound.play();
			}

			if (input-> getValue (LEFT_KEY))
			{
				cout << "[left]";
				//if (! hitSound.isPlaying()) hitSound.play();
			}


			if (input-> getValue (DOWN_KEY))
			{
				cout << "[down]";
				//if (! badTones.isPlaying()) badTones.play();
			}

			if (input-> getValue (UP_KEY))
			{
				cout << "[up]";
			}

			if (input-> isKeyHit (icode::key_s))
			{
				window-> showCursor ();
			}

			if (input-> isKeyReleased (icode::key_s))
			{
				window-> hideCursor ();
			}

			//if (input-> isKeyHit (icode::key_m))
			{
				//window-> minimise ();
			}

			//puppetTexture-> draw		((int)x2 + 200, (int)y2 + 100);


			if (input-> isKeyDown (icode::key_z))
			{
				darknutA-> rotate (- dt);
			}

			if (input-> isKeyDown (icode::key_x))
			{
				darknutA-> rotate (dt);
			}

			if (input-> isKeyDown (icode::key_c))
			{
				darknutA-> scale (0.9, 0.9);
			}

			if (input-> isKeyDown (icode::key_v))
			{
				darknutA-> scale (1.1, 1.1);
			}

			if (input-> isKeyDown (icode::key_a))
			{
				darknutChildA-> rotate (- dt);
			}

			if (input-> isKeyDown (icode::key_s))
			{
				darknutChildA-> rotate (dt);
			}

			if (input-> isKeyDown (icode::key_d))
			{
				darknutChildA-> scale (0.9, 0.9);
			}

			if (input-> isKeyDown (icode::key_f))
			{
				darknutChildA-> scale (1.1, 1.1);
			}
			
			
            if(input-> isDown(TEST_ISDOWN))
            {
                cout << "is down" << endl;
            }
            if(input-> isToggled(TEST_ISTOGGLED))
            {
                cout << "is toggled" << endl;
            }
            if(input-> isHit(TEST_ISHIT))
            {
                cout << "is hit" << endl;
            }
            if(input-> isReleased(TEST_ISRELEASED))
            {
                cout << "is released" << endl;
            }
            if(input-> isHeldLongerThanTime(TEST_ISHELDLONGERTHAN, 2000))
            {
                cout << "is held longer than (time)" << endl;
            }
            if(input-> isHeldLongerThanInput(TEST_ISHELDLONGERTHANA, TEST_ISHELDLONGERTHANB))
            {
                cout << "is held longer than (input)" << endl;
            }
            
            /*
            {
                cout << "rest " << input-> getRest(TEST_GETREST) << endl;
            }
            //if()
            {
                cout << "modified " << input-> getLastModified(TEST_GETLASTMODIFIED) << endl;
            }
            //if()
            {
                cout << "hasRead " << input-> hasRead(TEST_HASREAD) << endl;
            }
            //if()
            {
                cout << "hasJustModified " << input-> hasJustModified(TEST_HASJUSTMODIFIED) << endl;
            }*/
            
            

            /**
			x2 += dt * speed * static_cast<float>(gamepad_test-> getXAxis ())/(gamepad_axis_max);
			y2 += dt * speed * static_cast<float>(gamepad_test-> getYAxis ())/(gamepad_axis_max);
			

			x2 += dt * speed * static_cast<float>(gamepad_test2-> getXAxis ())/(gamepad_axis_max);
			y2 += dt * speed * static_cast<float>(gamepad_test2-> getYAxis ())/(gamepad_axis_max);
			*/
						
			//utility methods
			//IsCodeHit etc
			//test various things
			//shopv
			//segs
			
			//x2 += dt * speed * static_cast<float>(input-> getCodeValue (universal::gamepad_0_axis_0))/(gamepad_axis_max);// universal::gamepadAxisCode(0,0)))/(gamepad_axis_max);
			//y2 += dt * speed * static_cast<float>(input-> getCodeValue (universal::gamepadAxisCode(0,1)))/(gamepad_axis_max);
			
			x2 += dt * speed * static_cast<float>(input-> getHatX(0));
			y2 += dt * speed * static_cast<float>(input-> getHatY(0));
			
			//std::cout << "\naxis 0:" << input-> getCodeValue (universal::gamepad_0_axis_0)
			//<< " axis 1:"<< input-> getCodeValue (universal::gamepad_0_axis_1);
			
			
			for (int t = 0; t < input->getGamepadButtonCount(0);++t)
			{
                if (input->isGamepadButtonDown(0,t))
                {
                    std::cout << " " <<t;
                }
			}
			


			//darknutChildA->getAnimator()-> update();

			sceneGraph-> update ();

			//window-> update ();
			//fps.update();
			cap.wait ();
			//deltaTime-> update ();

			darknutTickerA-> update ();
			darknutTickerB-> update ();
			
            darknutA->setFrame(darknutTickerA->getFrame());
            darknutChildA->setFrame(darknutTickerB->getFrame());

		}
	}

    virtual void focusLostLoop ()
    {
        aab::time::delay(10);
    }
    
    /*
    virtual void gamepadsUnplugged(aab::input::GamepadUnpluggedList unpluggedIds)
    {     
        std::cout << "Gamepads unplugged callback.\n";
        
        using aab::input::GamepadUnpluggedIterator;        
        for(GamepadUnpluggedIterator badPad = unpluggedIds.begin(); badPad != unpluggedIds.end(); ++badPad)
        {
            std::cout << "Gamepad unplugged: " << (*badPad) << "\n";
            if (gamepadPorts->isPortRegistered(*badPad))
            {
                std::cout << "REGISTERED\n.";
            }
        }
    }*/

};

int main ()//(int argc, char** argv)
{
	using std::cout;
	using std::endl;
	using std::cin;

	cout << "beginning" << endl;

	try
	{
		MyGame myGame;

		myGame.run();

	}
	catch(aab::input::NoGamepadsException&nge)
	{
	    std::cout << "error occurred:\t" << nge.what () << std::endl;
	    std::cin.get ();
	}
	catch (std::exception &e)
	{
		std::cout << "error occurred:\t" << e.what () << std::endl;
		std::cin.get ();
	}
	catch(...)
	{
	    std::cout << "Unknown error occurred!" << std::endl;
	    std::cin.get ();
	}
	
	//std::cout << "not died!\t";
	std::cin.get ();


	return 0;
}



