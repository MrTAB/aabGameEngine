
/**
*
*	mouse_data.cpp
*
**/

#include"mouse_data.hpp"
#include<sdl.H>
namespace aab	{
namespace input	{


MouseData makeMouseData (int x, int y, int xrel, int yrel, unsigned char buttonMask)
{
	MouseData ptr (new MouseDataClass(x, y, xrel, yrel, buttonMask), MouseDataClass::Deleter());
	return ptr;
}



MouseDataClass::MouseDataClass (int x, int y, int xrel, int yrel, unsigned char buttonMask) :
	x (x),
	y (y),
	xrel (xrel),
	yrel (yrel),
	buttonMask (buttonMask)
{
	// nothing //
}

MouseDataClass::~MouseDataClass () throw ()
{
	// nothing //
}


int MouseDataClass::getX () const
{
	return x;
}

int MouseDataClass::getY () const
{
	return y;
}

int MouseDataClass::getXChange () const
{
	return xrel;
}

int MouseDataClass::getYChange () const
{
	return yrel;
}

bool MouseDataClass::isButtonDown (int button) const
{
	return buttonMask & SDL_BUTTON (button);
}


}		//	input
}		//	aab





