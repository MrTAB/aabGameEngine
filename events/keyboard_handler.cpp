
/**
*
*	keyboard_handler.cpp
*
**/

#include"keyboard_handler.hpp"
#include"event_handlers.hpp"
namespace aab	{
namespace events{


class KeyboardHandler::PressedEventHandler : public KeyDownHandler
{
	KeyboardHandler &owner;

	public:

	PressedEventHandler (KeyboardHandler &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData key)
	{
		owner.setKeyEvent (key);
		owner.keyPressed (key.getKeyCode ());
	}
};


class KeyboardHandler::ReleasedEventHandler : public KeyUpHandler
{
	KeyboardHandler &owner;

	public:

	ReleasedEventHandler (KeyboardHandler &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData key)
	{
		owner.setKeyEvent (key);
		owner.keyReleased (key.getKeyCode ());
	}
};

class KeyboardHandler::FocusGainedHandler : public KeyboardFocusGainedHandler
{
	KeyboardHandler &owner;

	public:

	FocusGainedHandler (KeyboardHandler &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData)
	{
		owner.focusGained ();
	}
};


class KeyboardHandler::FocusLostHandler : public KeyboardFocusLostHandler
{
	KeyboardHandler &owner;

	public:

	FocusLostHandler (KeyboardHandler &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData)
	{
		owner.focusLost ();
	}
};



KeyboardHandler::KeyboardHandler () : keyEvent (0, aab::input::key_a, 0, 0)
{
	EventHandler::Ptr pressedHandler (new PressedEventHandler (*this));
	EventHandler::Ptr releasedHandler (new ReleasedEventHandler (*this));
	EventHandler::Ptr focusGainedHandler (new FocusGainedHandler (*this));
	EventHandler::Ptr focusLostHandler (new FocusLostHandler (*this));

	setHandler (pressedHandler);
	setHandler (releasedHandler);
	setHandler (focusGainedHandler);
	setHandler (focusLostHandler);
}


KeyboardHandler::~KeyboardHandler () throw ()
{
	// nothing //
}

void KeyboardHandler::keyPressed (KeyCode)
{
	// nothing //
}

void KeyboardHandler::keyReleased (KeyCode)
{
	// nothing //
}

void KeyboardHandler::focusGained ()
{
	// nothing //
}

void KeyboardHandler::focusLost ()
{
	// nothing //
}

void KeyboardHandler::setKeyEvent (KeyEvent keyEvent)
{
	this-> keyEvent = keyEvent;
}

std::string KeyboardHandler::getKeyName (KeyCode key)
{
	return aab::input::getKeyName (key);
}


}		//	events
}		//	aab



