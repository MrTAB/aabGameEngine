
/**
*
*	gamepad_axis_event.cpp
*
**/

#include"gamepad_axis_event.hpp"
#include<sdl.h>
#include<cmath>
namespace aab	{
namespace events{



GamepadAxisEvent::GamepadAxisEvent (InternalEvent internalEvent) : Event (getClassEventType ())
{
	SDL_Event * event = static_cast <SDL_Event *> (internalEvent-> getReference ());

	id = event-> jaxis.which;
	axis = event-> jaxis.axis;
	value = event-> jaxis.value;
}


GamepadAxisEvent::~GamepadAxisEvent () throw ()
{
	// nothing //
}

EventType GamepadAxisEvent::getClassEventType ()
{
	return gamepad_axis_event;
}

int GamepadAxisEvent::getGamePadId () const
{
	return id;
}

bool GamepadAxisEvent::isXAxis () const
{
	return axis == 0;
}

bool GamepadAxisEvent::isYAxis () const
{
	return axis == 1;
}

int GamepadAxisEvent::getWhichAxis () const
{
	return axis;
}

int16_t GamepadAxisEvent::getRawValue () const
{
	return value;
}

GamepadAxisValue GamepadAxisEvent::getAxisValue () const
{
    return value;/*
	if (std::abs (value) < 10)
	{
		return 0;
	}

	return (static_cast <double> (value)) / 32768.0;;*/
}



}		//	events
}		//	aab



