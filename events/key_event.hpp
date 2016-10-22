
/**
*
*	key_event.hpp
*
*   Records infomration about an individual Key event
**/

#if !defined(AAB_EVENTS_KEY_EVENT_CLASS)
#define AAB_EVENTS_KEY_EVENT_CLASS
#include"event.hpp"
#include"internal_event.hpp"
#include"imports.hpp"
#include"../input/key_codes.hpp"
#include"types/byte.hpp"
namespace aab	{
namespace events{


class KeyEvent : public Event
{
	public:

		typedef aab::types::Smart <KeyEvent>::Ptr Ptr;
		typedef input::KeyCode KeyCode;
		typedef input::ModCode ModCode;
		typedef types::byte_t byte_t;

	private:

		byte_t scanCode;
		KeyCode keyCode;
		ModCode modCode;
		wchar_t unicode;

	public:

	explicit KeyEvent (InternalEvent, EventType);
	explicit KeyEvent (byte_t scanCode, KeyCode keyCode, ModCode modCode, wchar_t unicode);
	virtual ~KeyEvent () throw ();

	byte_t getScanCode () const;
	KeyCode getKeyCode () const;
	ModCode getModCode () const;
	wchar_t getUnicode () const; // if enabled.

	// static EventType getClassEventType (); KeyEvent is class wide-ishly abstract.
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_KEY_UP_EVENT_CLASS

