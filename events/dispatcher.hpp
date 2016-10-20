
/**
*
*	dispatcher.hpp
*
*
**/

#if !defined(AAB_EVENTS_DISPATCHER_CLASS)
#define AAB_EVENTS_DISPATCHER_CLASS
#include"event.hpp"
#include"event_type.hpp"
#include"internal_event.hpp"
#include"event_handler.hpp"
#include"multi_event_handler.hpp"
#include"imports.hpp"
#include<map>
#include<list>
namespace aab	{
namespace events{


class DispatcherClass : public aab::types::Manager <DispatcherClass>
{
	public:

	typedef aab::types::Smart <DispatcherClass>::Ptr Ptr;
	typedef aab::types::Manager <DispatcherClass> SuperClass;
	typedef std::list<EventHandler::Ptr> HandlerList;
	typedef std::map<EventType, HandlerList *> DispatcherMap;
	typedef std::list<MultiEventHandler::Ptr> MultiEventHandlerList;

	private:

		DispatcherMap  dispatcher;
		MultiEventHandlerList multiEventHandlerList; // these are needed to maintain a reference count for the actual multieventhandler!

	protected:

		friend class SuperClass::Deleter;
		friend Ptr makeDispatcher ();
		explicit DispatcherClass ();
		virtual ~DispatcherClass ();

	public:

		void notify (InternalEvent);
		void addHandler (EventHandler::Ptr);
		void addHandler (EventHandler::Ptr, EventType);
		void addExplicitHandler (EventHandler::Ptr);
		void addExplicitHandler (EventHandler::Ptr, EventType);
		void removeHandler (EventHandler::Ptr);

		void clearHandlers ();
		void clearHandlersFor (Event);
		void clearHandlersFor (EventType);

};

typedef DispatcherClass::Ptr Dispatcher;
typedef Dispatcher EventDispatcher;

Dispatcher makeDispatcher ();


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_DISPATCHER_CLASS

