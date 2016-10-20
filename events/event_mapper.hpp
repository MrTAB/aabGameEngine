
/**
*
*	event_mapper.hpp
*
*	Maps InternalEvents to their EventTypes.
*	This class is used by dispatcher, and is not part of the API.
*	An extension may be to make the dispatchers have Ptr to a
*	global instance, and allow it to be swapped with a different
*	one such that event mapping may be modified.
*
**/

#if !defined(AAB_EVENTS_EVENT_MAPPER_CLASS)
#define AAB_EVENTS_EVENT_MAPPER_CLASS
#include"event.hpp"
#include"internal_event.hpp"
#include<map>
#include<memory>
#include<vector>
namespace aab	{
namespace events{

class EventMapper
{
	public:

		typedef InternalEventClass::Type InternalEventType;
		typedef std::vector <EventType> (* ConvertMethod)(InternalEvent);
		typedef std::map <InternalEventType, ConvertMethod> Map;
		typedef std::auto_ptr <Map> MapAutoPtr;

	private:

		static MapAutoPtr mapping;

	public:

	static std::vector <EventType> convert (InternalEvent);
};



}		//	events
}		//	aab
#endif	//	AAB_EVENTS_EVENT_MAPPER_CLASS

