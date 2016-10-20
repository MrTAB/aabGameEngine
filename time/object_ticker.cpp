
/**
*
*	object_ticker.cpp
*
**/

#include"object_ticker.hpp"
#include"../test/exceptions.hpp"
#include"../test/debug_assertions.hpp"
#include<algorithm>
namespace aab	{
namespace time	{


//todo - Ticker SetRange is not valid for our purposes


ObjectTicker::ObjectTicker (TimeReporter::Ptr report, const int defaultFrameLengthIn):
//_DEBUG std::invalid_argument
    Ticker(report), defaultFrameLength(defaultFrameLengthIn)
{
    max = 0;
    
    if (defaultFrameLength < 0)
    {
        _DEBUG_THROW(std::invalid_argument("ObjectTicker::ObjectTicker::\t defaultFrameLength cannot be negative.\n"));
        _RELEASE_RESPONSE(defaultFrameLength = 0);
    }
}



ObjectTicker::~ObjectTicker ()// throw ()
{
    // do nothing //
}

void ObjectTicker::update ()
{
    // todo change? required?
    
	timeInThisFrame += report-> getChange ();
	
    while (timeInThisFrame > tickMapping[frameIndex].length)
    {
        timeInThisFrame -= tickMapping[frameIndex].length;
        ++frameIndex;
        
        if (frameIndex > max)
        {
            rolledBack = true;
		    if (isLoopEnabled())
		    {
                frameIndex = min;
		    }
		    else
		    {
		        frameIndex = max;
		        //break;
		        // todo - any reason not to break here
		    }
        }
    }
}


int ObjectTicker::getFrame () const
{
    if (tickMapping.empty())
    {
        return 0;
    }
    
	return tickMapping[frameIndex].frame;
}

int ObjectTicker::getCurrentFrameLength () const
{
    if (tickMapping.empty())
    {
        return 0;
    }
    
	return tickMapping[frameIndex].length;
}

void ObjectTicker::addTick(const ObjectTick objectTick)
{
    //todo check frame for being positive
    //todo check length for being positive
    
    if (min == 0 && (0 == max || max == tickMapping.size() - 1))
    {
        ++max;
    }
    tickMapping.push_back(objectTick);
    
}

int ObjectTicker::getAnimationLength() const
{
    TickMapping::const_iterator itr = tickMapping.begin();
    int total = 0;
    for(;itr!=tickMapping.end();++itr)
    {
        total += itr->length;
    }
    return total;
}

void ObjectTicker::addTick (const int frame, const int length)
{
    addTick(ObjectTick(frame,length < 0? defaultFrameLength: length));
}

void ObjectTicker::setIndexRange (int min_in, int max_in) //_DEBUG std::invalid_argument
{
	if (min_in > max_in || min_in < 0)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::ObjectTick::setIndexRange: min cannot be less than max, and min must be positive."));
		_RELEASE_RESPONSE(min_in = max_in = 0);
	}
	
	if (max_in >= tickMapping.size())
	{
        _DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::ObjectTick::setIndexRange: max cannot be greater than the number of ticks."));
        _RELEASE_RESPONSE(max_in = (tickMapping.empty()? 0 : tickMapping.size() - 1));
	}

	this-> min = min_in;
	this-> max = max_in;

    if (frameIndex < min_in || frameIndex > max_in)
    {
        setToStart ();
    }
}






}		//	time
}		//	aab





