
/**
*
*	gameengine.hpp
*
*   While the library can be used imperatively by creating and managing an
*   instance of screen, you can instead extend GameEngine and implement the
*   virtual methods defined as { } below. Invoke run on an instance of your
*   subclass and it will run through the game loop, returning control to your
*   code base by calling those overriden methods. Alternatively, you can choose
*   not to invoke run and use the gameengine imperatively, by calling
*   updateEngine() to update the screen and input devices etc.
*
*   start is called after window initialisation, and is for load time operations.
*   loop is then called once every loop.
*   end is called after the main game loop has exited.
*   
*   loop has a default implemntation of  { processInput(); updateLogic(); render();};
*   You can choose to implement them and leave loop as it is, or to override loop
*   and deal with the deal as it is. 
*
*   Override the focusLost methods to respond to focus being lost.
**/

#if !defined(AAB_ENGINE_GAME_ENGINE_CLASS)
#define AAB_ENGINE_GAME_ENGINE_CLASS
#include"prototype/gameengine.hh"
#include"../auden/auden.hpp"
#include"../events/events.hpp"
#include"../game/game.hpp"
#include"../input/input.hpp"
#include"../maths/maths.hpp"
#include"../time/time.hpp"
#include"../types/types.hpp"
#include"../visen/visen.hpp"
#include"../test/test.hpp"
#include<string>
namespace aab	{
namespace engine	{



class GameEngine //: public virtual aab::input::GamePadUnpluggedCallback
{	
	void sharedConstructorCode();        
        
	public:

	typedef visen::ScreenMode ScreenMode;
	typedef game::Sprite Sprite;
	typedef game::SpriteBatch SpriteBatch;
	typedef visen::TexturePtr TexturePtr;
	typedef visen::AnimatedTexturePtr AnimatedTexturePtr;
	typedef visen::TextureAtlasPtr TextureAtlasPtr;

	explicit GameEngine (int screenWidth, int screenHeight, ScreenMode mode = visen::windowed_mode, unsigned int fps=60);
	explicit GameEngine (const visen::ContextDefinition&, unsigned int fps=60);
	virtual ~GameEngine ();

	virtual void start () {};
	virtual void loop () { processInput(); updateLogic(); render();};
	virtual void end () {};
	virtual void processInput() {}; 
	virtual void updateLogic () {}; 
	virtual void render () {}; 

    virtual void focusLostStart() { };
	virtual void focusLostLoop ();
	virtual void focusLostEnd() { };
	virtual void run ();
	bool running ();
	void updateEngine ();

    unsigned int getExpectedFps() const { return expectedFps; }
    
	float secondsToFrames(const float seconds) {return seconds*static_cast<float>(this->getExpectedFps());}

	//utility methods

	//input::Gamepad makeGamepad();// throw (aab::input::GamepadUnavailableException&, aab::input::NoGamepadsException&, aab::input::FailedToOpenGamepadException&);
	void closeGame();

	// methods which do not ask for a ticker will require the ticker being updated once per loop
	// Pull out and Update - can pull them all into a list and run through that list each loop.

	Sprite * loadSprite (std::string filename);
	Sprite * loadSprite (std::string filename, const visen::Colorf mask);
	Sprite * loadSprite (std::string filename, std::string maskfilename);
	Sprite * loadSprite (std::string filename, const visen::Colorf mask, int frameWidth, int frameHeight, int frames);
	Sprite * loadSprite (std::string filename, std::string maskfilename, int frameWidth, int frameHeight, int frames);
	Sprite * loadSprite (std::string filename, const visen::Colorf mask, int frameWidth, int frameHeight);//, time::FrameTicker::Ptr ticker);
	Sprite * loadSprite (std::string filename, std::string maskfilename, int frameWidth, int frameHeight);//, time::FrameTicker::Ptr ticker);
	Sprite * clearSprite (Sprite * sprite) { return game::clearSprite(sprite); }

	protected:

		visen::Screen window;
		//input::GamepadPorts gamepadPorts;
		events::EventQueue eventQueue;
		events::Dispatcher eventDispatcher;
		input::Mouse mouse;
		//input::Keyboard keyboard;
		time::DeltaTime::Ptr deltaTime;
		time::Fps fps;
		auden::Mixer mixer;
		//aab::events::GamepadsAutoHandler::Ptr gamepadsHandler;
		events::CloseHandler::Ptr closeHandler;
		//events::EventHandler::Ptr keyboardHandler;
		game::Viewport * viewport;
		events::KeyboardFocusMonitor keyboardFocusMonitor;
		bool clearScreen;
		time::Cap frameCap;
		bool useFrameCap;
		unsigned int expectedFps;
		///
		//input::Gamepad gamepad;
		
		input::InputController input;
		//events::EventHandler::Ptr ICkeyboardHandler;
		
	public:

        //int countGamepads(){ return gamepadPorts->countGamepads(); }
		visen::Screen getWindow(){return window;}
		//input::GamepadPorts getGamepadPorts(){return gamepadPorts;}
		events::EventQueue getEventQueue(){return eventQueue;}
		events::Dispatcher getEventDispatcher(){return eventDispatcher;}
		input::Mouse getMouse(){return mouse;}
		//input::Keyboard getKeyboard(){return keyboard;}
		input::InputController getInputController(){ return input; }
		time::DeltaTime::Ptr getDeltaTime(){return deltaTime;}
		time::Fps&referenceFps(){return fps;}
		auden::Mixer&referenceMixer(){return mixer;}
		events::CloseHandler::Ptr getCloseHandler(){return closeHandler;}
		//events::EventHandler::Ptr getGamepadsHandler(){return gamepadsHandler;}
		
		//temporary
		//events::EventHandler::Ptr getKeyboardHandler(){return keyboardHandler;}
		void updateInputDevices();
		void checkForLostFocus();
		void waitTillCap() { frameCap.wait(); }
		
		/*
        virtual void gamepadsUnplugged(aab::input::GamepadUnpluggedList unpluggedIds)
        {        
            // implement this method in the engine subclass and do what you wish to be done during the event where a gamepad has been unplugged.            
            // iterate unpluggedIds to see what gamepad id's have been invalidated.
            // If the gamepad your user is using has not been unplugged then you may not have to do anything about it.
            // e.g.
            //        using aab::input::GamepadUnpluggedIterator;
            //        for(GamepadUnpluggedIterator badPad = unpluggedIds.begin(); badPad != unpluggedIds.end(); ++badPad)
            //        {
            //            if(*badPad // using? Can use isPortRegistered() to check if it is one that has had a gamepad made from it using makeGamepad
            //        }
        }
        */

};



}		//	engine
}		//	aab
#endif	//	AAB_ENGINE_GAME_ENGINE_CLASS




