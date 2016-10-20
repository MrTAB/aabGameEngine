
/**
*
*	auto_keyboard.cpp
*
**/

#include"auto_keyboard.hpp"
#include"../time/time.hpp"
#include<sdl.H>
#include<cstdio>
#include<algorithm>
#include<iostream>
namespace aab	{
namespace input	{
using std::cout;

AutoKeyboard makeAutoKeyboard (InputConnector::Ptr inputConnector)
	//throw (std::exception &)
{
	AutoKeyboard ptr (new AutoKeyboardClass (inputConnector), AutoKeyboardClass::Deleter ());
	return ptr;
}


AutoKeyboardClass::AutoKeyboardClass (InputConnector::Ptr):
	//throw (std::exception &):
	keys (NULL),
	size (0),
	pumpEvents (true),
	timeFunction (aab::time::getMilliseconds),
	mods (0)
{
	/* nothing */
}

AutoKeyboardClass::~AutoKeyboardClass () throw ()
{
	/* nothing */
}

bool AutoKeyboardClass::isDown (KeyCode key) const
{
	if (hasRead (key))
	{
		return keys[key];
	}

	return false;
}

bool AutoKeyboardClass::isToggled (KeyCode key) const
{
	if (hasRead (key) && hasPreviouslyRead (key))
	{
		return keys[key] != previousKeys[key];
	}

	return false;
}

void AutoKeyboardClass::refreshKey(KeyCode key)
{
    previousKeys[key] = 0;
}

bool AutoKeyboardClass::isHit (KeyCode key) const
{
	return isDown (key) && isToggled (key);
}

bool AutoKeyboardClass::isReleased (KeyCode key) const
{
	return (! isDown (key)) && isToggled (key);
}

bool AutoKeyboardClass::isHeldLongerThan (KeyCode key, unsigned int milliseconds) const
{
	return isDown (key) && getRest (key) >= milliseconds;
}

bool AutoKeyboardClass::isHeldLongerThan (KeyCode a, KeyCode b) const
{
	return isDown (a) && isDown (b) && getLastToggle (a) < getLastToggle (b);
}

bool AutoKeyboardClass::isModOn (ModCode mod) const
{
	return mods & mod;
}

unsigned int AutoKeyboardClass::getRest (KeyCode key) const
{
	return timeFunction() - getLastToggle (key);
}


unsigned int AutoKeyboardClass::getLastToggle (KeyCode key) const
{
	if (hasToggleTimeFor (key))
	{
		return lastToggle[key];
	}
	else
	{
		return 0;
	}
}


bool AutoKeyboardClass::hasRead (KeyCode key) const
{
	return static_cast <int> (key) < size;
}

bool AutoKeyboardClass::hasPreviouslyRead (KeyCode key) const
{
	return static_cast <unsigned int> (key) < previousKeys.size ();
}

bool AutoKeyboardClass::hasToggleTimeFor (KeyCode key) const
{
	return static_cast <unsigned int> (key) < lastToggle.size ();
}


void AutoKeyboardClass::update ()
{

	//store a copy of the previous values of the keys before updating events:

	std::copy (keys,keys+size,&previousKeys.front());


	//update events:

	if (pumpEvents)
	{
		SDL_PumpEvents ();
	}

	// get the current state of the keys:
	keys = SDL_GetKeyState (&size);
	mods = SDL_GetModState ();

	//check for change in size (change in keyboard?)

	if (static_cast <unsigned int> (size) < previousKeys.size())
	{
		// can leave this i guess.
	}
	else if (static_cast <unsigned int> (size) > previousKeys.size())
	{
		resize (size);
	}

	// update the toggle times:
	unsigned int now = timeFunction ();

	for (int t = 0; t < size; ++t)
	{
		if (keys[t] != previousKeys[t])
		{
			lastToggle[t] = now;
		}
	}
}

void AutoKeyboardClass::resize (int newSize)
{
	unsigned char blankchar = 0;
	unsigned int blankuint = 0;
	previousKeys.insert (previousKeys.end(), newSize - previousKeys.size(), blankchar);
	lastToggle.insert (lastToggle.end(), newSize - lastToggle.size(), blankuint);
	size = newSize;
}

void AutoKeyboardClass::enableEventGrabbing ()
{
	pumpEvents = true;
}

void AutoKeyboardClass::disableEventGrabbing ()
{
	pumpEvents = false;
}

bool AutoKeyboardClass::isEventGrabbingEnabled () const
{
	return pumpEvents;
}



}		//	input
}		//	aab





