
/**
*
*	key_down_event.hpp
*
**/

#if !defined(AAB_EVENTS_KEY_DOWN_EVENT_CLASS)
#define AAB_EVENTS_KEY_DOWN_EVENT_CLASS
#include"key_event.hpp"
namespace aab	{
namespace events{


class KeyDownEvent : public KeyEvent
{
	public:

	typedef aab::types::Smart <KeyDownEvent>::Ptr Ptr;

	explicit KeyDownEvent (InternalEvent e);
	virtual ~KeyDownEvent () throw ();

	static EventType getClassEventType ();
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_KEY_DOWN_EVENT_CLASS

