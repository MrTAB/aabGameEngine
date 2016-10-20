
/**
*
*	key_event.cpp
*
**/

#include"key_event.hpp"
#include<sdl.h>
namespace aab	{
namespace events{

KeyEvent::KeyEvent (InternalEvent internalEvent, EventType type) : Event (type)
{
	SDL_Event * event = static_cast <SDL_Event *> (internalEvent-> getReference ());

	scanCode = event-> key.keysym.scancode;
	keyCode = static_cast <KeyCode> (event-> key.keysym.sym);
	modCode = event-> key.keysym.mod;
	unicode = event-> key.keysym.unicode;
}

KeyEvent::KeyEvent (byte_t scanCode, KeyCode keyCode, ModCode modCode, wchar_t unicode) :
	Event (key_up_event),
	scanCode (scanCode),
	keyCode (keyCode),
	modCode (modCode),
	unicode (unicode)
{
	// nothing //
}


KeyEvent::~KeyEvent () throw ()
{
	// nothing //
}


KeyEvent::byte_t KeyEvent::getScanCode () const
{
	return scanCode;
}

KeyEvent::KeyCode KeyEvent::getKeyCode () const
{
	return keyCode;
}

KeyEvent::ModCode KeyEvent::getModCode () const
{
	return modCode;
}

wchar_t KeyEvent::getUnicode () const
{
	return unicode;
}


}		//	events
}		//	aab



