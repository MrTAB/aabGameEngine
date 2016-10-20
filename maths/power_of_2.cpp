
/**
*
*	power_of_2.cpp
*
**/

#include"power_of_2.hpp"
namespace aab{
namespace maths {


bool isPowerOf2 (int value)
{
	if (value < 2)
	{
		return false;
	}

	while (value > 2)
	{
		if ((value % 2) != 0)
		{
			return false;
		}

		value >>= 1;
	}

	return true;
}

int nextPowerOf2 (int value)
{
	int count = 0;

	if (value < 2)
	{
		return 2;
	}

	while (value > 1)
	{
		value >>= 1;
		++count;
	}

	return 1 << (count + 1);
}

bool testIsPowerOf2 ()
{
	return
	isPowerOf2 (0) == false &&
	isPowerOf2 (-2) == false &&
	isPowerOf2 (-50) == false &&
	isPowerOf2 (3) == false &&
	isPowerOf2 (2) == true &&
	isPowerOf2 (16) == true &&
	isPowerOf2 (1024) == true &&
	isPowerOf2 (1025) == false;
}

bool testNextPowerOf2  ()
{
	return
	nextPowerOf2 (-50) == 2 &&
	nextPowerOf2 (1) == 2 &&
	nextPowerOf2 (2) == 4 &&
	nextPowerOf2 (4) == 8 &&
	nextPowerOf2 (5) == 8 &&
	nextPowerOf2 (37) == 64 &&
	nextPowerOf2 (1569) == 2048 &&
	nextPowerOf2 (15) == 16;
}

bool testPowers ()
{
	return testNextPowerOf2 ();
}





}		//	maths
}		//	aab





