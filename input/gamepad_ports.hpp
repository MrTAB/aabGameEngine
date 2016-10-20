
/**
*
*	gamepad_ports.hpp
*
*	GamePadPorts	-	ports of the gamepads plugged in.
*
*	Create an instance of GamePadPorts, and then check the available GamePads.
*	Use GamePadPorts to obtain GamePad objects, and continually call
*	updateGamePads() to synchronize the state of all the GamePads; unless
*	your using the event handlers or a gamepad_state, in which case there
*	is no need to call update.
*	Its a singleton too.
*   Call updateGamepadPorts to continually check that game pads are still
*   plugged in. Register a GamePadUnpluggedCallback to receive a notification
*   when gamepads have been unplugged. Alternatively, use isPortActive with
*   individual, previously requested port numbers in order to check if those
*   gamepads are still plugged in.
*
*	Use hintNextId to hint on what the next created GamePads Id will be.
*	.. and use referencing or pointers when passing as Copy construction
*	is dissallowed.
**/

#if !defined(AAB_INPUT_GAMEPAD_PORTS_CLASS)
#define AAB_INPUT_GAMEPAD_PORTS_CLASS
#include"input_connector.hpp"
#include"../types/smart_ptr.hpp"
#include"../types/manager.hpp"
#include<stdexcept>
#include<string>
#include<sstream>
#include<vector>
#include<list>
namespace aab	{
namespace input	{

class GamepadUnavailableException: public std::runtime_error
{
    public:
    
    GamepadUnavailableException():
        runtime_error("aab::input::GamepadsUnavailableException\tNo Gamepads detected that are available for use.")
    {
        // do nothing //
    }
};

class NoGamepadsException: public std::runtime_error
{
    public:
    
    NoGamepadsException():
        runtime_error("aab::input::NoGamepadsException\tNo Gamepads are connected to the computer.")
    {
        // do nothing //
    }
};

class FailedToOpenGamepadException: public std::runtime_error
{
    int id;
    public:
    
    FailedToOpenGamepadException(const int id_in):
        runtime_error("aab::input::FailedToOpenGamepadException\tFailed to open Gamepad id: "),
        id(id_in)
    {
        // do nothing //
    }
    
    virtual const char* what() const throw ()
    {
        std::string message(runtime_error::what());
        //message += std::to_string(id);
        
        std::stringstream ss;
        ss << message << id;
        
        return ss.str().c_str();
    }
};

typedef std::list<int> GamepadUnpluggedList;
typedef std::list<int>::iterator GamepadUnpluggedIterator;
    
struct GamePadUnpluggedCallback
{
    virtual ~GamePadUnpluggedCallback()
    {
        // do nothing //
    }
    
    virtual void gamepadsUnplugged(GamepadUnpluggedList unpluggedIds)
    {
        // extend this class, implement this method and do what you wish to be done during the event where a gamepad has been unplugged.
        // Must register your instance polymorphically with GamepadPortsClass, and call updateGamepadPorts() to check ports available and receive callbacks where appropriate.
        //iterate unpluggedIds to see what gamepad id's have been invalidated.
        // If the gamepad your user is using has not been unplugged then you may not have to do anything about it.
        // e.g.
        //        for(GamepadUnpluggedIterator badPad = unpluggedIds.begin(); badPad != unpluggedIds.end(); ++badPad)
        //        {
        //            if(*badPad // using? - can use ::isPortRegistered() to check if it has been registered for use
        //        }
    }
};

// GamepadPortsClass
//  Manages 
class GamepadPortsClass : public aab::types::Manager <GamepadPortsClass>
{
	public:

		typedef aab::types::Smart <GamepadPortsClass>::Ptr Ptr;

	private:

		std::vector<bool> portFree; // each port is either free (true) or not (false)
		int hint;
		GamePadUnpluggedCallback * unpluggedCallback;

		static bool exists;

		int getFreeId (); //throw (GamepadUnavailableException&, NoGamepadsException&);
		void releaseId (int id);

		friend class GamepadDataClass;

		GamepadPortsClass (GamepadPortsClass &);

	protected:

		friend Ptr startGamepadPorts (InputConnector::Ptr);//aab::test::already_instantiated_error
		friend class aab::types::Manager <GamepadPortsClass>::Deleter;
		explicit GamepadPortsClass (InputConnector::Ptr);
		virtual ~GamepadPortsClass () throw ();

	public:

	int countGamepads () const;
	int countGamepadsAvailable () const;
	bool hasFreeGamepad () const;

	void updateGamepads ();
	void updateGamepadPorts ();

	bool hintNextId (int id); // false on failure (gamepad not plugged in or already taken).

	void enableGamepadEvents ();
	
	// Does not take ownership: must keep object in scope.
	// updateGamepadPorts will invoke the callback if any gamepads have been unplugged.
	void setUnpluggedCallback (GamePadUnpluggedCallback * unpluggedCallback);
	bool isPortActive(int id); // explicitly checks if a port has a plugged in gamepad ..
	bool isPortRegistered(int id); //checks if the port/id has been taken by a gamepad object
	bool isPortFree(int id); //checks if a port is free, i.e. opposite of isPortRegistered()

};

typedef GamepadPortsClass::Ptr GamepadPorts;
GamepadPorts startGamepadPorts (InputConnector::Ptr); //aab::test::already_instantiated_error


}		//	input
}		//	aab
#endif	//	AAB_INPUT_GAMEPAD_PORTS_CLASS




