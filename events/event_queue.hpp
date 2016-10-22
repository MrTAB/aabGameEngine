
/**
*
*	event_queue.hpp
*
*   The EventQueue processes events with either wait() or poll() depending on
    wether you want to wait on an event to occur (desktop application) or poll
    for events while ploughing through your main loop (computer game).
    
    Supply a dispatcher to the eventqueue and the dispatcher will be notified of
    any events in the queue.
    
    Thus to set up event handling:
    
    1) Implement event handlers that you wish to use, or crate instances of event
    handling objects that you wish to use.
    2) Plug these into an instance of Dispatcher
    3) Plug this Dispatcher into an EventQueue
    4) poll the EventQueue each loop. Now your handlers will be notified of any
    events relevant to them.
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

