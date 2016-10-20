/**
*
*	imperative driver.cpp
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
#include<exception>
#include<iostream>





class MyMouseFocusGainedHandler : public aab::events::MouseFocusGainedHandler
{
	public:

	void handleEvent (const EventData)
	{
		std::cout << "Mouse focus gained\n";
	}
};

class MyMouseFocusLostHandler : public aab::events::MouseFocusLostHandler
{
	public:

	void handleEvent (const EventData)
	{
		std::cout << "Mouse focus lost\n";
	}
};

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
	aab::game::SceneNode * sceneGraph;

	public:
	MyFocusMethod (FocusPauser * focusPauserIn, aab::visen::Screen screen, aab::events::EventQueue eventQueue, aab::game::SceneNode*sceneGraph):
		FocusMethod (focusPauserIn, eventQueue), screen (screen), sceneGraph (sceneGraph)
	{	// blank //
	}

	virtual void run ()
	{
		screen-> clear ();
		aab::time::delay(10);
		sceneGraph-> update ();
		//displayList-> render ();
		screen-> update ();
	}
};


class MyMixerFactory : public aab::auden::MixerFactory
{
	public:

	explicit MyMixerFactory ()
	{
		// nothing //
	};

	virtual ~MyMixerFactory () throw ()
	{
	};

	int getFrequency () const
	{
		return 22050;
	}
	Format getFormat () const
	{
		return default_format;
	}
	int getMusicChannelCount () const
	{
		return 2;
	}
	int getSampleSize () const
	{
		return 1024;
	}
	int getSoundChannelCount () const
	{
		return 10;
	}

};


int main ()
{
	using std::cout;
	using std::endl;
	using std::cin;

	cout << "beginning main()" << endl;

	try
	{

		using namespace aab::visen;
		using namespace aab::input;
		using namespace aab::time;
		using namespace aab::auden;
		using namespace aab::game;
		using namespace aab::events;



		Screen screen = startScreen (640, 480, windowed_mode);

		screen-> setCaption ("Driver [Test unit] ^__^ ");

		double x, y, speed = 2.0;
		double x2, y2;

		x = x2 = screen-> getWidth()/2;
		y = y2 = screen-> getHeight()/2;

        //GamepadPorts padPorts = startGamepadPorts (screen);


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
		EventHandler::Ptr mouseFocusGainedHandler (new MyMouseFocusGainedHandler());
		EventHandler::Ptr mouseFocusLostHandler (new MyMouseFocusLostHandler());


		//dispatcher-> addHandler (padsHandler);
		dispatcher-> addHandler (closeHandler);
		dispatcher-> addHandler (keyboardHandler);
		dispatcher-> addHandler (windowFocusGainedHandler);
		dispatcher-> addHandler (windowFocusLostHandler);
		dispatcher-> addHandler (mouseFocusGainedHandler);
		dispatcher-> addHandler (mouseFocusLostHandler);
		//dispatcher-> addHandler (mouseHandler);

		cout << "adding dispatcher to queue" << endl;

		eventQueue-> addDispatcher (dispatcher);



		Cap cap (5);
		cap.setMaximumFPS (60);
		cap.setSleepInterval (10);

		DeltaTime::Ptr delta (new DeltaTime (60));

		//FrameTicker ticker (delta, 0.05, 20, 20);

		Fps fps;

		delta-> setBound (0.5, 3.0);

		screen-> setClearColor (255, 0, 0);



		TexturePtr ironGiantTexture = makeTexture (screen, "../visen/media/iron_giant.PNG");
		TexturePtr puppetTexture = makeTexture (screen, "../visen/media/puppet.PNG", "../visen/media/puppet_mask.PNG");

		TexturePtr darknutTexture	= makeTexture (screen, "../visen/media/darknut.PNG", 255, 0, 255); // 11x4
		FrameTicker::Ptr darknutTickerA (new FrameTicker (delta, delta-> getExpectedFps()/10, 11, 16));
		FrameTicker::Ptr darknutTickerB (new FrameTicker (delta, delta-> getExpectedFps()/8, 3, 5));

		Sprite * darknutA      = new Sprite (darknutTexture, 64, 64);
		Sprite * darknutChildA = new Sprite (darknutTexture, 64, 64);
		Sprite * ironGiant     = new Sprite (ironGiantTexture);
		


		DisplayListNode * displayList = new DisplayListNode();



		SceneNode * sceneGraph = makeSceneNode ();
		ColorNode * colorNode = new ColorNode();

		sceneGraph-> addChild (darknutA);
		darknutA-> addChild (displayList);
		displayList-> addChild (colorNode);
		darknutChildA-> addChild (ironGiant);
		colorNode-> addChild (darknutChildA);

		colorNode-> accessColor ().set (0, 128, 255, 255);

		darknutA-> move (100, 100);
		darknutChildA-> move (100, 200);
		ironGiant-> move (-100, 200);
		ironGiant-> scale (0.5, 0.5);

        /*
		Mixer mixer (screen, MyMixerFactory());

		Music music (mixer, "../auden/media/Lttp_CastleFull.mp3");

		music.play (Music::forever);

		music.setMusicVolume (zero_volume);

		Sound bushSound (mixer, "../auden/media/Lttp_Boing_Bush.wav");
		Sound hitSound (mixer, "../auden/media/Lttp_GhutHit.wav");
		Sound badTones (mixer, "../auden/media/bad_tones.wav");
		*/

		MyFocusMethod myFocusMethod (&focusPauser, screen, eventQueue, sceneGraph);

		double dt;

		cout << "beginning main loop" << endl;

	/* do we need to check if window is avtive etc!? */

		while (! closeHandler-> hasClosed () && ! keys->isHit(key_escape))//keys-> isHeldLongerThan (key_leftshift, key_escape))
		{
			myFocusMethod.checkFocus();

			screen-> clear ();

			dt = delta-> getChange () ;
			
            darknutTickerA->update();
            darknutTickerB->update();
            darknutA->setFrame(darknutTickerA->getFrame());
            darknutChildA->setFrame(darknutTickerB->getFrame());

			//pad-> update ();
			mouse-> update ();
			keys-> update ();


			eventQueue-> poll ();

			darknutA-> setPosition (mouse-> getX (), mouse-> getY ());


			if (keys-> isHit (key_u))
			{
				displayList-> setDisplayListAs (darknutChildA);
			}



			if (keys-> isDown (key_right))
			{
				cout << "[right]";
			}

			if (keys-> isDown (key_left))
			{
				cout << "[left]";
			}


			if (keys-> isDown (key_down))
			{
				cout << "[down]";
			}

			if (keys-> isDown (key_up))
			{
				cout << "[up]";
			}

			if (keys-> isHit (key_s))
			{
				screen-> showCursor ();
			}

			if (keys-> isReleased (key_s))
			{
				screen-> hideCursor ();
			}

			if (keys-> isHit (key_m))
			{
				screen-> minimise ();
			}

			//puppetTexture-> draw		((int)x2 + 200, (int)y2 + 100);


			if (keys-> isDown (key_z))
			{
				darknutA-> rotate (- dt);
			}

			if (keys-> isDown (key_x))
			{
				darknutA-> rotate (dt);
			}

			if (keys-> isDown (key_c))
			{
				darknutA-> scale (0.9, 0.9);
			}

			if (keys-> isDown (key_v))
			{
				darknutA-> scale (1.1, 1.1);
			}

			if (keys-> isDown (key_a))
			{
				darknutChildA-> rotate (- dt);
			}

			if (keys-> isDown (key_s))
			{
				darknutChildA-> rotate (dt);
			}

			if (keys-> isDown (key_d))
			{
				darknutChildA-> scale (0.9, 0.9);
			}

			if (keys-> isDown (key_f))
			{
				darknutChildA-> scale (1.1, 1.1);
			}


			//x2 += dt * speed * pad-> getXAxis ();
			//y2 += dt * speed * pad-> getYAxis ();

			sceneGraph-> update ();
			//displayList-> render ();
			screen-> update ();
			fps.update ();
			cap.wait ();
			delta-> update ();

			//ticker.update ();
			darknutTickerA-> update ();
			darknutTickerB-> update ();


			std::cout << "\t" << fps.getFps() << "\n";

		}

		cout << "ending main loop" << endl;

        clearSprite(darknutA);
        clearSprite(darknutChildA);
        clearSprite(ironGiant);

        delete sceneGraph;
        delete colorNode;
        delete displayList;
		


	}
	catch (std::exception &e)
	{
		std::cout << "error occurred:\t" << e.what () << std::endl;
	}

	std::cout << "end\t";
	std::cin.get ();


	return 0;
}



