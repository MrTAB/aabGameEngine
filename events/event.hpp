
/**
*
*	event.hpp
*
*	Event class.
*
**/

#if !defined(AAB_EVENTS_EVENT_CLASS)
#define AAB_EVENTS_EVENT_CLASS
#include"internal_event.hpp"
#include"imports.hpp"
#include"../input/gamepad_values.hpp"
namespace aab	{
namespace events{


typedef aab::input::GamepadAxisValue GamepadAxisValue;

class Event
{
	public:

	typedef aab::types::Smart <Event>::Ptr Ptr;

	private:

		EventType type;

	protected:

		explicit Event (const EventType);
		virtual ~Event () throw ();

	public:

	EventType getType () const;

};



}		//	events
}		//	aab
#endif	//	AAB_EVENTS_EVENT_CLASS

