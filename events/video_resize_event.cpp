
/**
*
*	video_resize_event.cpp
*
**/

#include"video_resize_event.hpp"
#include<sdl.h>
#include<cmath>
namespace aab	{
namespace events{



VideoResizeEvent::VideoResizeEvent (InternalEvent internalEvent) : Event (getClassEventType ())
{
	SDL_Event * event = static_cast <SDL_Event *> (internalEvent-> getReference ());

	width = event-> resize.w;
	height = event-> resize.h;
}


VideoResizeEvent::~VideoResizeEvent () throw ()
{
	// nothing //
}

int VideoResizeEvent::getNewWidth () const
{
	return width;
}

int VideoResizeEvent::getNewHeight () const
{
	return height;
}


EventType VideoResizeEvent::getClassEventType ()
{
	return video_resize_event;
}

}		//	events
}		//	aab



