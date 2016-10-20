
/**
*
*	random.hpp
*
*	- a collection of a few randomization methods.
*	These currents rely on rand(). This limits the depth
*	to RAND_MAX which is generally 32767.
**/

#if !defined(AAB_MATHS_RANDOM_METHODS)
#define AAB_MATHS_RANDOM_METHODS
namespace aab	{
namespace maths {

struct random_value
{
	static const int maximum;
};

int random (); // [0, 32767]
double randomReal (); // [0,1]
void seed_random (unsigned int);

int random (int n); // random 1 to n INCLUSIVE
int random (int a, int b);
long int random (long int a, long int b);
long long int random (long long int a, long long int b);
unsigned int random (unsigned int n); // random 1 to n INCLUSIVE
unsigned int random (unsigned int a, unsigned int b);
unsigned long int random (long unsigned int a, long unsigned int b);
unsigned long long int random (long long unsigned int a, long long unsigned int b);
double random (double n);
double random (double a, double b);
float random (float n);
float random (float a, float b);

int random_sign(); // returns -1 or 1

/*
int signed_random (int n);
int signed_random (int a, int b);
double signed_random (double n);
double signed_random (double a, double b);
float signed_random (float n);
float signed_random (float a, float b);
*/

char randomAtoZ ();
char randomatoz ();
char random1to9 ();
char randomWellFormed();


bool random1in (int n); // e.g. random1in(5) is likely to return true 1/5th fo the time randomly
bool randomMinN (int m, int n);

}		//	maths
}		//	aab
#endif	//	AAB_MATHS_RANDOM_METHODS
