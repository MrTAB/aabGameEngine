
/**
*   gamepad_values.hpp
**/

#if !defined(AAB_INPUT_GAMEPAD_VALUES)
#define AAB_INPUT_GAMEPAD_VALUES
#include<cstdint>
namespace aab	{
namespace input	{

typedef int16_t GamepadAxisValue; //value ranging from  -32768 to 32767
enum
{
    gamepad_axis_min = -32768,
    gamepad_axis_max = 32767
};



}		//	input
}		//	aab
#endif	//	AAB_INPUT_GAMEPAD_VALUES




