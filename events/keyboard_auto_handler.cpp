
/**
*
*	keyboard_auto_handler.cpp
*
**/

#include"keyboard_auto_handler.hpp"
namespace aab	{
namespace events{

KeyboardAutoHandler::KeyboardAutoHandler (KeyEventReceiver keyInfo) : keyInfo (keyInfo)
{
	// nothing //
}

KeyboardAutoHandler::~KeyboardAutoHandler () throw ()
{
	// nothing //
}

void KeyboardAutoHandler::keyPressed (KeyCode code)
{
	keyInfo-> setKeyPress (code);
}

void KeyboardAutoHandler::keyReleased (KeyCode code)
{
	keyInfo-> setKeyRelease (code);
}

void KeyboardAutoHandler::focusGained ()
{
	// nothing //
}

void KeyboardAutoHandler::focusLost ()
{
	// nothing //
}


}		//	events
}		//	aab



