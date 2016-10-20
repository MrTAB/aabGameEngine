
/**
*
*	gamepad_button_up_event.cpp
*
**/

#include"gamepad_button_up_event.hpp"
#include<sdl.h>
#include<cmath>
namespace aab	{
namespace events{



GamepadButtonUpEvent::GamepadButtonUpEvent (InternalEvent internalEvent) : Event (getClassEventType ())
{
	SDL_Event * event = static_cast <SDL_Event *> (internalEvent-> getReference ());

	id = event-> jbutton.which;
	button = event-> jbutton.button;
}


GamepadButtonUpEvent::~GamepadButtonUpEvent () throw ()
{
	// nothing //
}

int GamepadButtonUpEvent::getGamePadId () const
{
	return id;
}

int GamepadButtonUpEvent::getButton () const
{
	return button;
}

EventType GamepadButtonUpEvent::getClassEventType ()
{
	return gamepad_button_up_event;
}

}		//	events
}		//	aab



