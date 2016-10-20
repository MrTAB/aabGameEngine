
/**
*
*	auto_gamepad.hpp
*
*	an asynchronous Gamepad class -
*		represents a pad thats plugged in. The constructor requires a GamepadPort
*		from which it takes an available port. If no port is available, an
*		exception is thrown from the constructor.
*			Attempts to evaluate buttons or axes which do not exist result in
*		false return values... More acceptable than program doom (however much
*		less acceptable than the program DOOM itself).
*			When the Gamepad instance loses scope, its deconstructor puts the
*		port back into the Gamepad Ports class as an available port.
*			When the pad is unplugged during use, its state freezes..
*		Plug it back in quickly! An extension was considered: You supply a
*		method, it calls it when the pad is unplugged. However, i could not
*		figure out when the pad was unplugged by any means other than nothing
*		happening (which could reasonably be because nothing is happening).
*
*
*	Note:	The constructor may throw a std::exception if it fails. It could
*	fail for no reason other than there not being enough controll pads plugged
*	in, e.g. if there are three Gamepads floating about and only 3 plugged in,
*	then trying to make another instance will cause an exception to be thrown.
*	a) A logic_error means that there are no pads available.
*	b) A runtime_error means that it failed to open an available pad.
*	c) A bad_aloc may also be thrown if memory runs out.
*	catch (std::exception &) will catch all of these, but in the case of a)
*	and b) you can do something about it and inform your user.
*
*	AutoGamepad is a noncopyable class, so use referencing or pointers
*	(Copy Construction is private)
**/

#if !defined(AAB_INPUT_AUTO_GAMEPAD)
#define AAB_INPUT_AUTO_GAMEPAD
#include"gamepad_ports.hpp"
#include"gamepad_data.hpp"
#include"gamepad_values.hpp"
#include"../types/smart_ptr.hpp"
#include<string>
#include<memory>
#include<exception>
#include<stdexcept>
namespace aab	{
namespace input	{

/*
*	may be extended to have Ball and Hat operations once i get a pad with them
*	(So i can test it lol). May also be extended with isHit(Button),
*	isReleased(Button) getRest (Button)
*/



class AutoGamepadClass : public GamepadDataClass
{
	public:

	typedef aab::types::Smart <AutoGamepadClass>::Ptr Ptr;

	private:

		AutoGamepadClass (AutoGamepadClass&);

	protected:

		friend Ptr makeGamepad2 (GamepadPorts);
			//throw (GamepadUnavailableException&, NoGamepadsException&);
		explicit AutoGamepadClass (GamepadPorts);
			//throw (GamepadUnavailableException&, NoGamepadsException&);

		virtual ~AutoGamepadClass () throw ();

	public:

	typedef int Button;


	int getAxesCount () const;
	int getBallCount () const;
	int getHatCount () const;
	int getButtonCount () const;

	int16_t getRawAxis (int axis) const;
	GamepadAxisValue getXAxis () const;
	GamepadAxisValue getYAxis () const;

	bool isDown (Button) const;
	bool hasButtonState (Button) const;

};

typedef AutoGamepadClass::Ptr AutoGamepad;

AutoGamepad makeAutoGamepad (GamepadPorts);
			//throw (GamepadUnavailableException&, NoGamepadsException&);



}		//	input
}		//	aab
#endif	//	AAB_INPUT_AUTO_GAMEPAD




