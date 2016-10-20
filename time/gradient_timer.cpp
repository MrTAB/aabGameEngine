
/**
*
*	gradient_timer.cpp
*
**/

#include"gradient_timer.hpp"
#include"../test/exceptions.hpp"
#include"../test/debug_assertions.hpp"
#include<algorithm>
namespace aab	{
namespace time	{


GradientTimer::GradientTimer (TimeReporter::Ptr reportIn, double frameLengthIn):
//std::invalid_argument 
    report(reportIn),
	timeInThisFrame (0.0),
	frameLength (frameLengthIn),
	ratio(0.0)
{
	assertFrameLength ();
}


GradientTimer::~GradientTimer () throw ()
{
    // do nothing //
}

void GradientTimer::update ()
{
	timeInThisFrame += report-> getChange ();

	if (timeInThisFrame > frameLength)
	{
		// ok now we are up a frame (or several):

		int increase = static_cast <int> (timeInThisFrame/frameLength);

		// and reset time by the number of frames we've covered:

		timeInThisFrame -= increase * frameLength;

	}
	
	ratio = timeInThisFrame/frameLength;
}


void GradientTimer::assertFrameLength () //std::invalid_argument 
{
	if (frameLength < 0)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::GradientTimer::assertFrameLength: frameLength cannot be less than zero"));
		_RELEASE_RESPONSE(frameLength = 1.0f/60.0f);
	}
}



}		//	time
}		//	aab





