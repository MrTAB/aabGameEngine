
/**
*
*	cap.cpp
*
*	Could modify to use totalling of a double on each update -> more accurate fps result
**/

#include"cap.hpp"
#include"time_method.hpp"
#include<cmath>
namespace aab	{
namespace time	{



Cap::Cap (float fps)
{
	this-> sleepWait = 0.f;	
	this-> last = getMilliseconds ();
	setMaximumFPS(fps);
}

Cap::~Cap ()// throw ()
{
    // do nothing //
}

void Cap::wait ()
{
	float current = getMilliseconds ();
	float target = last + this-> min;

	if (current < target)
	{
		if (sleepWait > 0.f)
		{
			//do
			//{
			//	delay (this-> sleepWait);
			//}
			//while (getMilliseconds () < target);

			if (target - current > sleepWait)
			{
				delay (0.8f * (target - current));
			}

			while (getMilliseconds () < target)
			{
				/* do nothing */
			}

		}
		else
		{
			while (getMilliseconds () < target)
			{
				/* do nothing */
			}
		}
		
        last = target;
	}
	else
	{
	    last = current;
	}

	
}



void Cap::setMinimumSleepInterval (float milliseconds)
{
	this-> sleepWait = milliseconds;
}


void Cap::setMinimumLapse (float milliseconds)
{
	this-> min = milliseconds;
}

void Cap::setMaximumFPS (float fps)
{
	//this-> min = (unsigned int) std::floor (0.5 + 1000.0 / (double) fps); // must round the number
	min = 1000.f/fps - 0.5f;
}


}		//	time
}		//	aab





