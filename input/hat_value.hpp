
/**
*
*	hat_value.hpp
*
*   Defines values for comparison against a joystick hat
*/

#if !defined(AAB_INPUT_HAT_VALUE_CLASS)
#define AAB_INPUT_HAT_VALUE_CLASS
namespace aab	{
namespace input	{
    
enum HatValue
{
    hat_centered = 0,
    hat_up,
    hat_right,
    hat_down,
    hat_left,
    hat_rightup,
    hat_rightdown,
    hat_leftup,
    hat_leftdown
};

inline HatValue getFirstHatValue()
{ 
    return hat_centered;
}

inline HatValue getLastHatValue()
{ 
    return hat_leftdown;
}

}		//	input
}		//	aab
#endif	//	AAB_INPUT_HAT_VALUE_CLASS




