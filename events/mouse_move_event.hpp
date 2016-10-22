
/**
*
*	mouse_move_event.hpp
*
**/
/*NOT REMOVED */
//#if 0
#if !defined(AAB_EVENTS_MOUSE_MOVE_EVENT_CLASS)
#define AAB_EVENTS_MOUSE_MOVE_EVENT_CLASS
#include"event.hpp"
#include"internal_event.hpp"
#include"imports.hpp"
#include"../input/mouse_data.hpp"
#include"../types/smart_ptr.hpp"
namespace aab	{
namespace events{


class MouseMoveEvent : public Event, public aab::input::MouseDataClass
{
	public:

	typedef aab::types::Smart <MouseMoveEvent>::Ptr Ptr;

	explicit MouseMoveEvent (InternalEvent e);
	virtual ~MouseMoveEvent () throw ();

	static EventType getClassEventType ();
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_MOUSE_MOVE_EVENT_CLASS
//#endif
