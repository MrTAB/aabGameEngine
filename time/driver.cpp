
/**
*
*	driver.cpp
*
*	tests the units in the time package.
*	also serves as a usefull example of use.
*
**/


#include"time.hpp"
#include"cap.hpp"
#include"fps.hpp"
#include"delta_time.hpp"
#include<cmath>
#include<iostream>


int main ()
{
	using std::cout;
	using namespace aab::time;

	Fps fps;

	Cap cap (5);

	cap.setMinimumFPS (60);
	cap.setSleepInterval (10);

	DeltaTime deltaTime (60); //expect 60 frames per second
	deltaTime.setFpi (20);
	deltaTime.setBound (0.3, 3.00);

	while (1)
	{
		cout << getMilliseconds () << "\tfps: " << fps.update () << "\tdelta: " << deltaTime.getChange() << "\n";

		cap.wait ();
		deltaTime.update ();
	}


	return 0;
}
