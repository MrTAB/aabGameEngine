
/**
*
*	empty_event.hpp - EmptyEvent is used in some scenarios to define non
*   abstract events of particular types without any default behaviour associated
*   with the event.
*
**/

#if !defined(AAB_EVENTS_EMPTY_EVENT_CLASS)
#define AAB_EVENTS_EMPTY_EVENT_CLASS
#include"event.hpp"
#include"internal_event.hpp"
#include"imports.hpp"
namespace aab	{
namespace events{

template <const EventType const_EventType>
class EmptyEvent : public Event
{
	public:

	//typedef aab::types::Smart <EmptyEvent>::Ptr Ptr;

	explicit EmptyEvent (InternalEvent) : Event (getClassEventType ())
	{
		// nothing //
	}

	virtual ~EmptyEvent () throw ()
	{
		// nothing //
	}

	static EventType getClassEventType ()
	{
		return const_EventType;
	}
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_EMPTY_EVENT_CLASS

