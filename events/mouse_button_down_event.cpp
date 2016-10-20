
/**
*
*	mouse_button_down_event.cpp
*
**/
/* NOT REMOVED */
//#if 0
#include"mouse_button_down_event.hpp"
#include<sdl.h>
namespace aab	{
namespace events{

MouseButtonDownEvent::MouseButtonDownEvent (InternalEvent internalEvent) : Event (getClassEventType ())
{
	SDL_Event * event = static_cast <SDL_Event *> (internalEvent-> getReference ());

	x = event-> button.x;
	y = event-> button.y;
	button = event-> button.button;
}


MouseButtonDownEvent::~MouseButtonDownEvent () throw ()
{
	// nothing //
}


int MouseButtonDownEvent::getButton () const
{
	return button;
}

int MouseButtonDownEvent::getX () const
{
	return x;
}

int MouseButtonDownEvent::getY () const
{
	return y;
}


EventType MouseButtonDownEvent::getClassEventType ()
{
	return mouse_button_down_event;
}


}		//	events
}		//	aab
//#endif


