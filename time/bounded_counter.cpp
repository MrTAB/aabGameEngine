
/**
*
*	bounded_counter.cpp
*
**/

#include"bounded_counter.hpp"
#include"../test/debug_assertions.hpp"
#include"../test/exceptions.hpp"
#include<algorithm>
#include<cassert>
namespace aab	{
namespace time	{


BoundedCounter::BoundedCounter (int min, int max):
//	_DEBUG std::invalid_argument
	frameIndex (min),
	min (min),
	max (max),	
	rolledBack(false),
	callback(0),
	rollOverType(seek_roll)
{

	if (min > max || min < 0)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::BoundedCounter::BoundedCounter: min cannot be less than max, and min must be positive"));
		_RELEASE_RESPONSE(min =  max = 0);
	}
}



BoundedCounter::~BoundedCounter () //throw ()
{
    if (callback)
    {
        delete callback;
    }
}


void BoundedCounter::setIndexRange (int minIn, int maxIn)// _DEBUG std::invalid_argument
{
	if (minIn > maxIn || minIn < 0)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::BoundedCounter::setIndexRange: min cannot be less than max, and min must be positive"));
		_RELEASE_RESPONSE(min = max = 0);
	}

	this-> min = minIn;
	this-> max = maxIn;

    if (frameIndex < minIn || frameIndex > maxIn)
    {
        setToStart ();
    }
}

void BoundedCounter::setToStart ()
{
	frameIndex = min;
	rolledBack = false;
	
	if (callback)
        (*callback)(getFrame());
}

void BoundedCounter::setToEnd ()
{
	frameIndex = max;	
	rolledBack = true;
	
	if (callback)
        (*callback)(getFrame());
}

void BoundedCounter::seekToIndex (int frame, SeekPolicy seekPolicy)// std::invalid_argument
{
	assertSeekPolicy (frame, seekPolicy);

	frameIndex = frame;
	
	if (callback)
        (*callback)(getFrame());
}

void BoundedCounter::seekIntoIndex (int frame, SeekPolicy seekPolicy)// std::invalid_argument
{
	assertSeekPolicy (frame, seekPolicy);

	frameIndex = frame;
	
	if (callback)
        (*callback)(getFrame());
}


void BoundedCounter::assertSeekPolicy (int&frame, SeekPolicy seekPolicy)// std::invalid_argument
{
	switch (seekPolicy)
	{
		case seek_error:
		{
			if (frame < min || frame > max)
			{
				throw std::invalid_argument ("aab::time::BoundedCounter::assertSeekPolicy: invalid frame value");
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
			_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::BoundedCounter::assertSeekPolicy: invalid seek policy"));
			_RELEASE_RESPONSE(assertSeekPolicy(frame, seek_bound));
		}
	}
}


void BoundedCounter::notifyFrameIncrease(const int increase)
{    
    if (callback)
    {
        int oldFrameIndex = frameIndex;
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
        
        if (oldFrameIndex != frameIndex)
        {
            (*callback)(getFrame());
        }
    }
    else
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
}

void BoundedCounter::setCallback(Callback * callbackIn)
{
    assert(callbackIn);
    
    if (callback)
    {
        delete callback;
    }
    
    callback = callbackIn;
}

BoundedCounter::Callback * BoundedCounter::removeCallback()
{
    assert(callback);
    Callback * callbackOut = callback;
    callback = 0;
    return callbackOut;
}

}		//	time
}		//	aab





