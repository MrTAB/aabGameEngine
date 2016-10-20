
/**
*
*	keyboard.cpp
*
**/

#include"keyboard.hpp"
#include"../time/time.hpp"
#include<sdl.H>
#include<cstdio>
#include<algorithm>
#include<iostream>
namespace aab	{
namespace input	{
using std::cout;


Keyboard makeKeyboard ()
{
	Keyboard ptr (new KeyboardClass (), KeyboardClass::Deleter ());
	return ptr;
}


KeyboardClass::KeyboardClass () :
	timeFunction (aab::time::getMilliseconds)
{
	// nothing //
}

KeyboardClass::~KeyboardClass () throw ()
{
	// nothing //
}

void KeyboardClass::update ()
{
	justRead.clear ();
}

bool KeyboardClass::isDown (KeyCode key) const
{
	if (hasRead (key))
	{
		return keys[key].down;
	}

	return false;
}

bool KeyboardClass::isToggled (KeyCode key) const
{
	if (hasJustRead (key))
	{
		return keys[key].down != keys[key].previous;
	}

	return false;
}

bool KeyboardClass::isHit (KeyCode key) const
{
	return isDown (key) && isToggled (key);
}

bool KeyboardClass::isReleased (KeyCode key) const
{
	return (! isDown (key)) && isToggled (key);
}

bool KeyboardClass::isHeldLongerThan (KeyCode key, unsigned int milliseconds) const
{
	return isDown (key) && getRest (key) >= milliseconds;
}

bool KeyboardClass::isHeldLongerThan (KeyCode a, KeyCode b) const
{
	return isDown (a) && isDown (b) && getLastToggle (a) < getLastToggle (b);
}

unsigned int KeyboardClass::getRest (KeyCode key) const
{
	return timeFunction() - getLastToggle (key);
}


unsigned int KeyboardClass::getLastToggle (KeyCode key) const
{
	if (hasRead (key))
	{
		return keys[key].lastToggle;
	}
	else
	{
		return 0;
	}
}


bool KeyboardClass::hasRead (KeyCode key) const
{
	return keys.find (key) != keys.end ();
}

bool KeyboardClass::hasJustRead (KeyCode key) const
{
	return find (justRead.begin (), justRead.end (), key) != justRead.end ();
}

void KeyboardClass::prepareForKey (KeyCode code)
{
	keys[code].previous = keys[code].down;
	keys[code].lastToggle = timeFunction ();
	justRead.push_front (code);
}

void KeyboardClass::setKeyPress (KeyCode code)
{
	prepareForKey (code);
	keys[code].down = true;
}

void KeyboardClass::setKeyRelease (KeyCode code)
{
	prepareForKey (code);
	keys[code].down = false;
}

KeyboardClass::KeyData::KeyData () :
	down (0),
	previous (0),
	lastToggle (0)
{
	// nothing //
}

KeyboardClass::KeyData::KeyData (bool down, bool previous, unsigned int lastToggle) :
	down (down),
	previous (previous),
	lastToggle (lastToggle)
{
	// nothing //
}





}		//	input
}		//	aab





