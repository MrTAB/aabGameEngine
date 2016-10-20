
/**
*
*	gamepad_port_handler.cpp
*
**/

#include"gamepad_port_handler.hpp"
#include"event_handlers.hpp"
namespace aab	{
namespace events{



class GamepadPortHandler::PressedEventHandler : public GamepadButtonDownHandler
{
	GamepadPortHandler &owner;

	public:

	explicit PressedEventHandler (GamepadPortHandler &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData pads)
	{
		owner.buttonPressed (pads.getGamePadId (), pads.getButton ());
	}
};

class GamepadPortHandler::ReleasedEventHandler : public GamepadButtonUpHandler
{
	GamepadPortHandler &owner;

	public:

	explicit ReleasedEventHandler (GamepadPortHandler &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData pads)
	{
		owner.buttonReleased (pads.getGamePadId (), pads.getButton ());
	}
};

class GamepadPortHandler::AxisHandler : public GamepadAxisHandler
{
	GamepadPortHandler &owner;

	public:

	explicit AxisHandler (GamepadPortHandler &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData pads)
	{
		owner.axisMove (pads.getGamePadId (), pads.getWhichAxis (), pads.getAxisValue ());
	}
};

class GamepadPortHandler::BallHandler : public GamepadBallHandler
{
	GamepadPortHandler &owner;

	public:

	explicit BallHandler (GamepadPortHandler &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData pads)
	{
		owner.ballMove (pads.getGamePadId (), pads.getBallId (), pads.getXChange (), pads.getYChange ());
	}
};

class GamepadPortHandler::HatHandler : public GamepadHatHandler
{
	GamepadPortHandler &owner;

	public:

	explicit HatHandler (GamepadPortHandler &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData pads)
	{
		owner.hatMove (pads.getGamePadId (), pads.getHatId (), pads.getHatPosition ());
	}
};


GamepadPortHandler::GamepadPortHandler ()
{

	EventHandler::Ptr pressedHandler (new PressedEventHandler (*this));
	EventHandler::Ptr releasedHandler (new ReleasedEventHandler (*this));
	EventHandler::Ptr axisHandler (new AxisHandler (*this));
	EventHandler::Ptr ballHandler (new BallHandler (*this));
	EventHandler::Ptr hatHandler (new HatHandler (*this));

	setHandler (pressedHandler);
	setHandler (releasedHandler);
	setHandler (axisHandler);
	setHandler (ballHandler);
	setHandler (hatHandler);
}


GamepadPortHandler::~GamepadPortHandler () throw ()
{
	// nothing //
}


void GamepadPortHandler::buttonPressed (int, int)
{
	// nothing //
}


void GamepadPortHandler::buttonReleased (int, int)
{
	// nothing //
}


void GamepadPortHandler::axisMove (int, int, GamepadAxisValue)
{
	// nothing //
}


void GamepadPortHandler:: ballMove (int, int, GamepadAxisValue, GamepadAxisValue)
{
	// nothing //
}


void GamepadPortHandler::hatMove (int, int, HatPosition)
{
	// nothing //
}




}		//	events
}		//	aab



