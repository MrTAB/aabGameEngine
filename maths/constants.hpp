
/**
*
*	constants.hpp
*
**/

#if !defined(AAB_MATHS_CONSTANTS)
#define AAB_MATHS_CONSTANTS
namespace aab	{
namespace maths {

extern const double pi;
extern const double epsilon;
extern const double euler; // i.e. e
extern const double golden_ratio;
extern const double sqrt_2;
extern const double sqrt_3;
extern const double sqrt_5;
extern const double invsqrt_2;

inline bool near (double a, double b) { return (a<b? ( b-a<epsilon ) : (a-b<epsilon) ); }
inline bool near_zero (double x) { return (x>0? x < epsilon : -x < epsilon); }


inline  float radiansToDegrees (const float radians)
{
    return 180.0*radians/pi;
}

inline  float degreesToRadians (const float degrees)
{
    return pi*degrees/180.0;
}

}		//	maths
}		//	aab
#endif	//	AAB_MATHS_CONSTANTS
