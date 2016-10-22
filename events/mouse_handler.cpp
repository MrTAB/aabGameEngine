
/**
*
*	mouse_handler.cpp
*
**/

/* REMOVED  - PUT BACK IN FOR TESTING*/
//#if 0
#include"mouse_handler.hpp"
#include"event_handlers.hpp"
namespace aab	{
namespace events{


class MouseHandler::MovedEventHandler : public MouseMoveHandler
{
	MouseHandler &owner;

	public:

	explicit MovedEventHandler (MouseHandler &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData mouse)
	{
		owner.moved (mouse.getX (), mouse.getY (), mouse.getXChange (), mouse.getYChange ());
	}
};


class MouseHandler::PressedEventHandler : public MouseButtonDownHandler
{
	MouseHandler &owner;

	public:

	explicit PressedEventHandler (MouseHandler &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData mouse)
	{
		owner.buttonPressed (mouse.getButton (), mouse.getX (), mouse.getY ());
	}
};


class MouseHandler::ReleasedEventHandler : public MouseButtonUpHandler
{
	MouseHandler &owner;

	public:

	explicit ReleasedEventHandler (MouseHandler &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData mouse)
	{
		owner.buttonReleased (mouse.getButton (), mouse.getX (), mouse.getY ());
	}
};

class MouseHandler::FocusGainedHandler : public MouseFocusGainedHandler
{
	MouseHandler &owner;

	public:

	explicit FocusGainedHandler (MouseHandler &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData)
	{
		owner.focusGained ();
	}
};


class MouseHandler::FocusLostHandler : public MouseFocusLostHandler
{
	MouseHandler &owner;

	public:

	explicit FocusLostHandler (MouseHandler &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData)
	{
		owner.focusLost ();
	}
};



MouseHandler::MouseHandler ()
{
	EventHandler::Ptr movedHandler (new MovedEventHandler (*this));
	EventHandler::Ptr pressedHandler (new PressedEventHandler (*this));
	EventHandler::Ptr releasedHandler (new ReleasedEventHandler (*this));
	EventHandler::Ptr focusGainedHandler (new FocusGainedHandler (*this));
	EventHandler::Ptr focusLostHandler (new FocusLostHandler (*this));

	setHandler (movedHandler);
	setHandler (pressedHandler);
	setHandler (releasedHandler);
	setHandler (focusGainedHandler);
	setHandler (focusLostHandler);
}


MouseHandler::~MouseHandler () throw ()
{
	// nothing //
}

void MouseHandler::moved (int, int, int, int)
{
	// nothing //
}

void MouseHandler::buttonPressed (int, int, int)
{
	// nothing //
}

void MouseHandler::buttonReleased (int, int, int)
{
	// nothing //
}

void MouseHandler::focusGained ()
{
	// nothing //
}

void MouseHandler::focusLost ()
{
	// nothing //
}


}		//	events
}		//	aab



//#endif
