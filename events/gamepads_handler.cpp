
/**
*
*	gamepads_handler.cpp
*
**/

#include"gamepads_handler.hpp"
#include"event_handlers.hpp"
namespace aab	{
namespace events{

/*
GamepadsHandler::GamepadsHandler (GamepadHandler::Ptr handler, int id)
{
	setHandler (handler, id);
}

GamepadsHandler::GamepadsHandler ()
{
	// nothing //
}

GamepadsHandler::~GamepadsHandler () throw ()
{
	// nothing //
}


void GamepadsHandler::setHandler (GamepadHandler::Ptr handler, int id)
{
	handlersG [id] = handler;
}

void GamepadsHandler::clearHandler (int id)
{
	handlersG.erase (id);
}

void GamepadsHandler::clearHandlers ()
{
	handlersG.clear ();
}

GamepadHandler::Ptr GamepadsHandler::getHandler (int id)
{
	return handlersG [id];
}


bool GamepadsHandler::hasHandler (int id) const
{
	return handlersG.find (id) != handlersG.end ();
}

int GamepadsHandler::countHandlers () const
{
	return handlersG.size ();
}

void GamepadsHandler::buttonPressed (int id, int button)
{
	HandlerMap::iterator itr = handlersG.find (id);

	if (itr != handlersG.end ())
	{
		itr-> second-> buttonPressed (button);
	}
}

void GamepadsHandler::buttonReleased (int id, int button)
{
	HandlerMap::iterator itr = handlersG.find (id);

	if (itr != handlersG.end ())
	{
		itr-> second-> buttonReleased (button);
	}
}

void GamepadsHandler::axisMove (int id, int axis, double value)
{
	HandlerMap::iterator itr = handlersG.find (id);

	if (itr != handlersG.end ())
	{
		itr-> second-> axisMove (axis, value);
	}
}

void GamepadsHandler::ballMove (int id, int ball, double xchange, double ychange)
{
	HandlerMap::iterator itr = handlersG.find (id);

	if (itr != handlersG.end ())
	{
		itr-> second-> ballMove (ball, xchange, ychange);
	}
}

void GamepadsHandler::hatMove (int id, int hat, HatPosition position)
{
	HandlerMap::iterator itr = handlersG.find (id);

	if (itr != handlersG.end ())
	{
		itr-> second-> hatMove (hat, position);
	}
}
*/


}		//	events
}		//	aab



