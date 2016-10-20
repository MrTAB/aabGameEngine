
/**
*
*	event_queue.hpp
*
*
**/

#if !defined(AAB_EVENTS_EVENT_QUEUE_CLASS)
#define AAB_EVENTS_EVENT_QUEUE_CLASS
#include"event_type.hpp"
#include"internal_event.hpp"
#include"event.hpp"
#include"event_handler.hpp"
#include"event_connector.hpp"
#include"dispatcher.hpp"
#include"imports.hpp"
#include<list>
namespace aab	{
namespace events{


class EventQueueClass : public aab::types::Manager <EventQueueClass>
{
	public:

	typedef aab::types::Smart <EventQueueClass>::Ptr Ptr;
	typedef aab::types::Manager <EventQueueClass> SuperClass;
	typedef std::list <EventDispatcher> DispatcherList;

	private:

		struct Data;
		const std::auto_ptr <Data> data;

	protected:

		friend class SuperClass::Deleter;
		friend Ptr makeEventQueue (EventConnector::Ptr);
		explicit EventQueueClass (EventConnector::Ptr);
		virtual ~EventQueueClass ();

		void notifyDispatchers (InternalEvent);

	public:

		void wait ();
		bool poll ();

		void addDispatcher (EventDispatcher);
		void removeDispatcher (EventDispatcher);

		void clearDispatchers ();
};

typedef EventQueueClass::Ptr EventQueue;

EventQueue makeEventQueue (EventConnector::Ptr);


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_EVENT_QUEUE_CLASS

