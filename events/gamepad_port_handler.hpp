
/**
*
*	gamepad_port_handler.hpp
*
**/


#if !defined(AAB_EVENTS_GAMEPAD_PORT_HANDLER_CLASS)
#define AAB_EVENTS_GAMEPAD_PORT_HANDLER_CLASS
#include"imports.hpp"
#include"multi_event_handler.hpp"
#include"../input/hat_position.hpp"
#include"../input/gamepad_values.hpp"
namespace aab	{
namespace events{


class GamepadPortHandler : public MultiEventHandler
{
	private:

		class PressedEventHandler;
		class ReleasedEventHandler;
		class AxisHandler;
		class BallHandler;
		class HatHandler;

	public:

    typedef aab::input::GamepadAxisValue GamepadAxisValue;
	typedef aab::types::Smart <GamepadPortHandler>::Ptr Ptr;
	typedef aab::input::HatPosition HatPosition;

	explicit GamepadPortHandler ();
	virtual ~GamepadPortHandler () throw ();

	virtual void buttonPressed (int, int);
	virtual void buttonReleased (int, int);
	virtual void axisMove (int, int, aab::input::GamepadAxisValue);
	virtual void ballMove (int, int, aab::input::GamepadAxisValue, aab::input::GamepadAxisValue);
	virtual void hatMove (int, int, HatPosition);

};



}		//	events
}		//	aab
#endif	//	AAB_EVENTS_GAMEPAD_PORT_HANDLER_CLASS

