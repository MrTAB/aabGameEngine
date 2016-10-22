
/**
*
*	event_connector.hpp
*
*	An EventConnector represents an object which prepares the events subsystem.
*   Thus event queues demand an eventconnector subclass be established in order to be
*   instantiated. visen::Screen is an example of such a subclass.
*
*	EventConnector is noncopy-constuctable.
**/

#if !defined(AAB_EVENTS_EVENT_CONNECTOR_CLASS)
#define AAB_EVENTS_EVENT_CONNECTOR_CLASS
#include"imports.hpp"
namespace aab	{
namespace events{


class EventConnector
{
	private:

		EventConnector (EventConnector&){};

	protected:

		explicit EventConnector () {};
		virtual ~EventConnector()// throw () {};
		{}

	public:

	typedef aab::types::Smart <EventConnector>::Ptr Ptr;

};




}		//	events
}		//	aab
#endif	//	AAB_EVENTS_EVENT_CONNECTOR_CLASS

