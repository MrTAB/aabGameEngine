
/**
*
*	gamepad.cpp
*
**/

#include"gamepad.hpp"
#include"gamepad_data_class_data.hpp"
#include"../test/debug_assertions.hpp"
namespace aab	{
namespace input	{


Gamepad makeGamepad (GamepadPorts ports)
	//throw (GamepadUnavailableException&, NoGamepadsException&, FailedToOpenGamepadException&)
{
	Gamepad ptr (new GamepadClass (ports), GamepadClass::Deleter ());
	return ptr;
}

GamepadClass::GamepadClass (GamepadPorts ports):
	//throw (GamepadUnavailableException&, NoGamepadsException&, FailedToOpenGamepadException&) :
	GamepadDataClass (ports)
{
	ports-> enableGamepadEvents ();
	id = GamepadDataClass::getId ();
	
	//axis_pair defaultBall;
	//defaultBall.first = defaultBall.second = 0;
	
	hats.assign(SDL_JoystickNumHats (data-> joystick),HatPosition());
	balls.assign(SDL_JoystickNumBalls (data-> joystick),axis_pair(0,0));
	axes.assign(SDL_JoystickNumAxes (data-> joystick),0);
	buttons.assign(SDL_JoystickNumButtons (data-> joystick),0);
}

GamepadClass::~GamepadClass () throw ()
{
	// nothing //
}

void GamepadClass::update ()
{
	// nothing (yet) //
}

int GamepadClass::getId () const
{
	return id;
}

int GamepadClass::getAxesCount () const
{
	return axes.size ();
}

int GamepadClass::getBallCount () const
{
	return balls.size ();
}

int GamepadClass::getHatCount () const
{
	return hats.size ();
}

int GamepadClass::getButtonCount () const
{
	return buttons.size ();
}


bool GamepadClass::isDown (Button button) const
{
    if (button >= buttons.size() || button < 0)
        return false;
        
	return buttons[button];
}

GamepadAxisValue GamepadClass::getAxis (int axis) const
{
    if (axis >= axes.size() || axis < 0)
        return false;
        
	return axes[axis];
}

GamepadAxisValue GamepadClass::getXAxis () const
{
    if (axes.empty())
        return 0;
	return getAxis (0);
}

GamepadAxisValue GamepadClass::getYAxis () const
{
    if (axes.size() < 1)
        return 0;
	return getAxis (1);
}

GamepadAxisValue GamepadClass::getBallXChange (int ball) const
{
    if (ball >= balls.size() || ball < 0)
        return false;
	return balls[ball].first;
}

GamepadAxisValue GamepadClass::getBallYChange (int ball) const
{
    if (ball >= balls.size() || ball < 0)
        return false;
	return balls[ball].second;
}

HatPosition GamepadClass::getHatPosition (int hat) const
{
    if (hat >= hats.size() || hat < 0)
        return false;
	return hats[hat];
}

bool GamepadClass::hasButtonState (Button button) const
{
    if (button >= buttons.size() || button < 0)
        return false;
    return true;
	//return buttons.find (button) != buttons.end ();
}

bool GamepadClass::hasAxisState (int axis) const
{
    if (axis >= axes.size() || axis < 0)
        return false;
    return true;
	//return axes.find (axis) != axes.end ();
}

bool GamepadClass::hasXAxisState () const
{
	return hasAxisState (0);
}

bool GamepadClass::hasYAxisState () const
{
	return hasAxisState (1);
}

bool GamepadClass::hasBallState (int ball) const
{
    if (ball >= balls.size() || ball < 0)
        return false;
    return true;
	//return balls.find (ball) != balls.end ();
}

bool GamepadClass::hasHatState (int hat) const
{
    if (hat >= hats.size() || hat< 0)
        return false;
    return true;
	//return hats.find (hat) != hats.end ();
}

void GamepadClass::pressButton (Button button) //_DEBUG std::invalid_argument
{
    if (button >= 0 || button < buttons.size())
    {
        buttons[button] = true;
    }
    else
    {
        _DEBUG_THROW(std::invalid_argument("GamepadClass::pressButton::\tInvalid Button."));
    }
}

void GamepadClass::releaseButton (Button button) //_DEBUG std::invalid_argument
{
    if (button >= 0 || button < buttons.size())
    {
        buttons[button] = false;
    }
    else
    {
        _DEBUG_THROW(std::invalid_argument("GamepadClass::releaseButton::\tInvalid Button."));
    }
}

void GamepadClass::setAxis (int axis, GamepadAxisValue value) //_DEBUG std::invalid_argument
{
    if (axis >= 0 || axis < axes.size())
    {
        axes[axis] = value;
    }
    else
    {
        _DEBUG_THROW(std::invalid_argument("GamepadClass::setAxis::\tInvalid Axis."));
    }
	
}

void GamepadClass::setBall (int ball, GamepadAxisValue xchange, GamepadAxisValue ychange) //_DEBUG std::invalid_argument
{
    if (ball >= 0 || ball < balls.size())
    {
        balls[ball] = axis_pair (xchange, ychange);
    }
    else
    {
        _DEBUG_THROW(std::invalid_argument("GamepadClass::setBall::\tInvalid Ball."));
    }
}

void GamepadClass::setHat (int hat, HatPosition pos) //_DEBUG std::invalid_argument
{
    if (hat >= 0 || hat < hats.size())
    {
        hats[hat] = pos;
    }
    else
    {
        _DEBUG_THROW(std::invalid_argument("GamepadClass::setHat::\tInvalid Hat."));
    }
	
}




}		//	input
}		//	aab





