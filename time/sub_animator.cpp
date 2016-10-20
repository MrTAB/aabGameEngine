
/**
*
*	sub_animator.cpp"
*
**/

#include"sub_animator.hpp"
#include"../test/debug_assertions.hpp"
namespace aab	{
namespace time	{




SubAnimator::SubAnimator(int minIn, int maxIn, double frameLengthIn, int startIndexIn) // _DEBUG std::invalid_argument
{
	startIndex = SUBANIMATOR_USE_MIN_FRAME;
	setRangeStarting (minIn, maxIn, startIndexIn);
	setFrameLength(frameLengthIn);
}

void SubAnimator::setRangeStarting (int minIn, int maxIn, int frame)// _DEBUG std::invalid_argument
{
	setRange (minIn, maxIn);
	if (frame == SUBANIMATOR_USE_MIN_FRAME)
	{
		startIndex = SUBANIMATOR_USE_MIN_FRAME;
	}
	else
	{
		setStartFrame (frame);
	}
}

void SubAnimator::setRange (int minIn, int maxIn)// _DEBUG std::invalid_argument
{
	if (minIn > maxIn || minIn < 0)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::SubAnimator::setRange: min cannot be less than max, and min must be positive"));
		_RELEASE_RESPONSE(minIn = maxIn = 0);
	}

	this-> min = minIn;
	this-> max = maxIn;

	if (startIndex >=0 && (startIndex < min || startIndex > max))
	{
			startIndex = SUBANIMATOR_USE_MIN_FRAME;
	}
}

void SubAnimator::setFrameLength (double frameLengthIn) // _DEBUG std::invalid_argument
{
	if (frameLengthIn < 0)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::SubAnimator::assertFrameLength: frameLength cannot be less than zero"));
		_RELEASE_RESPONSE(frameLengthIn = 0);
	}
	this-> frameLength = frameLengthIn;
}

void SubAnimator::setStartFrame(int frame) // _DEBUG std::invalid_argument
{
	if (frame < min || frame > max)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("aab::time::SubAnimator::setStartFrame: start frame cannot be outside the range [min,max]"));
		_RELEASE_RESPONSE(frame = min);
	}

	startIndex = frame;
}

void SubAnimator::setStartToMin()
{
	startIndex = SUBANIMATOR_USE_MIN_FRAME;
}

void SubAnimator::set (aab::time::FrameTicker::Ptr frameTicker) // _DEBUG std::invalid_argument
{
	setStartToMin ();
	setRange (frameTicker->getMin(),frameTicker->getMax());
	setFrameLength(frameTicker->getFrameLength());
}

void SubAnimator::applyTo (aab::time::FrameTicker::Ptr frameTicker) // _DEBUG std::invalid_argument
{
	frameTicker-> setIndexRange (min,max); // automatically sets frame to start
	if (startIndex >= 0)
	{
		frameTicker-> seekToIndex (startIndex,aab::time::FrameTicker::seek_error);
	}

	frameTicker-> setFrameLength (frameLength);
}




}		//	time
}		//	aab





