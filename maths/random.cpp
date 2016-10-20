
/**
*
*	random.cpp
*
**/

#include"random.hpp"
#include<iostream>
#include<cstdlib>
namespace aab{
namespace maths {


// Still to modify for NEGATIVES



const int random_value::maximum = RAND_MAX;


int test_random ()
{
	using std::cout;

	typedef int type;

	type min = -10000000;
	type max = 10000000;
	type smallest = max;
	type largest = min;
	type current = 0;

	for (;;)
	{
		current = random (-10);

		smallest = std::min (smallest, current);
		largest = std::max (largest, current);

		cout << "smallest:\t" << smallest << "\tlargest:\t" << largest << "\tcurrent:\t" << current << "\n";
	}



	return 0;
}


void seed_random (unsigned int seed)
{
	srand (seed);
}

int random ()
{
	return rand ();
}


int random (int n)
{
	return rand () % (n + 1);
}

int random (int a, int b)
{
	return a + (rand () % (1 + b - a));
}

long int random (long int a, long int b)
{
	return a + (rand () % (1 + b - a));
}

long long int random (long long int a, long long int b)
{
    //const long int a = static_cast<long int>(a_in);
    //const long int b = static_cast<long int>(b_in);
	return a + (rand () % (1 + b - a));
}

unsigned int random (unsigned int n)
{
	return rand () % (n + 1);
}

unsigned int random (unsigned int a, unsigned int b)
{
	return a + (rand () % (1 + b - a));
}

long unsigned int random (long unsigned int a, long unsigned int b)
{
	return a + (rand () % (1 + b - a));
}


long long unsigned int random (long long unsigned int a, long long unsigned int b)
{
    //const long unsigned int a = static_cast<long unsigned int>(a_in);
    //const long unsigned int b = static_cast<long unsigned int>(b_in);
	return a + (rand () % (1 + b - a));
}


double randomReal ()
{
	return static_cast <double> (rand ()) / RAND_MAX;
}

double random (double n)
{
	return randomReal() * n;
}

double random (double a, double b)
{
	return a + random (b - a);
}

float random (float n)
{
	return (static_cast <float> (rand ()) * n) / RAND_MAX;
}

float random (float a, float b)
{
	return a + random (b - a);
}

int random_sign()
{
    return ((rand () %(2)) ? 1 : -1);
}


char randomAtoZ ()
{
	return static_cast <char> (random ('A', 'Z'));
}

char randomatoz ()
{
	return static_cast <char> (random ('a', 'z'));
}

char random1to9 ()
{
	return static_cast <char> (random ('1', '9'));
}

char randomWellFormed()
{
    return static_cast <char> (random (' ', '~'));
}

bool random1in (int n)
{
	return random (n - 1) == 0;
}

bool randomMinN (int m, int n)
{
	return random (n - 1) < m;
}




}		//	maths
}		//	aab




