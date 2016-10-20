
/**
*
*	frame_ticker.cpp
*
**/

#include"callback_ticker.hpp"
#include"../test/exceptions.hpp"
#include"../test/debug_assertions.hpp"
#include<algorithm>
#include<cassert>
namespace aab	{
namespace time	{


CallbackTicker::CallbackTicker (TimeReporter::Ptr reportIn, Callback*callbackIn, double frameLengthIn):
//std::invalid_argument 
    report(reportIn),
    callback(callbackIn),
	frameLength (frameLengthIn),
	timeInThisFrame (0)
{
    assert(callback);
	assertFrameLength ();
}


CallbackTicker::~CallbackTicker () //throw ()
{
    assert(callback && "Sub class has failed to define a callback, or data corruption has occurred.");
    delete callback;
}

void CallbackTicker::update ()
{
	timeInThisFrame += report-> getChange ();

	if (timeInThisFrame > frameLength)
	{
		// ok now we are up a frame (or several):

		int increase = static_cast <const int> (timeInThisFrame/frameLength);

		// and reset time by the number of frames we've covered:

		timeInThisFrame -= increase * frameLength;

        assert(callback && "Sub class has failed to define a callback, or data corruption has occurred.");
        
		(*callback)(increase);
	}

}



void CallbackTicker::setFrameLength (double frameLength) //std::invalid_argument 
{
	this-> frameLength = frameLength;

	assertFrameLength ();
}


void CallbackTicker::assertFrameLength () //std::invalid_argument 
{
	if (frameLength < 0)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::CallbackTicker::assertFrameLength: frameLength cannot be less than zero"));
		_RELEASE_RESPONSE(frameLength = 1.0f/60.0f);
	}
}



}		//	time
}		//	aab





