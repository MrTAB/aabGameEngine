
/**
*
*	event_handler_template.hpp
*
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

