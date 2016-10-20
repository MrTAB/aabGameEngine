
/**
*
*	gamepad_hat_event.cpp
*
**/

#include"gamepad_hat_event.hpp"
#include<sdl.h>
#include<cmath>
namespace aab	{
namespace events{


GamepadHatEvent::GamepadHatEvent (InternalEvent internalEvent) : Event (getClassEventType ())
{
	SDL_Event * event = static_cast <SDL_Event *> (internalEvent-> getReference ());

	id = event-> jhat.which;
	hat = event-> jhat.hat;
	value = event-> jhat.value;
}


GamepadHatEvent::~GamepadHatEvent () throw ()
{
	// nothing //
}

int GamepadHatEvent::getGamePadId () const
{
	return id;
}

int GamepadHatEvent::getHatId () const
{
	return hat;
}

GamepadHatEvent::HatPosition GamepadHatEvent::getHatPosition () const
{
	return value;
}

EventType GamepadHatEvent::getClassEventType ()
{
	return gamepad_hat_event;
}

}		//	events
}		//	aab



