
/**
*
*	internal_event.hpp
*
*	NOT a type of event. Rather event data for any type
*	of event before conversion to a specific event.
*
**/

#if !defined(AAB_EVENTS_INTERNAL_EVENT_CLASS)
#define AAB_EVENTS_INTERNAL_EVENT_CLASS
#include"event_type.hpp"
#include"imports.hpp"
#include<memory>
namespace aab	{
namespace events{


class InternalEventClass : public aab::types::Manager <InternalEventClass>
{
	public:

	typedef aab::types::Smart <InternalEventClass>::Ptr Ptr;
	typedef aab::types::Manager <InternalEventClass> SuperClass;

	private:

		struct Data;
		const std::auto_ptr <Data> data;

	protected:

		friend class SuperClass::Deleter;
		friend Ptr makeInternalEvent (); // No need
		explicit InternalEventClass ();
		virtual ~InternalEventClass ();

	public:

	typedef unsigned int Type;

	void * getReference ();
	bool waitOn ();
	bool pollOn ();

	int getType () const;

};

typedef InternalEventClass::Ptr InternalEvent;

InternalEvent makeInternalEvent ();


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_INTERNAL_EVENT_CLASS

