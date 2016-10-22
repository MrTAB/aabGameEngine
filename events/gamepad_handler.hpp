
/**
*
*	gamepad_handler.hpp
*
*   Recieves callbacks for gamepad events associated with a single gamepad.
**/


#if !defined(AAB_EVENTS_GAMEPAD_HANDLER_CLASS)
#define AAB_EVENTS_GAMEPAD_HANDLER_CLASS
#include"../input/hat_position.hpp"
#include"imports.hpp"
#include"../input/gamepad_values.hpp"
namespace aab	{
namespace events{


class GamepadHandler // Yup, no extension!!
{
	public:

	typedef aab::types::Smart <GamepadHandler>::Ptr Ptr;
	typedef aab::input::HatPosition HatPosition;

	explicit GamepadHandler () {};
	virtual ~GamepadHandler () throw () {};
	
	typedef aab::input::GamepadAxisValue GamepadAxisValue;

	virtual void buttonPressed (int) {};
	virtual void buttonReleased (int) {};
	virtual void axisMove (int axis, GamepadAxisValue) {};
	virtual void ballMove (int ball, GamepadAxisValue, GamepadAxisValue) {};
	virtual void hatMove (int hat, HatPosition) {};

};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_GAMEPAD_HANDLER_CLASS

