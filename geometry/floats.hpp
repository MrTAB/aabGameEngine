/**
*
*	floats.hpp
*
**/

#if !defined(AAB_GEOMETRY_FLOAT_METHODS)
#define AAB_GEOMETRY_FLOAT_METHODS
#include<cmath>
#include<limits>
namespace aab	{
namespace geometry{
namespace floats{

// compares floats with vectors in mind. This will be less effective at comparison for larger numbers beyond the expected scope of vectors, such as tens of thousands and up.
// should do fine for comparing anything above 1e-5 to 0
inline bool compare (const float a, const float b)
{
    return std::fabs(a-b) < 1e-5; 
}

inline bool isZero(const float a)
{
    return std::fabs(a) < 1e-5;
}

//compares the difference to a % of the largest number, avoiding least significant bit round off errors.
// "To compare f1 and f2 calculate diff = fabs(f1-f2). If diff is smaller than n% of max(abs(f1),abs(f2)) then f1 and f2 can be considered equal." from http://randomascii.wordpress.com/
inline bool compareRel(const float a, const float b)
{
    using std::fabs;
    return fabs (a - b) <= ((fabs (a) < fabs (b) ? fabs (b) : fabs (a)) *
        std::numeric_limits<double>::epsilon ());
}

inline float trimIfNearZero (const float f)
{
	if (isZero (f))
	{
		return 0.0f;
	}

	return f;
}




/*
static inline const float getEpsilon ()
{
	return 0.00001f;
}

static inline bool areClose (const float a, const float b)
{
	return closeToZero (b - a);
}

static inline bool closeToZero (const float f)
{
	return std::abs (f) < getEpsilon ();
}
*/

/*

Who knows.. Might add something like this...

class Float
{
	float value;

	public:

	Float () : value (0)
	{
		// nothing //
	}

	Float (const float value) : value (value)
	{
		// nothing //
	}

	Float & operator () (const Float & f)
	{
		value *= f.value;
		return *this;
	}

	operator float () const
	{
		return value;
	}

	Float & operator += (const Float & f)
	{
		value += f.value;
		return *this;
	}

	Float & operator -= (const Float & f)
	{
		value -= f.value;
		return *this;
	}

	Float operator + (const Float & f) const
	{
		return Float (*this) += f;
	}

	Float operator - (const Float & f) const
	{
		return Float (*this) -= f;
	}

	bool operator == (const Float & f) const
	{
		return areClose (value, f.value);
	}

	bool operator != (const Float & f) const
	{
		return ! (*this) == f;
	}

	bool operator < (const Float & f) const
	{
		return value < f.value;
	}

	bool operator <= (const Float & f) const
	{
		return value <= f.value;
	}

	bool operator > (const Float & f) const
	{
		return value > f.value;
	}

	bool operator >= (const Float & f) const
	{
		return value >= f.value;
	}
};

*/


}   // floats
}	// geometry
}	// aab
#endif // AAB_GEOMETRY_FLOAT_METHODS

