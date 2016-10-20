
/**
*
*	ticker.cpp
*
**/

#include"ticker.hpp"
#include"../test/debug_assertions.hpp"
#include"../test/exceptions.hpp"
#include<algorithm>
namespace aab	{
namespace time	{


Ticker::Ticker (TimeReporter::Ptr report, int min, int max):
//	_DEBUG std::invalid_argument
	report (report),
	timeInThisFrame (0),
	frameIndex (min),
	min (min),
	max (max),	
	rolledBack(false),
	rollOverType(seek_roll)
{

	if (min > max || min < 0)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::Ticker::Ticker: min cannot be less than max, and min must be positive"));
		_RELEASE_RESPONSE(min =  max = 0);
	}
}



Ticker::~Ticker () //throw ()
{
    // do nothing //
}




void Ticker::setIndexRange (int min, int max)// _DEBUG std::invalid_argument
{
	if (min > max || min < 0)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::Ticker::setIndexRange: min cannot be less than max, and min must be positive"));
		_RELEASE_RESPONSE(min = max = 0);
	}

	this-> min = min;
	this-> max = max;

    if (frameIndex < min || frameIndex > max)
    {
        setToStart ();
    }
}

void Ticker::setToStart ()
{
	frameIndex = min;
	timeInThisFrame = 0;
	rolledBack = false;
}

void Ticker::setToEnd ()
{
	frameIndex = max;
	timeInThisFrame = 0;
	rolledBack = true;
}

void Ticker::seekToIndex (int frame, SeekPolicy seekPolicy)// std::invalid_argument
{
	assertSeekPolicy (frame, seekPolicy);

	frameIndex = frame;
	timeInThisFrame = 0;
}

void Ticker::seekIntoIndex (int frame, SeekPolicy seekPolicy)// std::invalid_argument
{
	assertSeekPolicy (frame, seekPolicy);

	frameIndex = frame;
}


void Ticker::assertSeekPolicy (int&frame, SeekPolicy seekPolicy)// std::invalid_argument
{
	switch (seekPolicy)
	{
		case seek_error:
		{
			if (frame < min || frame > max)
			{
				throw std::invalid_argument ("aab::time::Ticker::assertSeekPolicy: invalid frame value");
			}
		}
		break;

		case seek_bound:
		{
			frame = std::max (std::min (frame, max), min);
		}
		break;

		case seek_roll:
		{
			if (frame > max)
			{
				frame = min + ((frame - min) % (max - min + 1));
			}
		}
		break;

		default:
		{
			_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::Ticker::assertSeekPolicy: invalid seek policy"));
			_RELEASE_RESPONSE(assertSeekPolicy(frame, seek_bound));
		}
	}
}


}		//	time
}		//	aab





