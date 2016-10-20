
/**
*
*	auto_gamepad.cpp
*
**/

#include"auto_gamepad.hpp"
#include"gamepad_data_class_data.hpp"
#include<sdl.H>
#include<exception>
#include<cmath>
namespace aab	{
namespace input	{


AutoGamepad makeGamepad2 (GamepadPorts ports)
	//throw (GamepadUnavailableException&, NoGamepadsException&)
{
	AutoGamepad ptr (new AutoGamepadClass (ports), AutoGamepadClass::Deleter ());
	return ptr;
}

AutoGamepadClass::AutoGamepadClass (GamepadPorts ports):
	//throw (GamepadUnavailableException&, NoGamepadsException&):
	GamepadDataClass (ports)
{
	// nothing //
}

AutoGamepadClass::~AutoGamepadClass () throw ()
{
	// nothing //
}

int AutoGamepadClass::getAxesCount () const
{
	return SDL_JoystickNumAxes (data-> joystick);
}

int AutoGamepadClass::getBallCount () const
{
	return SDL_JoystickNumBalls (data-> joystick);
}


int AutoGamepadClass::getHatCount () const
{
	return SDL_JoystickNumHats (data-> joystick);
}

int AutoGamepadClass::getButtonCount () const
{
	return SDL_JoystickNumButtons (data-> joystick);
}


int16_t AutoGamepadClass::getRawAxis (int axis) const
{
	return (int16_t)SDL_JoystickGetAxis (data-> joystick, axis);
}

GamepadAxisValue AutoGamepadClass::getXAxis () const
{
    return getRawAxis(0);/*
	short int x = getRawAxis (0);

	if (std::abs (x) < 10)
	{
		return 0;
	}

	return (static_cast<double> (x)) / 32768.0;*/
}

GamepadAxisValue AutoGamepadClass::getYAxis () const
{
    return getRawAxis(1);
    /*
	short int y = getRawAxis (1);

	if (std::abs (y) < 10)
	{
		return 0;
	}

	return (static_cast<double> (y)) / 32768.0;
	*/
}

bool AutoGamepadClass::isDown (Button button) const
{
	return SDL_JoystickGetButton (data-> joystick, button);
}

bool AutoGamepadClass::hasButtonState (Button button) const
{
	return button < getButtonCount () && button >= 0;
}


}		//	input
}		//	aab





