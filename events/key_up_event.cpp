
/**
*
*	key_up_event.cpp
*
**/

#include"key_up_event.hpp"
#include<sdl.h>
namespace aab	{
namespace events{

KeyUpEvent::KeyUpEvent (InternalEvent internalEvent) : KeyEvent (internalEvent, getClassEventType ())
{
	// nothing //
}


KeyUpEvent::~KeyUpEvent () throw ()
{
	// nothing //
}


EventType KeyUpEvent::getClassEventType ()
{
	return key_up_event;
}


}		//	events
}		//	aab



