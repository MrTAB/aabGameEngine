
/**
*
*	gamepads_auto_handler.hpp
*
*
**/


#if !defined(AAB_EVENTS_GAMEPADS_AUTO_HANDLER_CLASS)
#define AAB_EVENTS_GAMEPADS_AUTO_HANDLER_CLASS
#include"../input/gamepad.hpp"
#include"gamepad_port_handler.hpp"
#include"imports.hpp"
#include<map>
namespace aab	{
namespace events{


class GamepadsAutoHandler : public GamepadPortHandler
{
	public:

	typedef aab::types::Smart <GamepadsAutoHandler>::Ptr Ptr;
	typedef aab::input::HatPosition HatPosition;
	typedef aab::input::Gamepad Gamepad;

	private:

		typedef std::map <int, Gamepad> PadMap;
		PadMap pads;


	public:

	explicit GamepadsAutoHandler (Gamepad);
	explicit GamepadsAutoHandler ();
	virtual ~GamepadsAutoHandler () throw ();

	//void setGamepad (Gamepad);
	void addGamepad (Gamepad);
	void clearGamepad (int id);
	void clearGamepads ();
	Gamepad getGamepad (int id);

	bool hasGamepad (int id) const;
	int countGamepads () const;

	virtual void buttonPressed (int id, int button);
	virtual void buttonReleased (int id, int button);
	virtual void axisMove (int id, int axis, GamepadAxisValue);
	virtual void ballMove (int id, int ball, GamepadAxisValue x, GamepadAxisValue y);
	virtual void hatMove (int id, int hat, HatPosition);

};



}		//	events
}		//	aab
#endif	//	AAB_EVENTS_GAMEPADS_AUTO_HANDLER_CLASS

