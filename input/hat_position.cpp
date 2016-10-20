
/**
*
*	hat_position.cpp
*
**/

#include"hat_position.hpp"
#include<sdl.H>
namespace aab	{
namespace input	{

const int HatPosition::centered = SDL_HAT_CENTERED;
const int HatPosition::up = SDL_HAT_UP;
const int HatPosition::right = SDL_HAT_RIGHT;
const int HatPosition::down = SDL_HAT_DOWN;
const int HatPosition::left = SDL_HAT_LEFT;
const int HatPosition::rightup = SDL_HAT_RIGHTUP;
const int HatPosition::rightdown = SDL_HAT_RIGHTDOWN;
const int HatPosition::leftup = SDL_HAT_LEFTUP;
const int HatPosition::leftdown = SDL_HAT_LEFTDOWN;
const int HatPosition::upright = SDL_HAT_RIGHTUP;
const int HatPosition::downright = SDL_HAT_RIGHTDOWN;
const int HatPosition::upleft = SDL_HAT_LEFTUP;
const int HatPosition::downleft = SDL_HAT_LEFTDOWN;

HatValue HatPosition::as_hat_value()const
{
    switch(value)
    {
        case SDL_HAT_CENTERED: return hat_centered;
        case SDL_HAT_UP: return hat_up;
        case SDL_HAT_RIGHT: return hat_right;
        case SDL_HAT_DOWN: return hat_down;
        case SDL_HAT_LEFT: return hat_left;
        case SDL_HAT_RIGHTUP: return hat_rightup;
        case SDL_HAT_RIGHTDOWN: return hat_rightdown;
        case SDL_HAT_LEFTUP: return hat_leftup;
        case SDL_HAT_LEFTDOWN: return hat_leftdown;
    }
}

HatPosition::HatPosition () : value (centered)
{
	// nothing //
}

/*implicit*/ 
/*HatPosition::HatPosition (int value):
	value (value)
{
	// nothing //
}
*/


/*
HatPosition::operator int& ()
{
	return value;
}

HatPosition::operator int () const
{
	return value;
}
*/


int HatPosition::getX() const
{
    switch(value)
    {
        case centered:
        case up:
        case down: return 0;
        
        case right:
        case rightup:
        case rightdown: return 1;
        
        case leftup:
        case leftdown:
        case left: return -1;
    }
}

int HatPosition::getY() const
{
    switch(value)
    {
        case centered:
        case right:
        case left: return 0;
        
        case down:
        case leftdown:
        case rightdown: return 1;   
                 
        case up:
        case rightup:
        case leftup: return -1;

    }
}

}		//	input
}		//	aab





