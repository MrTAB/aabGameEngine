
/**
*
*	gameengine.cpp
*
**/

#include"../game/game.hpp"
#include"gameengine.hpp"
namespace aab	{
namespace engine	{
    
    
    /*
    
    About GameEngine:
    
    extend and implement virtuals to define behaviour of game.
    Create an instance and invoke run() to begin the game.
    
    Within your constructor:
        Arguments provided to superclass constructor define the window/fullscreen options.
        These can be individual width, height mode etc, or a visen::ContextDefinition.
        
    Within start():
        load begin game things.
        Run title menu etc - TODO - should title menu be done differently? some games might want to load running stuff after bringing up title menu, or even while the title menu runs for example.
    
    loop():
        loop defines the code which is executed during each loop (i.e. is the inside of the loop).
        loop does not have to be overridden, you can instead implement processInput(), updateLogic() and render()
        However, the option exists for you to replace this rigid form and implement loop as you see fit.
    
    end():
        generally cleanup anything allocated during start.
        
    focusLostStart()
        load anything for displaying when focus is lost. Change any states as required.
    focusLostLoop()
        This is handled by the engine by default but can be overridden. The default behaviour is to sleep for 10ms.
        
    
    uses input::InputController for input. This combines and buffers input values various sources that can then be evaluated with a flag, allowing you to map them universally.
    
    
    
    

    */

/*todo
 Consider adding two exception wrappers in the game engine, to wrap around start() and loop()
 User couldcatch exceptions in loop_catch(), create error messages to display to player, and then resume the game or close it.
 */

GameEngine::GameEngine (int screenWidth, int screenHeight, ScreenMode screenMode, unsigned int expectedFpsIn):
	window(visen::startScreen (screenWidth,screenHeight,screenMode)),
	mixer (window, aab::auden::MixerFactory()), // mixer doesn't actually use window/need it to be complete, just needs to know that it has undergone its constructors body code.
	frameCap(1000/60), // not used
	expectedFps(expectedFpsIn)
{
	sharedConstructorCode ();
}

GameEngine::GameEngine (const visen::ContextDefinition& def, unsigned int expectedFpsIn):
	window(visen::startScreen (def)),
	mixer (window, aab::auden::MixerFactory()), // mixer doesn't actually use window/need it to be complete, just needs to know that it has undergone its constructors body code.
	frameCap(1000/60), // not used
	expectedFps(expectedFpsIn)
{
	sharedConstructorCode ();
}

	
void GameEngine::sharedConstructorCode ()
{
	using namespace aab::visen;
	using namespace aab::input;
	using namespace aab::time;
	using namespace aab::auden;
	using namespace aab::game;
	using namespace aab::events;

	//gamepadPorts = startGamepadPorts (window);
	//gamepadPorts->setUnpluggedCallback(this);
	
	eventQueue = makeEventQueue (window);
	eventDispatcher = makeDispatcher ();
	mouse = makeMouse (window);
	//keyboard = makeKeyboard ();
	input = makeInputController(window);
	clearScreen = true;
	
    ///gamepadsHandler = aab::events::GamepadsAutoHandler::Ptr
    ///                        (new events::GamepadsAutoHandler ());

	///
	//gamepad = makeGamepad ();

	///
	//EventHandler::Ptr
	//GamepadsAutoHandler::Ptr
	//gamepadsHandler2 = GamepadsAutoHandler::Ptr(new GamepadsAutoHandler (gamepad));
	//gamepadsHandler = EventHandler::Ptr(new GamepadsAutoHandler (gamepad));

	closeHandler = CloseHandler::Ptr (new CloseHandler());
	//KeyboardAutoHandler::Ptr 
	///keyboardHandler = KeyboardAutoHandler::Ptr(new KeyboardAutoHandler (keyboard));
	EventHandler::Ptr notifiedKeyboardFocusLostHandler (new NotifiedKeyboardFocusLostHandler(&keyboardFocusMonitor));
	//EventHandler::Ptr notifiedKeyboardFocusLostHandler = NotifiedKeyboardFocusLostHandler::Ptr(new NotifiedKeyboardFocusLostHandler(&keyboardFocusMonitor));
	EventHandler::Ptr notifiedKeyboardFocusGainedHandler (new NotifiedKeyboardFocusGainedHandler(&keyboardFocusMonitor));


    //ICkeyboardHandler = KeyboardAutoHandler::Ptr(new KeyboardAutoHandler (inputController));
	///
	//eventDispatcher-> addHandler (gamepadsHandler2);
	
	eventDispatcher-> addHandler (input); // currently testing it as a gamepad handler.
	// might be a good idea to make it one multi controller rather than having separate wrapping objects
	
	///eventDispatcher-> addHandler (gamepadsHandler);
	
	eventDispatcher-> addHandler (closeHandler);
	///eventDispatcher-> addHandler (keyboardHandler);
	eventDispatcher-> addHandler (notifiedKeyboardFocusLostHandler);
	eventDispatcher-> addHandler (notifiedKeyboardFocusGainedHandler);

	eventQueue-> addDispatcher (eventDispatcher);
	

	DeltaTime::Ptr deltaTimeBuffer (new DeltaTime (expectedFps));
	deltaTime = deltaTimeBuffer;

	deltaTime-> setBound (0.5, 3.0);
	window-> setClearColor (0, 0, 0);
	
	useFrameCap = false;
	frameCap.setMaximumFPS (expectedFps);
	frameCap.setMinimumSleepInterval (5);

	//MyFocusMethod myFocusMethod (&focusPauser, window, eventQueue, sceneGraph);

	viewport = new aab::game::Viewport (window);
	
	//crashes
	//gamepad = makeGamepad ();
	//EventHandler::Ptr gamepadsHandler2 (EventHandler::Ptr(new GamepadsAutoHandler (gamepad)));
	//eventDispatcher-> addHandler (gamepadsHandler2);
	
	//doesn't crash, but provides no control!
//	gamepad = makeGamepad ();
//		EventHandler::Ptr
	//gamepadsHandler2 = EventHandler::Ptr(new GamepadsAutoHandler (gamepad));
	//eventDispatcher-> addHandler (gamepadsHandler2);
}

GameEngine::~GameEngine ()
{
	delete viewport;

	//events, pads and screen are smart pointers
}

void GameEngine::focusLostLoop ()
{
	aab::time::delay(10);
}

void GameEngine::run ()
{
	start ();
	while (running())
	{
		updateEngine();
		checkForLostFocus();
		loop ();
	}
	end();
}

void GameEngine::checkForLostFocus ()
{
    if (keyboardFocusMonitor.isFocusLost())
    {
        focusLostStart();
        
        while(1)
        {
            focusLostLoop ();
            updateInputDevices();
            
            if (! keyboardFocusMonitor.isFocusLost())
            {
                focusLostEnd();
                break;
            }
        }
        
    }
    
//	while(keyboardFocusMonitor.isFocusLost())
//	{
//		//window-> clear (); // todo - clear should be done by user inside loop
//		this-> focusLost ();
//		//window-> update ();
//		updateInputDevices();
//	}
}



void GameEngine::updateEngine ()
{
	//afters
	//loop();
	//viewport->commit(); // must be called within loop instead, as game logic updates for the rest of the loop
	window-> update ();
	if (useFrameCap)
	{
        frameCap.wait();
	}
	fps.update();
	deltaTime-> update ();
	//ticker.update ();

	//befores
	//myFocusMethod.checkFocus();
	if (clearScreen)
	{
        window-> clear ();
	}

	updateInputDevices();
}

void GameEngine::updateInputDevices()
{
	//gamepad-> update ();
	//gamepadPorts->updateGamepadPorts();

	mouse-> update ();
	input-> update();
	///keyboard-> update ();
	eventQueue-> poll ();
}

bool GameEngine::running ()
{
	return ! closeHandler-> hasClosed ();
}


/**
input::Gamepad GameEngine::makeGamepad ()
//	throw (aab::input::GamepadUnavailableException&, aab::input::NoGamepadsException&, aab::input::FailedToOpenGamepadException&)
{
	input::Gamepad gamepad = aab::input::makeGamepad(gamepadPorts);

	//events::EventHandler::Ptr gamepadsHandler = events::EventHandler::Ptr(new events::GamepadsAutoHandler (gamepad));
	//changed to:
	//events::EventHandler::Ptr gamepadsHandler (new events::GamepadsAutoHandler (gamepad));
	//eventDispatcher-> addHandler (gamepadsHandler);

	//EventHandler::Ptr
	//GamepadsAutoHandler::Ptr
	//gamepadsHandler2 = GamepadsAutoHandler::Ptr(new GamepadsAutoHandler (gamepad));
	//gamepadsHandler = EventHandler::Ptr(new GamepadsAutoHandler (gamepad));
	
	
	///aab::events::GamepadsAutoHandler::Ptr gamepadsHandler =
    ///    aab::events::GamepadsAutoHandler::Ptr
     ///               (new events::GamepadsAutoHandler (gamepad));
	///eventDispatcher-> addHandler (gamepadsHandler);
	gamepadsHandler->addGamepad(gamepad);
	// should the handler be premade and new pads added to it?

	return gamepad;
}
*/

void GameEngine::closeGame()
{
	closeHandler->close();
}

game::Sprite * GameEngine::loadSprite (std::string filename)
{ return game::loadSprite(window, filename); }

game::Sprite * GameEngine::loadSprite (std::string filename, const visen::Colorf mask)
{ return game::loadSprite(window, filename, mask); }

game::Sprite * GameEngine::loadSprite (std::string filename, std::string maskfilename)
{ return game::loadSprite(window, filename, maskfilename); }

game::Sprite * GameEngine::loadSprite (std::string filename, const visen::Colorf mask, int frameWidth, int frameHeight, int frames)
{ return game::loadSprite(window, filename, mask, frameWidth, frameHeight, frames/*, deltaTime*/); }

game::Sprite * GameEngine::loadSprite (std::string filename, std::string maskfilename, int frameWidth, int frameHeight, int frames)
{ return game::loadSprite(window, filename, maskfilename, frameWidth, frameHeight, frames/*, deltaTime*/); }

game::Sprite * GameEngine::loadSprite (std::string filename, const visen::Colorf mask, int frameWidth, int frameHeight)//, time::FrameTicker::Ptr ticker)
{ return game::loadSprite(window, filename, mask, frameWidth, frameHeight/*, ticker*/); }

game::Sprite * GameEngine::loadSprite (std::string filename, std::string maskfilename, int frameWidth, int frameHeight)//, time::FrameTicker::Ptr ticker)
{ return game::loadSprite(window, filename, maskfilename, frameWidth, frameHeight/*, ticker*/); }


}		//	game
}		//	aab






