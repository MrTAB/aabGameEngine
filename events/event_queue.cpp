
/**
*
*	event_queue.cpp
*
*
**/

#include"event_queue.hpp"
#include<algorithm>
namespace aab	{
namespace events{
//using std::for_each;


// Make an internal Event class for dealing with SDL_Event.
// The individual Handlers should create the client events.


struct EventQueueClass::Data
{
	EventQueueClass::DispatcherList dispatchers;
	InternalEvent event;
};

EventQueue makeEventQueue (EventConnector::Ptr e)
{
	EventQueue ptr (new EventQueueClass(e), EventQueueClass::Deleter ());
	return ptr;
}

EventQueueClass::EventQueueClass (EventConnector::Ptr) : data (new Data ())
{
	data-> event = makeInternalEvent ();
}

EventQueueClass::~EventQueueClass ()
{
	// nothing //
}


void EventQueueClass::wait ()
{
	if (data-> event-> waitOn ())
	{
		notifyDispatchers (data-> event);
	}
	// note: error if returns 0.
}

bool EventQueueClass::poll ()
{
	if (data-> event-> pollOn ())
	{
		notifyDispatchers (data-> event);

		return true;
	}

	return false;
}

void EventQueueClass::notifyDispatchers (InternalEvent event)
{
	for (DispatcherList::iterator itr = data-> dispatchers.begin (); itr != data-> dispatchers.end(); ++itr)
	{
		(*itr)-> notify (event);
	}
}

void EventQueueClass::addDispatcher (EventDispatcher dispatcher)
{
	data-> dispatchers.push_back (dispatcher);
}

void EventQueueClass::removeDispatcher (EventDispatcher dispatcher)
{
	data-> dispatchers.remove (dispatcher);
}


void EventQueueClass::clearDispatchers ()
{
	data-> dispatchers.clear ();
}


}		//	events
}		//	aab



