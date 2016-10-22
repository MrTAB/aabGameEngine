
/**
*
*	mouse_move_event.cpp
*
**/
/* NOT REMOVED */
//#if 0
#include"mouse_move_event.hpp"
#include<sdl.h>
namespace aab	{
namespace events{

MouseMoveEvent::MouseMoveEvent (InternalEvent internalEvent) : Event (getClassEventType ())
{
	SDL_Event * event = static_cast <SDL_Event *> (internalEvent-> getReference ());

	x = event-> motion.x;
	y = event-> motion.y;
	xrel = event-> motion.xrel;
	yrel = event-> motion.yrel;
	buttonMask = event-> motion.state;
}


MouseMoveEvent::~MouseMoveEvent () throw ()
{
	// nothing //
}

EventType MouseMoveEvent::getClassEventType ()
{
	return mouse_move_event;
}


}		//	events
}		//	aab
//#endif


