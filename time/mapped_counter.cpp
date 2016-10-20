
/**
*
*	mapped_counter.cpp
*
**/

#include"mapped_counter.hpp"
#include"../test/exceptions.hpp"
#include"../test/debug_assertions.hpp"
#include<algorithm>
#include<cassert>
namespace aab	{
namespace time	{



MappedCounter::MappedCounter (int min, int max): BoundedCounter(min, max)
{
    // do nothing //
}



MappedCounter::~MappedCounter ()// throw ()
{
    // do nothing //
}



int MappedCounter::getFrame () const
{
    if (frameMapping.empty())
    {
        assert(false && "empty counter has no frames.");
        return 0;
    }
    
	return frameMapping[frameIndex];
}


void MappedCounter::addFrame(const int frame)
{
    //todo check frame for being positive
    //todo check length for being positive
    
    if (min == 0 && (0==max || max == frameMapping.size() - 1))
    {
        ++max;
    }
    frameMapping.push_back(frame);
    
}


void MappedCounter::setIndexRange (int min_in, int max_in) //_DEBUG std::invalid_argument
{
	if (min_in > max_in || min_in < 0)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::MappedCounter::setIndexRange: min cannot be less than max, and min must be positive."));
		_RELEASE_RESPONSE(min_in = max_in = 0);
	}
	
	if (max_in >= frameMapping.size())
	{
        _DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::MappedCounter::setIndexRange: max cannot be greater than the number of ticks."));
        _RELEASE_RESPONSE(max_in = (frameMapping.empty()? 0 : frameMapping.size() - 1));
	}

	this-> min = min_in;
	this-> max = max_in;

    if (frameIndex < min_in || frameIndex > max_in)
    {
        setToStart ();
    }
}



/*


MappedCounter::MappedCounter (int min, int max): BoundedCounter(min, max)
{
    min = max = frameIndex = 0;
    rolledBack = false;
}



MappedCounter::~MappedCounter ()// throw ()
{
    // do nothing //
}



void MappedCounter::notifyFrameIncrease(const int increase)
{
    frameIndex += increase;

    if (frameIndex > max)
    {
        rolledBack = true;
        if (isLoopEnabled())
        {
            frameIndex = min + ((frameIndex - min) % (max - min + 1));
        }
        else
        {
            frameIndex = max;
        }
    }
}



int MappedCounter::getFrame () const
{
    if (frameMapping.empty())
    {
        assert(false && "empty counter has no frames.");
        return 0;
    }
    
	return frameMapping[frameIndex];
}


void MappedCounter::addFrame(const int frame)
{
    //todo check frame for being positive
    //todo check length for being positive
    
    if (min == 0 && (0==max || max == frameMapping.size() - 1))
    {
        ++max;
    }
    frameMapping.push_back(frame);
    
}


void MappedCounter::setIndexRange (int min_in, int max_in) //_DEBUG std::invalid_argument
{
	if (min_in > max_in || min_in < 0)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::ObjectTick::setIndexRange: min cannot be less than max, and min must be positive."));
		_RELEASE_RESPONSE(min_in = max_in = 0);
	}
	
	if (max_in >= frameMapping.size())
	{
        _DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::ObjectTick::setIndexRange: max cannot be greater than the number of ticks."));
        _RELEASE_RESPONSE(max_in = (frameMapping.empty()? 0 : frameMapping.size() - 1));
	}

	this-> min = min_in;
	this-> max = max_in;

    if (frameIndex < min_in || frameIndex > max_in)
    {
        setToStart ();
    }
}



int MappedCounter::getMin () const
{
	return min;
}

int MappedCounter::getMax () const
{
	return max;
}



void MappedCounter::setToStart ()
{
	frameIndex = min;
	rolledBack = false;
}

void MappedCounter::setToEnd ()
{
	frameIndex = max;	
	rolledBack = true;
}

void MappedCounter::seekToIndex (int frame, SeekPolicy seekPolicy)// std::invalid_argument
{
	assertSeekPolicy (frame, seekPolicy);

	frameIndex = frame;
}

void MappedCounter::seekIntoIndex (int frame, SeekPolicy seekPolicy)// std::invalid_argument
{
	assertSeekPolicy (frame, seekPolicy);

	frameIndex = frame;
}


void MappedCounter::assertSeekPolicy (int frame, SeekPolicy seekPolicy)// std::invalid_argument
{
	switch (seekPolicy)
	{
		case seek_error:
		{
			if (frame < min || frame > max)
			{
				throw std::invalid_argument ("aab::time::MappedCounter::assertSeekPolicy: invalid frame value");
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
			_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::MappedCounter::assertSeekPolicy: invalid seek policy"));
			_RELEASE_RESPONSE(assertSeekPolicy(frame, seek_bound));
		}
	}
}


*/

}		//	time
}		//	aab





