
/**
*
*	gradient_timer.hpp
*
**/

#if !defined(AAB_TIME_GRADIENT_TIMER_CLASS)
#define AAB_TIME_GRADIENT_TIMER_CLASS
#include"time_reporter.hpp"
#include"../types/smart_ptr.hpp"
//#include"ticker.hpp"
//#include<exception>
//#include<stdexcept>
namespace aab	{
namespace time	{

class GradientTimer//: public Ticker
{
	protected:

        TimeReporter::Ptr report;
		double timeInThisFrame;
		double frameLength;
		double ratio;
		
		void assertFrameLength ();//std::invalid_argument 

	public:

	typedef aab::types::Smart <GradientTimer>::Ptr Ptr;

	explicit GradientTimer (TimeReporter::Ptr report, double frameLength = 0xffffff); //std::invalid_argument 

	virtual ~GradientTimer () throw ();

	virtual void update ();
	double getFrameLength () const { return frameLength; }
	TimeReporter::Ptr getTimeReporterPtr () const { return report; }
	
	inline void setFrameLength (double frameLength) ;//std::invalid_argument 
	
	double getRatio() const { return ratio; }
	
	inline void setToStart ();
		
};

inline
void GradientTimer::setFrameLength (double frameLengthIn) //std::invalid_argument 
{
	frameLength = frameLengthIn;
	assertFrameLength ();
}

inline
void GradientTimer::setToStart ()
{
    timeInThisFrame = 0;
    ratio = 0.0;
}

}		//	time
}		//	aab
#endif	//	AAB_TIME_GRADIENT_TIMER_CLASS




