
#include"../../utility/smart_ptr.hpp"
#include<iostream>
#include<list>
#include<algorithm>
#include<string>
#include<sstream>
#include<map>


using std::string;
using boost::shared_ptr;
using boost::dynamic_pointer_cast;

enum EventType
{
	no_event,
	mouse_motion_event,
	mouse_button_event,
	quit_event
};

class Event
{
	private:

		const EventType type;

	public:

	explicit Event (EventType type) : type (type)
	{
	}

	virtual ~Event ()
	{
	}

	EventType getType ()
	{
		return type;
	}
};

class MouseMotionEvent : public Event
{
	private:

		int x, y;

	public:

	MouseMotionEvent (int x = 0, int y = 0) : Event (mouse_motion_event), x(x), y(y)
	{
	}

	string getCoord ()
	{
		std::ostringstream ss;
		ss << "coord (" << x << "," << y << ")";
		return ss.str();
	}
};

class MouseButtonEvent : public Event
{
	private:

		int button;

	public:

	explicit MouseButtonEvent (int button = 0) : Event (mouse_button_event), button (button)
	{
	}

	string getButton ()
	{
		std::ostringstream ss;
		ss << "button " << button;
		return ss.str ();
	}
};


class QuitEvent : public Event
{
	public:

	QuitEvent () : Event (quit_event)
	{
	}
};


class EventHandler
{
	private:

		EventType type;

	public:

	EventHandler (Event event) : type (event.getType ())
	{
	}

	virtual ~EventHandler ()
	{
	};

	virtual void recieveMessage (shared_ptr <Event>) = 0;

	EventType getEventType ()
	{
		return type;
	}

};

class MouseButtonHandler : public EventHandler
{
	public:

	MouseButtonHandler () : EventHandler (MouseButtonEvent())
	{
	}

	void recieveMessage (shared_ptr <Event> e)
	{
		this-> mouseButtonEvent (dynamic_pointer_cast<MouseButtonEvent> (e));
	}

	virtual void mouseButtonEvent (shared_ptr <MouseButtonEvent>) = 0;
};

class MouseMotionHandler : public EventHandler
{
	public:

	MouseMotionHandler () : EventHandler (MouseMotionEvent())
	{
	}

	void recieveMessage (shared_ptr <Event> e)
	{
		this-> mouseMotionEvent (dynamic_pointer_cast<MouseMotionEvent> (e));
	}

	virtual void mouseMotionEvent (shared_ptr <MouseMotionEvent>) = 0;
};

class QuitHandler : public EventHandler
{
	public:

	QuitHandler () : EventHandler (QuitEvent())
	{
	}

	void recieveMessage (shared_ptr <Event> e)
	{
		this-> quitEvent ( dynamic_pointer_cast<QuitEvent> (e));
	}

	virtual void quitEvent (shared_ptr <QuitEvent>) = 0;
};



class MyMouseMotionHandler : public MouseMotionHandler
{
	public:

	void mouseMotionEvent (shared_ptr <MouseMotionEvent> mme)
	{
		std::cout << "mouseMotionEvent:\t" << mme-> getCoord () << "\n";
	}
};

class MyMouseButtonHandler : public MouseButtonHandler
{
	public:

	void mouseButtonEvent (shared_ptr <MouseButtonEvent> mbe)
	{
		std::cout << "mouseButtonEvent:\t" << mbe-> getButton () << "\n";
	}
};


class MyQuitHandler : public QuitHandler
{
	public:

	void quitEvent (shared_ptr <QuitEvent> )
	{
		std::cout << "quitEvent:\n";
	}
};



int main ()
{
	using std::cout;
	using std::list;
	using std::cin;
	using std::endl;
	using std::for_each;
	using std::map;

	list < shared_ptr <Event> > eventQueue;
	map <EventType, shared_ptr <EventHandler> > dispatcher;

	eventQueue.push_back (shared_ptr <MouseMotionEvent> (new MouseMotionEvent (40, 20)));
	eventQueue.push_back (shared_ptr <MouseMotionEvent> (new MouseMotionEvent (10, 17)));
	eventQueue.push_back (shared_ptr <MouseButtonEvent> (new MouseButtonEvent (5)));
	eventQueue.push_back (shared_ptr <MouseMotionEvent> (new MouseMotionEvent (-1010, 97)));
	eventQueue.push_back (shared_ptr <QuitEvent> (new QuitEvent ()));
	eventQueue.push_back (shared_ptr <MouseButtonEvent> (new MouseButtonEvent (3)));
	eventQueue.push_back (shared_ptr <QuitEvent> (new QuitEvent ()));
	eventQueue.push_back (shared_ptr <MouseButtonEvent> (new MouseButtonEvent (6)));
	eventQueue.push_back (shared_ptr <MouseButtonEvent> (new MouseButtonEvent (-15)));
	eventQueue.push_back (shared_ptr <QuitEvent> (new QuitEvent ()));


	shared_ptr<MyMouseMotionHandler> mouseMotionHandler (new MyMouseMotionHandler ());
	shared_ptr<MyMouseButtonHandler> mouseButtonHandler (new MyMouseButtonHandler ());
	shared_ptr<MyQuitHandler> quitHandler (new MyQuitHandler ());
	dispatcher[mouseMotionHandler-> getEventType ()] = mouseMotionHandler;
	dispatcher[mouseButtonHandler-> getEventType ()] = mouseButtonHandler;
	dispatcher[quitHandler-> getEventType ()] = quitHandler;


	while (! eventQueue.empty())
	{
		shared_ptr <Event> event = eventQueue.front ();
		eventQueue.pop_front ();

		shared_ptr <EventHandler> handler = dispatcher [event-> getType()];

		if (handler)
		{
			handler-> recieveMessage (event);
		}
		else
		{
			std::cout << "\t* b a d\t\te r r o r *\n";
		}
	}


	cin.get ();



	return 0;
}













