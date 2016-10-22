
/**
*
*	event_handler.hpp
*
*   Basic Event Handler, which will recieve callbacks via recieveEvent when
*   its event pops up and is handed to a Dispatcher in which the handler is
*   registered. These EventHandlers are a base used by EventHandlerTemplate,
*   which provides EventType information and can be instantiated or implemented
*   by the client - see EventHandlerTemplate
*
**/

#if !defined(AAB_EVENTS_EVENT_HANDLER_CLASS)
#define AAB_EVENTS_EVENT_HANDLER_CLASS
#include"event_type.hpp"
#include"internal_event.hpp"
#include"imports.hpp"
namespace aab	{
namespace events{


class EventHandler
{
	public:

	typedef aab::types::Smart <EventHandler>::Ptr Ptr;

	explicit EventHandler () {};
	virtual ~EventHandler () throw () {};

	virtual void recieveEvent (InternalEvent) = 0;
	virtual EventType getEventType () = 0;

	virtual bool isMultiHandler () const
	{
		return false;
	}

};



}		//	events
}		//	aab
#endif	//	AAB_EVENTS_EVENT_HANDLER_CLASS

