
/**
*
*	sub_animator.hpp
*
*	A SubAnimator is a state recorder which stores animation details so that
    they can be switched in and out easily.
*
**/

#if !defined(AAB_TIME_SUB_ANIMATOR)
#define AAB_TIME_SUB_ANIMATOR
#include"frame_ticker.hpp"
namespace aab	{
namespace time	{


enum
{
    SUBANIMATOR_USE_MIN_FRAME = -1
};

class SubAnimator
{
	double frameLength;
	int startIndex; // negative if not using
	int min, max; // inclusive

	public:

	explicit SubAnimator(int minIn, int maxIn, double frameLengthIn = 60, int startIndexIn = SUBANIMATOR_USE_MIN_FRAME) ;// _DEBUG std::invalid_argument

	void setRangeStarting (int min, int max, int frame = SUBANIMATOR_USE_MIN_FRAME);// _DEBUG std::invalid_argument
	void setRange (int min, int max);// _DEBUG std::invalid_argument
	void setFrameLength (double frameLength);// _DEBUG std::invalid_argument
	void setStartFrame(int frame);// _DEBUG std::invalid_argument
	void setStartToMin();
	void set (aab::time::FrameTicker::Ptr);// _DEBUG std::invalid_argument
	void applyTo (aab::time::FrameTicker::Ptr);// _DEBUG std::invalid_argument

	int getMax() const { return max; }

};



}		//	time
}		//	aab
#endif	//	AAB_TIME_SUB_ANIMATOR




