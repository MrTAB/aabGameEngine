
/**
*
*	keyboard_handler.hpp
*
*   Combines separate keyboard related events into a single handler that can be
*   used to update objects buffering complete keyboard state.
**/


#if !defined(AAB_EVENTS_KEYBOARD_HANDLER_CLASS)
#define AAB_EVENTS_KEYBOARD_HANDLER_CLASS
#include"imports.hpp"
#include"multi_event_handler.hpp"
#include"key_event.hpp"
#include<string>
namespace aab	{
namespace events{


class KeyboardHandler : public MultiEventHandler
{
	private:

		class PressedEventHandler;
		class ReleasedEventHandler;
		class FocusGainedHandler;
		class FocusLostHandler;

		KeyEvent keyEvent;

		void setKeyEvent (KeyEvent k);

	public:

	typedef KeyEvent::KeyCode KeyCode;
	typedef KeyEvent::ModCode ModCode;
	typedef KeyEvent::byte_t byte_t;

	typedef aab::types::Smart <KeyboardHandler>::Ptr Ptr;

	explicit KeyboardHandler ();
	virtual ~KeyboardHandler () throw ();

	const KeyEvent & getKeyEvent () const;

	virtual void keyPressed (KeyCode);
	virtual void keyReleased (KeyCode);
	virtual void focusGained ();
	virtual void focusLost ();

	static std::string getKeyName (KeyCode);
};




}		//	events
}		//	aab
#endif	//	AAB_EVENTS_KEYBOARD_HANDLER_CLASS

