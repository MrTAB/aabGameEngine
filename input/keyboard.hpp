
/*
*
*	keyboard.hpp
*
**/

#if !defined(AAB_INPUT_KEYBOARD_CLASS)
#define AAB_INPUT_KEYBOARD_CLASS
#include"key_codes.hpp"
#include"../types/smart_ptr.hpp"
#include"../types/manager.hpp"
#include<map>
#include<list>
namespace aab	{
namespace input	{

class KeyEventReceiverClass: public aab::types::Manager <KeyEventReceiverClass>
{
    public:
    
    friend class aab::types::Manager <KeyEventReceiverClass>::Deleter;
    typedef aab::types::Smart <KeyEventReceiverClass>::Ptr Ptr;
    
	virtual void setKeyPress (KeyCode) = 0;
	virtual void setKeyRelease (KeyCode) = 0;
	
};
typedef KeyEventReceiverClass::Ptr KeyEventReceiver;


class KeyboardClass : public KeyEventReceiverClass //aab::types::Manager <KeyboardClass>
{
	public:

	typedef aab::types::Smart <KeyboardClass>::Ptr Ptr;

	private:

		typedef unsigned int (* TimeFunction)(void);

		class KeyData
		{
			public:

			bool down;
			bool previous;
			unsigned int lastToggle;

			explicit KeyData ();
			explicit KeyData (bool, bool, unsigned int);

		};

		TimeFunction timeFunction;
		mutable std::map <KeyCode, KeyData> keys;
		std::list <KeyCode> justRead;

		KeyboardClass (KeyboardClass &);

		void prepareForKey (KeyCode);

	protected:
	
        //friend class aab::types::Manager <KeyboardClass>::Deleter;	
        friend Ptr makeKeyboard ();
        
		explicit KeyboardClass ();
		virtual ~KeyboardClass () throw ();

	public:
	    	


	void update ();

	bool isDown (KeyCode) const;
	bool isToggled (KeyCode) const;
	bool isHit (KeyCode) const;
	bool isReleased (KeyCode) const;
	bool isHeldLongerThan (KeyCode, unsigned int milliseconds) const;
	bool isHeldLongerThan (KeyCode, KeyCode) const;

	unsigned int getRest (KeyCode) const;
	unsigned int getLastToggle (KeyCode) const;

	bool hasRead (KeyCode) const;
	bool hasJustRead (KeyCode) const;

	virtual void setKeyPress (KeyCode);
	virtual void setKeyRelease (KeyCode);
};

typedef KeyboardClass::Ptr Keyboard;

Keyboard makeKeyboard ();




}		//	input
}		//	aab
#endif	//	AAB_INPUT_KEYBOARD_CLASS




