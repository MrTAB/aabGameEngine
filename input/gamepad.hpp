
/**
*
*	gamepad.hpp
*
*   Gamepad stores and queries the state of an individual gamepad.
*	Requires update via an GamepadAutoHandler
*	and a Dispatcher plugged into an EventQueue.
*
**/

#if !defined(AAB_INPUT_GAMEPAD_CLASS)
#define AAB_INPUT_GAMEPAD_CLASS
#include"hat_position.hpp"
#include"gamepad_data.hpp"
#include"../types/smart_ptr.hpp"
#include<map>
namespace aab	{
namespace input	{


class GamepadClass : public GamepadDataClass
{
	public:

	typedef aab::types::Smart <GamepadClass>::Ptr Ptr;
	typedef int Button;

	private:

		typedef std::pair <GamepadAxisValue, GamepadAxisValue> axis_pair;

		int id;
		// change from map to fully fitted vectors - map is smart and safe, but it's better to provide the allocation at load-time.
		/*
		mutable std::map<int, HatPosition> hats;
		mutable std::map<int, axis_pair> balls;
		mutable std::map<int, GamepadAxisValue> axes;
		mutable std::map<Button, bool> buttons;*/
		std::vector<HatPosition> hats;
		std::vector<axis_pair> balls;
		std::vector<GamepadAxisValue> axes;
		std::vector<int> buttons;

	protected:

		friend Ptr makeGamepad (GamepadPorts);
			//throw (GamepadUnavailableException&, NoGamepadsException&, FailedToOpenGamepadException&);
		explicit GamepadClass (GamepadPorts);
				//throw (GamepadUnavailableException&, NoGamepadsException&, FailedToOpenGamepadException&);
		virtual ~GamepadClass () throw ();

	public:



	void update ();

	int getId () const;
	int getAxesCount () const;
	int getBallCount () const;
	int getHatCount () const;
	int getButtonCount () const;

	bool isDown (Button) const;
	GamepadAxisValue getAxis (int) const;
	GamepadAxisValue getXAxis () const;
	GamepadAxisValue getYAxis () const;
	GamepadAxisValue getBallXChange (int) const;
	GamepadAxisValue getBallYChange (int) const;
	HatPosition getHatPosition (int) const;
	
	bool isMovingLeft()const{ return getXAxis() < 0.0; }
	bool isMovingRight()const{ return getXAxis() > 0.0; }
	bool isMovingUp()const{ return getYAxis() < 0.0; }
	bool isMovingDown()const{ return getYAxis() > 0.0; }

	bool hasButtonState (Button) const;
	bool hasAxisState (int) const;
	bool hasXAxisState () const;
	bool hasYAxisState () const;
	bool hasBallState (int) const;
	bool hasHatState (int) const;

	void pressButton (Button); //_DEBUG std::invalid_argument
	void releaseButton (Button); //_DEBUG std::invalid_argument
	void setAxis (int, GamepadAxisValue); //_DEBUG std::invalid_argument
	void setBall (int, GamepadAxisValue, GamepadAxisValue); //_DEBUG std::invalid_argument
	void setHat (int, HatPosition); //_DEBUG std::invalid_argument
};


typedef GamepadClass::Ptr Gamepad;

Gamepad makeGamepad (GamepadPorts);
		//throw (GamepadUnavailableException&, NoGamepadsException&, FailedToOpenGamepadException&);


}		//	input
}		//	aab
#endif	//	AAB_INPUT_GAMEPAD_CLASS




