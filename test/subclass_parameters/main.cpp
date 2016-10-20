
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
	public:

	virtual ~EventHandler ()
	{
	};

	virtual void recieveMessage (shared_ptr <Event>) = 0;

	virtual EventType getEventType () = 0;
};

//this inbetween layer is the glue that does all the silly stuff.
template <class T_Event>
class EventHandlerGlue : public EventHandler
{
	public:

	void recieveMessage (shared_ptr <Event> e)
	{
		this-> handleEvent (dynamic_pointer_cast<T_Event> (e));
	}

	virtual void handleEvent (shared_ptr <T_Event>) = 0;

	EventType getEventType ()
	{
		return T_Event().getType ();
	}
};

typedef EventHandlerGlue <MouseButtonEvent> MouseButtonHandler;
typedef EventHandlerGlue <MouseMotionEvent> MouseMotionHandler;
typedef EventHandlerGlue <QuitEvent> QuitHandler;


class MyMouseMotionHandler : public MouseMotionHandler
{
	public:

	void handleEvent (shared_ptr <MouseMotionEvent> mme)
	{
		std::cout << "mouseMotionEvent:\t" << mme-> getCoord () << "\n";
	}
};

class MyMouseButtonHandler : public MouseButtonHandler
{
	public:

	void handleEvent (shared_ptr <MouseButtonEvent> mbe)
	{
		std::cout << "mouseButtonEvent:\t" << mbe-> getButton () << "\n";
	}
};


class MyQuitHandler : public QuitHandler
{
	public:

	void handleEvent (shared_ptr <QuitEvent> )
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













