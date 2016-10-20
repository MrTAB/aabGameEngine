
/**
*
*	gamepad_ports.cpp
*
**/

#include"gamepad_ports.hpp"
#include<sdl.H>
#include<iterator>
#include<algorithm>
#include"../test/exceptions.hpp"
namespace aab	{
namespace input	{


bool GamepadPortsClass::exists (false);

GamepadPorts startGamepadPorts (InputConnector::Ptr inputConnector)// aab::test::already_instantiated_error
{
	if (GamepadPortsClass::exists)
	{
		throw aab::test::already_instantiated_error ("GamepadPorts::startGamepadPorts::\tSingleton GamepadPorts already exists and cannot be made again.");
	}

	GamepadPorts ptr (new GamepadPortsClass(inputConnector), GamepadPortsClass::Deleter());
	GamepadPortsClass::exists = true;

	return ptr;
}




GamepadPortsClass::GamepadPortsClass (InputConnector::Ptr):
	hint (-1),	// -1 will be used to mean no hint
	unpluggedCallback(0)
{
	int count = SDL_NumJoysticks ();
	bool initialValue = true; // initially all free

	if (count > 0)
	{
		portFree.assign (count, initialValue);
	}
	enableGamepadEvents();
}

GamepadPortsClass::~GamepadPortsClass() throw ()
{
	/* nothing */
}

int GamepadPortsClass::countGamepads () const
{
	return portFree.size ();
}


int GamepadPortsClass::countGamepadsAvailable () const
{
	return std::count (portFree.begin (), portFree.end (), true);
}

bool GamepadPortsClass::hasFreeGamepad () const
{
	return std::find (portFree.begin (), portFree.end (), true) != portFree.end ();
}

void GamepadPortsClass::updateGamepads ()
{
	SDL_JoystickUpdate ();
}

void GamepadPortsClass::updateGamepadPorts () 
{
	int num = SDL_NumJoysticks ();
    int oldSize = static_cast<int>(portFree.size());
    
	if (num < oldSize)
	{
	    portFree.erase (portFree.begin() + num, portFree.end());
	    if (unpluggedCallback)
	    {
	        GamepadUnpluggedList unpluggedIds;	        
	        for (int t = num;t<oldSize;++t)
	        {
                unpluggedIds.push_back(t);
	        }
	        unpluggedCallback->gamepadsUnplugged(unpluggedIds);
	    }		
	}
	else if (num > oldSize)
	{
		// add on the new Gamepads:
		bool initialValue = true;
		portFree.insert (portFree.end(), num - portFree.size(), initialValue);
	}
}

bool GamepadPortsClass::hintNextId (int id)
{
	if ((unsigned int) id < portFree.size ())
	{
		if (portFree [id])
		{
			hint = id;

			return true;
		}
	}

	return false;
}

int GamepadPortsClass::getFreeId () //throw (GamepadUnavailableException&, NoGamepadsException&)
{
    if (portFree.empty())
    {
        throw NoGamepadsException();
    }
    
	if (hint != -1)
	{
		int useHint = hint;

		hint = -1;

		portFree [useHint] = false;

		return useHint;
	}

	using std::vector;
	vector<bool>::iterator itr = portFree.begin ();
	vector<bool>::iterator end = portFree.end ();
	int index = 0;

	for (;itr != end; ++itr, ++index)
	{
		if (*itr)
		{
			*itr = false;

			return index;
		}
	}

	throw GamepadUnavailableException();

	return -1; // just to avoid warning
}

void GamepadPortsClass::releaseId (int id)
{
	if ((unsigned int) id < portFree.size () && id >= 0)
	{
		portFree [id] = true;
	}
}

void GamepadPortsClass::enableGamepadEvents ()
{
	SDL_JoystickEventState (SDL_ENABLE);
}

void GamepadPortsClass::setUnpluggedCallback (GamePadUnpluggedCallback * unpluggedCallbackIn)
{
    unpluggedCallback = unpluggedCallbackIn;
}

bool GamepadPortsClass::isPortActive(int id)
{
    return id < SDL_NumJoysticks () && id >= 0;
}

bool GamepadPortsClass::isPortRegistered(int id)
{
    if (id < portFree.size() && id >= 0)
    {
        return !(portFree[id]);
    }
    return false;
}

bool GamepadPortsClass::isPortFree(int id)
{
    if (id < portFree.size() && id >= 0)
    {
        return portFree[id];
    }
    return false;
}



}		//	input
}		//	aab





