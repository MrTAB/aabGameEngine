
/*
*
*	auto_keyboard.hpp
*
*	KeyState - describes the state of the keyboard.
*
*	Make one of these, and update it every round with update (); An InputConnector
*	subclass is required to create this; Its something that has connected to the
*	keyboard in its constructor, thus making a new instance of KeyState usefull
*	and valid. Infact, the constructor of this won't even throw an exception.
*	Smooth sailing.
*
*	You can check all sorts of things with this class, however it does overdo
*	computation for just checking the KeyBoard state:
*
*	isDown
*		true if that key is currently being held down
*
*	isToggled
*		true if that key has *just* changed state (ie down to up or up to down in this last update())
*
*	isHit
*		true if up to down in this last update
*
*	isReleased
*		true if down to up in this last update
*
*	isHeldLongerThan (keyCode, milliseconds)
*		true if its been held down for that amount of time
*
*	isHeldLongerThan (akey, bkey)
*		true if akey has been held down longer than bkey (and both are being held down as we speak). This is most usefull for command keys eg: isHeldLongerThan (key_leftcontrol, key_s)||isHeldLongerThan (key_rightcontrol, key_s); to check if someones trying Ctrl+s (notice how if you press s then control this doc wont save lol.
*
*	isModOn
*		true if a mod is on, eg numlocks or capslock might be down
*
*	getRest
*		returns how long its been since a key was toggled (changed state)
*
*	getLastToggle
*		returns when that key changed state last.
*
*	hasRead
*		if you use commands like isDown on a key that hasnt been read yet, or doesnt exist on the keyboard, itll return false. If the key exists on the keyboard, then update will read it and hasRead() will start returning true. If not, then hasRead will keep returning false.
*
*	hasPreviouslyRead
*		commands like isToggled, require knowing the previous state of the key, so it can see that its went from up to down or vice versa. Thus if this returns false, then so will those commands. After two calls to update this should be fine and return true for all existing keys. Really dont worry your head about this stuff.
*
*	hasToggleTimeFor
*		true if the time is being stored for this key.
*
*
*	use methods like enableEventPumping() to enable and disable eventpumping.
*	If you are using an event handling system alongside this, it will handle
*	the event pumping, and so update() needs to know not to use event pumping.
*	Disable it with disableEventPumping (). Alternatively, you may have multiple
*	systems which have event pumping; Only one of these should have eventpumping
*	enabled, and so it is also wise to invoke its update first, as it will
*	handle the event pumping.
*
*	Keystate is a noncopyable class.
*
**/

/*
*	todo - make a keyboard mapping class, so that user defined indices can map to specific keys
*/

#if !defined(AAB_INPUT_AUTO_KEYBOARD_CLASS)
#define AAB_INPUT_AUTO_KEYBOARD_CLASS
#include"key_codes.hpp"
#include"input_connector.hpp"
#include"../types/manager.hpp"
#include"../types/smart_ptr.hpp"
#include<vector>
namespace aab	{
namespace input	{

/*
	to allow user specification of the TimeFunction.
*/

class AutoKeyboardClass : public aab::types::Manager <AutoKeyboardClass>
{
	public:

	typedef aab::types::Smart <AutoKeyboardClass>::Ptr Ptr;

	private:

		typedef unsigned int (* TimeFunction)(void);

		unsigned char * keys;
		int size;
		bool pumpEvents;
		TimeFunction timeFunction;
		std::vector<unsigned char> previousKeys;
		std::vector<unsigned int> lastToggle;
		int mods;

		AutoKeyboardClass (AutoKeyboardClass &);

		void resize (int);

	protected:

		friend class aab::types::Manager <AutoKeyboardClass>::Deleter;
		friend Ptr makeAutoKeyboard (InputConnector::Ptr) ;//throw (std::exception &);
		explicit AutoKeyboardClass (InputConnector::Ptr) ;//throw (std::exception &);
		virtual ~AutoKeyboardClass () throw ();

	public:

	bool isDown (KeyCode) const;
	bool isToggled (KeyCode) const;
	bool isHit (KeyCode) const;
	bool isReleased (KeyCode) const;
	bool isHeldLongerThan (KeyCode, unsigned int milliseconds) const;
	bool isHeldLongerThan (KeyCode, KeyCode) const;
	
	void refreshKey(KeyCode);

	bool isModOn (ModCode) const;

	unsigned int getRest (KeyCode) const;
	unsigned int getLastToggle (KeyCode) const;

	bool hasRead (KeyCode) const;
	bool hasPreviouslyRead (KeyCode) const;
	bool hasToggleTimeFor (KeyCode) const;

	void update ();

	void enableEventGrabbing ();
	void disableEventGrabbing ();
	bool isEventGrabbingEnabled () const;

};

typedef AutoKeyboardClass::Ptr AutoKeyboard;

AutoKeyboard makeAutoKeyboard (InputConnector::Ptr);// throw (std::exception &);




}		//	input
}		//	aab
#endif	//	AAB_INPUT_AUTO_KEYBOARD_CLASS




