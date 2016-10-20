
/**
*
*	gamepad_data.cpp
*
**/

#include"gamepad_data.hpp"
#include"gamepad_data_class_data.hpp"
#include<sdl.H>
#include<exception>
#include<cmath>
namespace aab	{
namespace input	{


// root of exceptions?


GamepadDataClass::GamepadDataClass (GamepadPorts ports):
	//throw (GamepadUnavailableException&, NoGamepadsException&, FailedToOpenGamepadException&):
	data (new Data ()),
	ports (ports)
{
	int id = ports-> getFreeId ();

//	if (id == -1)
//	{
//		throw std::runtime_error ("GamepadDataClass::GamepadDataClass:: no gamepads available");
	//}

	data-> index = id;
	data-> joystick = SDL_JoystickOpen  (id);

	if (data-> joystick == NULL)
	{
		throw FailedToOpenGamepadException(id);
	}
}

GamepadDataClass::~GamepadDataClass () throw ()
{
	SDL_JoystickClose (data-> joystick);
	ports-> releaseId (data-> index);
}

GamepadPorts GamepadDataClass::getGamepadPorts () const
{
	return ports;
}

int GamepadDataClass::getId () const
{
	return data-> index;
}

std::string GamepadDataClass::getName () const
{
	return std::string (SDL_JoystickName  (data-> index));
}


}		//	input
}		//	aab





