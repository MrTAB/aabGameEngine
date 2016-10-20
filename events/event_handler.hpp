
/**
*
*	event_handler.hpp
*
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

