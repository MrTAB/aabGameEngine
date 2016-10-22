
/**
*
*	multi_event_handler.hpp
*
*   Multi event handlers allow several handlers of related function to be
*   fused together. This is useful where a single class wishes to be notified
*   via callbacks of those events, and collect information about them together,
*   For example to build a complete set of persistent keyboard state information
*   from just key events.
**/


#if !defined(AAB_EVENTS_MULTI_EVENT_HANDLER_CLASS)
#define AAB_EVENTS_MULTI_EVENT_HANDLER_CLASS
#include"event_type.hpp"
#include"event_handler.hpp"
#include"imports.hpp"
#include<list>
#include<map>
namespace aab	{
namespace events{


class MultiEventHandler : public EventHandler
{
	private:

		//typedef std::map <EventType, EventHandler::Ptr> HandlerMap ;

		//HandlerMap handlers;
		
    public:
		typedef std::list<EventHandler::Ptr> HandlerList;
		
		HandlerList handlers;

	protected:

		//void setHandler (EventType, EventHandler::Ptr);
		void setHandler (EventHandler::Ptr);

	public:

	typedef aab::types::Smart <MultiEventHandler>::Ptr Ptr;

	explicit MultiEventHandler ();
	virtual ~MultiEventHandler () throw ();

	std::list <EventType> getTypeList () const;
	//EventHandler::Ptr getHandler (EventType);

	virtual void recieveEvent (InternalEvent); // is blank
	
	EventType getEventType (); // returns null event
	
	HandlerList const* getHandlerList() { return &handlers; }
	
	//final:
	bool isMultiHandler () const; // always true


};




}		//	events
}		//	aab
#endif	//	AAB_EVENTS_MULTI_EVENT_HANDLER_CLASS

