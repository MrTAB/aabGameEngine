
/**
*
*	mouse_button_down_event.hpp
*
**/
/* NOT REMOVED */
//#if 0
#if !defined(AAB_EVENTS_MOUSE_BUTTON_DOWN_EVENT_CLASS)
#define AAB_EVENTS_MOUSE_BUTTON_DOWN_EVENT_CLASS
#include"event.hpp"
#include"internal_event.hpp"
#include"imports.hpp"
#include"../types/smart_ptr.hpp"
namespace aab	{
namespace events{


class MouseButtonDownEvent : public Event
{
	private:

		int button;
		int x, y;

	public:

	typedef aab::types::Smart <MouseButtonDownEvent>::Ptr Ptr;

	explicit MouseButtonDownEvent (InternalEvent e);
	virtual ~MouseButtonDownEvent () throw ();

	int getButton () const;
	int getX () const;
	int getY () const;

	static EventType getClassEventType ();
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_MOUSE_BUTTON_DOWN_EVENT_CLASS
//#endif
