
/**
*
*
*
**/

#include"delta_time.hpp"
#include"time_method.hpp"
namespace aab	{
namespace time	{


DeltaTime::DeltaTime (double expectedFps)
{
	this-> fpi = 5;
	this-> framesThisFpi = 0;
	this-> last = getMilliseconds ();
	this-> expectedChange = expectedFps / 1000.0;
	this-> delta = 1.0;
	this-> min = 0;
	this-> max = 0;
	this-> multiplier = this-> expectedChange / this-> fpi;
}

double DeltaTime::getChange () const
{
	return delta;
}

unsigned int DeltaTime::getFpi () const
{
	return this-> fpi;
}

double DeltaTime::getExpectedFps () const
{
	return 1000.0 * this-> expectedChange;
}

double DeltaTime::getMin () const
{
	return this-> min;
}

double DeltaTime::getMax () const
{
	return this-> max;
}

bool DeltaTime::isBounded () const
{
	return this-> min != 0 || this-> max != 0;
}


void DeltaTime::setFpi (unsigned int fpi)
{
	this-> fpi = fpi;
	this-> multiplier = this->expectedChange / this-> fpi;
}

void DeltaTime::setExpectedFps (double fps)
{
	this-> expectedChange = fps/1000.0;
	this-> multiplier = this-> expectedChange / this-> fpi;
}

void DeltaTime::setBound (double  min, double max)
{
	this-> min = min;
	this-> max = max;
}

void DeltaTime::removeBound ()
{
	setBound (0, 0);
}

void DeltaTime::setMin (double  min)
{
	this-> min = min;
}


void DeltaTime::setMax (double max)
{
	this-> max = max;
}


void DeltaTime::update ()
{

	++framesThisFpi;

	if (framesThisFpi >= fpi)
	{
		framesThisFpi = 0;

		// update delta:

		unsigned int current = getMilliseconds ();


		// we want to make delta the amount that a movement will
		//	have to be multiplied by in order to satisfy the desired
		// movement within that interval of time.

		delta = (double)(current - last) * (multiplier);
		//delta/= (double) fpi;

		if (delta < min) delta = min;
		if (delta > max && max > 0) delta = max;

		last = current;
	}

}

void DeltaTime::updateTo(unsigned int current)
{
	++framesThisFpi;

	if (framesThisFpi >= fpi)
	{
		framesThisFpi = 0;

		// update delta:

		// we want to make delta the amount that a movement will
		//	have to be multiplied by in order to satisfy the desired
		// movement within that interval of time.

		delta = (double)(current - last) * (multiplier);
		//delta/= (double) fpi;

		if (delta < min) delta = min;
		if (delta > max && max > 0) delta = max;

		last = current;
	}
}


}		//	time
}		//	aab





