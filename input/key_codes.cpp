
/**
*
*
*
**/

#include"key_codes.hpp"
#include<sdl.H>
namespace aab	{
namespace input	{

std::string getKeyName (KeyCode key)
{
	return std::string(SDL_GetKeyName ((SDLKey) key));
}

}		//	input
}		//	aab





