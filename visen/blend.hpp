
/**
*
*	blend.hpp - a simple blending method
*
**/

#if !defined(AAB_VISEN_BLEND)
#define AAB_VISEN_BLEND
namespace aab	{
namespace visen	{
namespace blend {


template<typename T, typename M = T>
T linear (T input, T target, M inputMultiplier)
{
    return input * inputMultiplier + (1.0f-inputMultiplier)*target;
}


}       //  blend
}		//	visen
}		//	aab
#endif	//	AAB_VISEN_BLEND




