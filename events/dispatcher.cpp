
/**
*
*	dispatcher.cpp
*
*
**/

#include"dispatcher.hpp"
#include"event_mapper.hpp"
#include<algorithm>
#include<iostream>
namespace aab	{
namespace events{
using std::for_each;
using std::vector;

class HandlerNotifier
{
	private:

		InternalEvent event;

	public:

	explicit HandlerNotifier (InternalEvent event) : event (event)
	{
	}

	void operator () (EventHandler::Ptr handler)
	{
		handler-> recieveEvent (event);
	}
};


class HandlerListNotifier
{
	typedef DispatcherClass::DispatcherMap DispatcherMap;
	typedef DispatcherClass::HandlerList HandlerList;

	InternalEvent &event;
	DispatcherMap& dispatcher;

	public:

	HandlerListNotifier (InternalEvent &event, DispatcherMap &dispatcher):
		event (event),
		dispatcher (dispatcher)
	{
		// nothing //
	}

	void operator () (EventType eventType)
	{
		HandlerList * handlers = dispatcher [eventType];

		if (handlers)
		{
			for_each (handlers-> begin(), handlers-> end(), HandlerNotifier (event));
		}
	}
};



Dispatcher makeDispatcher ()
{
	Dispatcher ptr (new DispatcherClass (), DispatcherClass::Deleter ());
	return ptr;
}

DispatcherClass::DispatcherClass ()
{
	// nothing //
}

DispatcherClass::~DispatcherClass ()
{
	clearHandlers ();
}


void DispatcherClass::notify (InternalEvent event)
{
	vector <EventType> events = EventMapper::convert (event);

	for_each (events.begin (), events.end(), HandlerListNotifier (event, dispatcher));
}

void DispatcherClass::addHandler (EventHandler::Ptr handler)
{
	if (handler-> isMultiHandler ())
	{
		//typedef std::list <EventType> TypeList;
		//typedef TypeList::iterator iterator;

		MultiEventHandler::Ptr multiHandler = boost::dynamic_pointer_cast <MultiEventHandler> (handler);

        /*
		TypeList types = multiHandler-> getTypeList ();

		for (iterator itr = types.begin (); itr != types.end (); ++itr)
		{
			addHandler (multiHandler-> getHandler (*itr));
		}*/
		
		MultiEventHandler::HandlerList * handlers = multiHandler->getHandlerList();
		typedef MultiEventHandler::HandlerList::const_iterator iterator;
		for(iterator itr=handlers->begin();itr!=handlers->end();++itr)
		{
		    addHandler(*itr);
		}
		
		//got to keep this around!
		multiEventHandlerList.push_back(multiHandler);
	}
	else
	{
		addExplicitHandler (handler);
	}
}

void DispatcherClass::addHandler (EventHandler::Ptr handler, EventType type)
{
	if (handler-> isMultiHandler ())
	{
	    MultiEventHandler::Ptr multiHandler = boost::dynamic_pointer_cast <MultiEventHandler> (handler);

		/*
		typedef std::list <EventType> TypeList;
		typedef TypeList::iterator iterator;

		

		TypeList types = multiHandler-> getTypeList ();

		for (iterator itr = types.begin (); itr != types.end (); ++itr)
		{
			addHandler (multiHandler-> getHandler (*itr), type);
		}*/
		
		MultiEventHandler::HandlerList * handlers = multiHandler->getHandlerList();
		typedef MultiEventHandler::HandlerList::const_iterator iterator;
		for(iterator itr=handlers->begin();itr!=handlers->end();++itr)
		{
		    addHandler(*itr, type);
		}
	}
	else
	{
		addExplicitHandler (handler, type);
	}
}

void DispatcherClass::addExplicitHandler (EventHandler::Ptr handler)
{
	addExplicitHandler (handler, handler-> getEventType ());
}

void DispatcherClass::addExplicitHandler (EventHandler::Ptr handler, EventType type)
{
	HandlerList * handlers = dispatcher [type];

	if (! handlers)
	{
		handlers = new HandlerList ();
		dispatcher [type] = handlers;
	}

	handlers-> push_front (handler);
}

void DispatcherClass::removeHandler (EventHandler::Ptr handler)
{
	typedef std::list <EventType> KeyList;
	KeyList removables;

	for (DispatcherMap::iterator itr = dispatcher.begin();
			itr != dispatcher.end();
			++itr)
	{

		HandlerList * handlers = itr-> second;

		handlers-> remove (handler);

		if (handlers-> empty ())
		{
			removables.push_back (itr-> first);
		}
	}

	//for_each (dispatcher.begin (), dispatcher.end (), HandlerRemover (handler, removables));

	for (KeyList::iterator itr = removables.begin(); itr != removables.end(); ++itr)
	{
		delete dispatcher [*itr];
		dispatcher [*itr] = NULL;
	}

	//for_each (removables.begin(), removables.end(), EmptyHandlersRemover (dispatcher, removables));
}


void DispatcherClass::clearHandlers ()
{
	for (	DispatcherMap::iterator itr = dispatcher.begin();
			itr != dispatcher.end();
			++itr)
	{
		delete itr-> second;
		itr-> second = NULL;
	}

	//for_each (dispatcher.begin(), dispatcher.end(), AllHandlersRemover ());

	dispatcher.clear ();
}

void DispatcherClass::clearHandlersFor (Event event)
{
	clearHandlersFor (event.getType ());
}

void DispatcherClass::clearHandlersFor (EventType type)
{
	HandlerList * handlers = dispatcher[type];

	if (handlers)
	{
		delete dispatcher[type];
		dispatcher[type] = NULL;
	}
}

}		//	events
}		//	aab



