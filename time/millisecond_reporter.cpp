
/**
*
*	millisecond_reporter.cpp
*
**/

#include"millisecond_reporter.hpp"
#include"time_method.hpp"
namespace aab	{
namespace time	{

MillisecondReporter::MillisecondReporter () : last (getMilliseconds ()), change (0)
{
	/* nothing */
}

void MillisecondReporter::update ()
{
	unsigned int now = getMilliseconds ();

	change = now - last;

	last = now;
}

void MillisecondReporter::updateTo (unsigned int now)
{
	change = now - last;

	last = now;
}


double MillisecondReporter::getChange () const
{
	return change;
}

}		//	time
}		//	aab





