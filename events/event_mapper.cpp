
/**
*
*	event_mapper.cpp
*
**/

#include"event_mapper.hpp"
#include<sdl.h>
namespace aab	{
namespace events{
using std::vector;


EventMapper::MapAutoPtr initialiseEventMapper ();
EventMapper::MapAutoPtr EventMapper::mapping = initialiseEventMapper ();



static vector <EventType> activeEventMethod (InternalEvent);
static vector <EventType> keyDownEventMethod (InternalEvent);
static vector <EventType> keyUpEventMethod (InternalEvent);
static vector <EventType> mouseMotionEventMethod (InternalEvent);
static vector <EventType> mouseDownEventMethod (InternalEvent);
static vector <EventType> mouseUpEventMethod (InternalEvent);
static vector <EventType> joyAxisMotionEventMethod (InternalEvent);
static vector <EventType> joyBallMotionEventMethod (InternalEvent);
static vector <EventType> joyHatMotionEventMethod (InternalEvent);
static vector <EventType> joyButtonDownEventMethod (InternalEvent);
static vector <EventType> joyButtonUpEventMethod (InternalEvent);
static vector <EventType> quitEventMethod (InternalEvent);
static vector <EventType> systemWindowManagerEventMethod (InternalEvent);
static vector <EventType> videoResizeEventMethod (InternalEvent);
static vector <EventType> userEventMethod (InternalEvent);



EventMapper::MapAutoPtr initialiseEventMapper ()
{
	EventMapper::MapAutoPtr mapPtr (new EventMapper::Map ());

	(*mapPtr) [SDL_ACTIVEEVENT]			= activeEventMethod;
	(*mapPtr) [SDL_KEYDOWN]				= keyDownEventMethod;
	(*mapPtr) [SDL_KEYUP]				= keyUpEventMethod;
	(*mapPtr) [SDL_MOUSEMOTION]			= mouseMotionEventMethod;
	(*mapPtr) [SDL_MOUSEBUTTONDOWN]		= mouseDownEventMethod;
	(*mapPtr) [SDL_MOUSEBUTTONUP]		= mouseUpEventMethod;
	(*mapPtr) [SDL_JOYAXISMOTION]		= joyAxisMotionEventMethod;
	(*mapPtr) [SDL_JOYBALLMOTION]		= joyBallMotionEventMethod;
	(*mapPtr) [SDL_JOYHATMOTION]		= joyHatMotionEventMethod;
	(*mapPtr) [SDL_JOYBUTTONDOWN]		= joyButtonDownEventMethod;
	(*mapPtr) [SDL_JOYBUTTONUP]			= joyButtonUpEventMethod;
	(*mapPtr) [SDL_QUIT]				= quitEventMethod;
	(*mapPtr) [SDL_SYSWMEVENT]			= systemWindowManagerEventMethod;
	(*mapPtr) [SDL_VIDEORESIZE]			= videoResizeEventMethod;
	(*mapPtr) [SDL_USEREVENT]			= userEventMethod;

	return mapPtr;
}

vector <EventType> EventMapper::convert (InternalEvent internal)
{
	ConvertMethod method = (*mapping)[internal-> getType ()];

	if (method)
	{
		return method (internal);
	}

	return vector <EventType> ();
}




vector <EventType> activeEventMethod (InternalEvent event)
{
	SDL_Event * sdlEvent = static_cast <SDL_Event*> (event-> getReference ());
	vector <EventType> events;
	Uint8 state = sdlEvent-> active.state;

	if (sdlEvent-> active.gain)
	{
		if (state & SDL_APPMOUSEFOCUS)
		{
			events.push_back (mouse_focus_gained_event);
		}
		if (state & SDL_APPINPUTFOCUS)
		{
			events.push_back (keyboard_focus_gained_event);
		}
		if (state & SDL_APPACTIVE)
		{
			events.push_back (window_restored_event);
		}
	}
	else
	{

		if (state & SDL_APPMOUSEFOCUS)
		{
			events.push_back (mouse_focus_lost_event);
		}
		if (state & SDL_APPINPUTFOCUS)
		{
			events.push_back (keyboard_focus_lost_event);
		}
		if (state & SDL_APPACTIVE)
		{
			events.push_back (window_minimised_event);
		}
	}

	return events;
}


vector <EventType> keyDownEventMethod (InternalEvent)
{
	return vector <EventType> (1, key_down_event);
}

vector <EventType> keyUpEventMethod (InternalEvent)
{
	return vector <EventType> (1, key_up_event);
}

vector <EventType> mouseMotionEventMethod (InternalEvent)
{
	return vector <EventType> (1, mouse_move_event);
}

vector <EventType> mouseDownEventMethod (InternalEvent)
{
	return vector <EventType> (1, mouse_button_down_event);
}

vector <EventType> mouseUpEventMethod (InternalEvent)
{
	return vector <EventType> (1, mouse_button_up_event);
}

vector <EventType> joyAxisMotionEventMethod (InternalEvent)
{
	return vector <EventType> (1, gamepad_axis_event);
}

vector <EventType> joyBallMotionEventMethod (InternalEvent)
{
	return vector <EventType> (1, gamepad_ball_event);
}

vector <EventType> joyHatMotionEventMethod (InternalEvent)
{
	return vector <EventType> (1, gamepad_hat_event);
}

vector <EventType> joyButtonDownEventMethod (InternalEvent)
{
	return vector <EventType> (1, gamepad_button_down_event);
}

vector <EventType> joyButtonUpEventMethod (InternalEvent)
{
	return vector <EventType> (1, gamepad_button_up_event);
}

vector <EventType> quitEventMethod (InternalEvent)
{
	return vector <EventType> (1, quit_event);
}

vector <EventType> systemWindowManagerEventMethod (InternalEvent)
{
	return vector <EventType> (1, window_manager_event);
}

vector <EventType> videoResizeEventMethod (InternalEvent)
{
	return vector <EventType> (1, video_resize_event);
}

vector <EventType> userEventMethod (InternalEvent)
{
	return vector <EventType> (1, user_event);
}


}		//	events
}		//	aab



