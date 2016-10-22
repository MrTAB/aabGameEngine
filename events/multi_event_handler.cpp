
/**
*
*	multi_event_handler.cpp
*
**/

#include"multi_event_handler.hpp"
#include<algorithm>
namespace aab	{
namespace events{


class InsertKey
{
	std::list <EventType> &list;

	public:

	InsertKey (std::list <EventType> &list) : list (list)
	{
		// nothing //
	}

	//void operator () (std::pair <EventType, EventHandler::Ptr> pair)
	void operator () (EventHandler::Ptr handler)
	{
		//list.push_back (pair.first);
		list.push_back (handler->getEventType());
	}
};



MultiEventHandler::MultiEventHandler ()
{
	// nothing //
}

MultiEventHandler::~MultiEventHandler () throw ()
{
	// nothing //
}


//void MultiEventHandler::setHandler (EventType eventType, EventHandler::Ptr handler)
void MultiEventHandler::setHandler (EventHandler::Ptr handler)
{
	//handlers [eventType] = handler;
	handlers.push_front(handler);
}


std::list <EventType> MultiEventHandler::getTypeList () const
{
	std::list <EventType> eventTypes;

	//std::for_each (handlers.begin (), handlers.end (), InsertKey (eventTypes));
	std::for_each (handlers.begin (), handlers.end (), InsertKey (eventTypes));

	return eventTypes;
}

/*
EventHandler::Ptr MultiEventHandler::getHandler (EventType type)
{
	return handlers[type];
}
*/

void MultiEventHandler::recieveEvent (InternalEvent)
{
	// nothing //
}

EventType MultiEventHandler::getEventType ()
{
	return null_event;
}

bool MultiEventHandler::isMultiHandler () const
{
	return true;
}


}		//	events
}		//	aab



