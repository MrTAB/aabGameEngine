
/**
*
*	gamepad_ball_event.cpp
*
**/

#include"gamepad_ball_event.hpp"
#include<sdl.h>
#include<cmath>
namespace aab	{
namespace events{



GamepadBallEvent::GamepadBallEvent (InternalEvent internalEvent) : Event (getClassEventType ())
{
	SDL_Event * event = static_cast <SDL_Event *> (internalEvent-> getReference ());

	id = event-> jball.which;
	ball = event-> jball.ball;
	xrel = event-> jball.xrel;
	yrel = event-> jball.yrel;
}


GamepadBallEvent::~GamepadBallEvent () throw ()
{
	// nothing //
}

int GamepadBallEvent::getGamePadId () const
{
	return id;
}

int GamepadBallEvent::getBallId () const
{
	return ball;
}

int16_t GamepadBallEvent::getRawXChange () const
{
	return xrel;
}

int16_t GamepadBallEvent::getRawYChange () const
{
	return yrel;
}

GamepadAxisValue GamepadBallEvent::getXChange () const
{
    return xrel;/*
	if (std::abs (xrel) < 10)
	{
		return 0;
	}

	return (static_cast <double> (xrel)) / 32768.0;;*/
}

GamepadAxisValue GamepadBallEvent::getYChange () const
{
    return yrel;/*
	if (std::abs (yrel) < 10)
	{
		return 0;
	}

	return (static_cast <double> (yrel)) / 32768.0;*/
}



EventType GamepadBallEvent::getClassEventType ()
{
	return gamepad_ball_event;
}

}		//	events
}		//	aab



