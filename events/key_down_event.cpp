
/**
*
*	key_down_event.cpp
*
**/

#include"key_down_event.hpp"
#include<sdl.h>
namespace aab	{
namespace events{

KeyDownEvent::KeyDownEvent (InternalEvent internalEvent) : KeyEvent (internalEvent, getClassEventType ())
{
	// nothing //
}


KeyDownEvent::~KeyDownEvent () throw ()
{
	// nothing //
}


EventType KeyDownEvent::getClassEventType ()
{
	return key_down_event;
}


}		//	events
}		//	aab



