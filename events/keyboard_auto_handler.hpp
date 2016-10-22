
/**
*
*	keyboard_auto_handler.hpp
*
*   Updates a keyInfo when the keyPressed/Released methods are invoked.
**/


#if !defined(AAB_EVENTS_KEYBOARD_AUTO_HANDLER_CLASS)
#define AAB_EVENTS_KEYBOARD_AUTO_HANDLER_CLASS
#include"imports.hpp"
#include"keyboard_handler.hpp"
#include"../input/keyboard.hpp"
namespace aab	{
namespace events{


class KeyboardAutoHandler : public KeyboardHandler
{
	public:

	typedef aab::types::Smart <KeyboardAutoHandler>::Ptr Ptr;
	typedef aab::input::KeyEventReceiver KeyEventReceiver;

	private:

		KeyEventReceiver keyInfo;

	public:

	explicit KeyboardAutoHandler (KeyEventReceiver);
	virtual ~KeyboardAutoHandler () throw ();

	virtual void keyPressed (KeyCode);
	virtual void keyReleased (KeyCode);
	virtual void focusGained ();
	virtual void focusLost ();
};



}		//	events
}		//	aab
#endif	//	AAB_EVENTS_KEYBOARD_AUTO_HANDLER_CLASS

