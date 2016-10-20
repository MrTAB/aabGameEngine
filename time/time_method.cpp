
/**
*
*	time_method.cpp"
*
**/

#include"time_method.hpp"
#include<sdl.H>
namespace aab	{
namespace time	{


unsigned int getMilliseconds ()
{
	return (unsigned int) SDL_GetTicks ();
}

void delay (unsigned int milliseconds)
{
	SDL_Delay ((Uint32) milliseconds);
}


}		//	time
}		//	aab





