
/**
*
*	gamepad_data.hpp
*
*   The GamepadDataClass is an abstract class defining objects which store and
*   query individual gamepads. Implementations of this abstract class may choose
*   to update the stored data in different manners
*
*	Using this are the Event Dependant Gamepad (Gamepad) and the Asynchronous
*   Gamepad (AutoGamepad)
*
**/

#if !defined(AAB_INPUT_GAMEPAD_DATA_CLASS)
#define AAB_INPUT_GAMEPAD_DATA_CLASS
#include"gamepad_values.hpp"
#include"gamepad_ports.hpp"
#include"../types/smart_ptr.hpp"
#include<string>
#include<memory>
#include<exception>
#include<stdexcept>
namespace aab	{
namespace input	{

/*
class no_gamepads_free_error : public std::runtime_error
{
	public:
	explicit no_gamepads_free_error (const std::string & what) : std::runtime_error(what) { }
};

class failed_to_open_gamepad_error : public std::runtime_error
{
	public:
	explicit failed_to_open_gamepad_error (const std::string & what) : std::runtime_error(what) { }
};
*/


class GamepadDataClass : public aab::types::Manager <GamepadDataClass>
{
	public:

	typedef aab::types::Smart <GamepadDataClass>::Ptr Ptr;

	protected:

		GamepadDataClass (GamepadDataClass &);

		struct Data;
		const std::auto_ptr <Data> data;

		GamepadPorts ports;

		friend class aab::types::Manager <GamepadDataClass>::Deleter;
		explicit GamepadDataClass (GamepadPorts);
			//throw (GamepadUnavailableException&, NoGamepadsException&, FailedToOpenGamepadException&);
		virtual ~GamepadDataClass () throw ();

	public:

	typedef int Button;


	GamepadPorts getGamepadPorts () const;

	virtual int getId () const;
	std::string getName () const;
	virtual int getAxesCount () const = 0;
	virtual int getBallCount () const = 0;
	virtual int getHatCount () const = 0;
	virtual int getButtonCount () const = 0;

	virtual GamepadAxisValue getXAxis () const = 0;
	virtual GamepadAxisValue getYAxis () const = 0;

	virtual bool isDown (Button) const = 0;
	virtual bool hasButtonState (Button) const = 0;

};

typedef GamepadDataClass::Ptr GamepadData;

}		//	input
}		//	aab
#endif	//	AAB_INPUT_GAMEPAD_DATA_CLASS




