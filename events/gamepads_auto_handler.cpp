
/**
*
*	gamepads_auto_handler.cpp
*
**/

#include"gamepads_auto_handler.hpp"
namespace aab	{
namespace events{


GamepadsAutoHandler::GamepadsAutoHandler (Gamepad pad)
{
	addGamepad (pad);
}

GamepadsAutoHandler::GamepadsAutoHandler ()
{
	// nothing //
}

GamepadsAutoHandler::~GamepadsAutoHandler () throw ()
{
	// nothing //
}


void GamepadsAutoHandler::addGamepad (Gamepad pad)
{
	pads [pad-> getId ()] = pad;
}

void GamepadsAutoHandler::clearGamepad (int id)
{
	pads.erase (id);
}

void GamepadsAutoHandler::clearGamepads ()
{
	pads.clear ();
}

GamepadsAutoHandler::Gamepad GamepadsAutoHandler::getGamepad (int id)
{
	return pads [id];
}


bool GamepadsAutoHandler::hasGamepad (int id) const
{
	return pads.find (id) != pads.end ();
}

int GamepadsAutoHandler::countGamepads () const
{
	return pads.size ();
}

void GamepadsAutoHandler::buttonPressed (int id, int button)
{
	PadMap::iterator itr = pads.find (id);

	if (itr != pads.end ())
	{
		itr-> second-> pressButton (button);
	}
}

void GamepadsAutoHandler::buttonReleased (int id, int button)
{
	PadMap::iterator itr = pads.find (id);

	if (itr != pads.end ())
	{
		itr-> second-> releaseButton (button);
	}
}

void GamepadsAutoHandler::axisMove (int id, int axis, GamepadAxisValue value)
{
	PadMap::iterator itr = pads.find (id);

	if (itr != pads.end ())
	{
		itr-> second-> setAxis (axis, value);
	}
}

void GamepadsAutoHandler::ballMove (int id, int ball, GamepadAxisValue xchange, GamepadAxisValue ychange)
{
	PadMap::iterator itr = pads.find (id);

	if (itr != pads.end ())
	{
		itr-> second-> setBall (ball, xchange, ychange);
	}
}

void GamepadsAutoHandler::hatMove (int id, int hat, HatPosition position)
{
	PadMap::iterator itr = pads.find (id);

	if (itr != pads.end ())
	{
		itr-> second-> setHat (hat, position);
	}
}



}		//	events
}		//	aab



