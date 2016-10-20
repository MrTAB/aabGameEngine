
/**
*
*	main.cpp
*
**/

#include"random.hpp"
#include<iostream>
namespace aab{
namespace maths {

int test_random ()
{
	using std::cout;

	for (;;)
	{
		cout << random () << "\n";
	}


	return 0;
}

int random ()
{
	return rand ();
}


int random (int n)
{
	return random () % (n);
}

int random (int a, int b)
{
	return 0;
}

double random (double n)
{
	return 0;
}

double random (double a, double b)
{
	return 0;
}

float random (float n)
{
	return 0;
}

float random (float a, float b)
{
	return 0;
}

char randomAtoZ ()
{
	return 0;
}

char randomatoz ()
{
	return 0;
}

char random1to9 ()
{
	return 0;
}


int main (int argc, char** argv)
{
	return test_random ();
}


}		//	maths
}		//	aab





