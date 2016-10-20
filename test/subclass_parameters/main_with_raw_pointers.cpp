
#include<iostream>
#include<list>
#include<algorithm>
#include<string>
#include<sstream>
#include<map>


using std::string;

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

	MouseMotionEvent (int x, int y) : Event (mouse_motion_event), x(x), y(y)
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

	explicit MouseButtonEvent (int button) : Event (mouse_button_event), button (button)
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

	EventHandler ()
	{
	}

	virtual ~EventHandler ()
	{
	};

	virtual void recieveMessage (Event *)
	{
		std::cout << "\tEventHandler::recieveMessage\n";
	}

};

class MouseHandler : public EventHandler
{
	public:

	void recieveMessage (Event * e)
	{
		switch (e-> getType ())
		{
			case mouse_motion_event:
			{
				this-> mouseMotionEvent ((MouseMotionEvent *) e);
			}
			break;

			case mouse_button_event:
			{
				this-> mouseButtonEvent ((MouseButtonEvent *) e);
			}
			break;

			default:
			{
				break;
			}
		}

	}

	virtual void mouseMotionEvent (MouseMotionEvent *) = 0;
	virtual void mouseButtonEvent (MouseButtonEvent *) = 0;
};

class QuitHandler : public EventHandler
{
	public:

	void recieveMessage (Event * e)
	{
		this-> quitEvent ((QuitEvent *) e);
	}

	virtual void quitEvent (QuitEvent *) = 0;
};



class MyMouseHandler : public MouseHandler
{
	public:

	void mouseMotionEvent (MouseMotionEvent * mme)
	{
		std::cout << "mouseMotionEvent:\t" << mme-> getCoord () << "\n";
	}

	void mouseButtonEvent (MouseButtonEvent * mbe)
	{
		std::cout << "mouseButtonEvent:\t" << mbe-> getButton () << "\n";
	}
};


class MyQuitHandler : public QuitHandler
{
	public:

	void quitEvent (QuitEvent *)
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

	list <Event *> eventQueue;
	map <EventType, EventHandler*> dispatcher;

	eventQueue.push_back (new MouseMotionEvent (40, 20));
	eventQueue.push_back (new MouseMotionEvent (10, 17));
	eventQueue.push_back (new MouseButtonEvent (5));
	eventQueue.push_back (new MouseMotionEvent (-1010, 97));
	eventQueue.push_back (new QuitEvent ());
	eventQueue.push_back (new MouseButtonEvent (3));
	eventQueue.push_back (new QuitEvent ());
	eventQueue.push_back (new MouseButtonEvent (6));
	eventQueue.push_back (new MouseButtonEvent (-15));
	eventQueue.push_back (new QuitEvent ());

	dispatcher[mouse_motion_event] = new MyMouseHandler ();
	dispatcher[mouse_button_event] = new MyMouseHandler ();
	dispatcher[quit_event] = new MyQuitHandler ();

	while (! eventQueue.empty())
	{
		Event * event = eventQueue.front ();
		eventQueue.pop_front ();

		EventHandler * handler = dispatcher [event-> getType()];

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













