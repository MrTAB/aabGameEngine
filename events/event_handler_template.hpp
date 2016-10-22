
/**
*
*	event_handler_template.hpp
*
*   This is an abstract Event Handler which maps InternalEvent data given to
*   recieveEvent (see EventHandler) onto handleEvent, which provides the more
*   useful EventData. This is used for elementary Event types which notify that
*   something has occurred. See event_handlers.hpp
**/

#if !defined(AAB_EVENTS_EVENT_HANDLER_TEMPLATE_CLASS)
#define AAB_EVENTS_EVENT_HANDLER_TEMPLATE_CLASS
#include"event_handler.hpp"
namespace aab	{
namespace events{


template <typename T_Event>
class EventHandlerTemplate : public EventHandler
{
	public:

	typedef T_Event EventData;

	virtual void handleEvent (const EventData) = 0;

	void recieveEvent (InternalEvent event)
	{
		this-> handleEvent (T_Event(event));
	}

	EventType getEventType ()
	{
		return T_Event::getClassEventType ();
	}

};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_EVENT_HANDLER_TEMPLATE_CLASS

