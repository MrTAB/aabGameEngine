
/**
*
*	mouse_button_up_event.cpp
*
**/
/* NOT REMOVED */
//#if 0
#include"mouse_button_up_event.hpp"
#include<sdl.h>
namespace aab	{
namespace events{

MouseButtonUpEvent::MouseButtonUpEvent (InternalEvent internalEvent) : Event (getClassEventType ())
{
	SDL_Event * event = static_cast <SDL_Event *> (internalEvent-> getReference ());

	x = event-> button.x;
	y = event-> button.y;
	button = event-> button.button;
}


MouseButtonUpEvent::~MouseButtonUpEvent () throw ()
{
	// nothing //
}

int MouseButtonUpEvent::getButton () const
{
	return button;
}

int MouseButtonUpEvent::getX () const
{
	return x;
}

int MouseButtonUpEvent::getY () const
{
	return y;
}

EventType MouseButtonUpEvent::getClassEventType ()
{
	return mouse_button_up_event;
}


}		//	events
}		//	aab
//#endif


