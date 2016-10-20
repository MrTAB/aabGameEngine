
/**
*
*	gamepad_button_down_event.cpp
*
**/

#include"gamepad_button_down_event.hpp"
#include<sdl.h>
#include<cmath>
namespace aab	{
namespace events{



GamepadButtonDownEvent::GamepadButtonDownEvent (InternalEvent internalEvent) : Event (getClassEventType ())
{
	SDL_Event * event = static_cast <SDL_Event *> (internalEvent-> getReference ());

	id = event-> jbutton.which;
	button = event-> jbutton.button;
}


GamepadButtonDownEvent::~GamepadButtonDownEvent () throw ()
{
	// nothing //
}

int GamepadButtonDownEvent::getGamePadId () const
{
	return id;
}

int GamepadButtonDownEvent::getButton () const
{
	return button;
}

EventType GamepadButtonDownEvent::getClassEventType ()
{
	return gamepad_button_down_event;
}

}		//	events
}		//	aab



