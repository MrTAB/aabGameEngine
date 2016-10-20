
/**
*
*	key_up_event.hpp
*
**/

#if !defined(AAB_EVENTS_KEY_UP_EVENT_CLASS)
#define AAB_EVENTS_KEY_UP_EVENT_CLASS
#include"key_event.hpp"
namespace aab	{
namespace events{


class KeyUpEvent : public KeyEvent
{
	public:

	typedef aab::types::Smart <KeyUpEvent>::Ptr Ptr;
	typedef input::KeyCode KeyCode;

	explicit KeyUpEvent (InternalEvent e);
	virtual ~KeyUpEvent () throw ();

	static EventType getClassEventType ();
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_KEY_UP_EVENT_CLASS

