
/**
*
*	gamepad_data_class_data.hpp
*
*	INTERNAL HEADER
*
*	specifies GamepadDataClass subclass Data
**/

#if !defined(AAB_INPUT_GAMEPAD_DATA_CLASS_DATA)
#define AAB_INPUT_GAMEPAD_DATA_CLASS_DATA
#include"gamepad_data.hpp"
#include<sdl.H>
namespace aab	{
namespace input	{

struct GamepadDataClass::Data
{
	SDL_Joystick *joystick;
	int index;
};

}		//	input
}		//	aab
#endif	//	AAB_INPUT_GAMEPAD_DATA_CLASS_DATA




