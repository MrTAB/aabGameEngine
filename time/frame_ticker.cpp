
/**
*
*	frame_ticker.cpp
*
**/

#include"frame_ticker.hpp"
#include"../test/exceptions.hpp"
#include"../test/debug_assertions.hpp"
#include<algorithm>
namespace aab	{
namespace time	{


FrameTicker::FrameTicker (TimeReporter::Ptr report, double frameLengthIn, int min, int max):
//std::invalid_argument 
	Ticker(report,min,max),
	frameLength (frameLengthIn)
{
	assertFrameLength ();
}


FrameTicker::~FrameTicker () throw ()
{
    // do nothing //
}

void FrameTicker::update ()
{
	timeInThisFrame += report-> getChange ();

	if (timeInThisFrame > frameLength)
	{
		// ok now we are up a frame (or several):

		int increase = static_cast <int> (timeInThisFrame/frameLength);

		// and reset time by the number of frames we've covered:

		timeInThisFrame -= increase * frameLength;

		// now add the frames and rollback if required, adding as you do.

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


int FrameTicker::getFrame () const
{
	return frameIndex;
}


double FrameTicker::getFrameLength () const
{
	return frameLength;
}


void FrameTicker::setFrameLength (double frameLength) //std::invalid_argument 
{
	this-> frameLength = frameLength;

	assertFrameLength ();
}


void FrameTicker::assertFrameLength () //std::invalid_argument 
{
	if (frameLength < 0)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::FrameTicker::assertFrameLength: frameLength cannot be less than zero"));
		_RELEASE_RESPONSE(frameLength = 1.0f/60.0f);
	}
}



}		//	time
}		//	aab





