
/**
*
*	manual_ticker.hpp
*
*   Use when a ticker implementation is required but the animation frame used is
*   controlled manually, ignoring the underlying reporter. Can also just use a StuckTimeReporter (less efficient)
*   
*
**/

#if !defined(AAB_TIME_MANUAL_TICKER_CLASS)
#define AAB_TIME_MANUAL_TICKER_CLASS
#include"ticker.hpp"
//#include<exception>
//#include<stdexcept>
namespace aab	{
namespace time	{

//abstract
class ManualTicker: public Ticker
{
	public:

	typedef aab::types::Smart <ManualTicker>::Ptr Ptr;

	explicit ManualTicker (int max_in = 0):// throw (std::exception &):
        Ticker(TimeReporter::Ptr(new StuckTimeReporter()))
	{
	    min = 0;
	    max = max_in;
	    frameIndex = max_in;
	}
	
	ManualTicker (int min_in, int max_in):// throw (std::exception &):
        Ticker(TimeReporter::Ptr(new StuckTimeReporter()))
	{
	    min = min_in;
	    max = max_in;
	    frameIndex = min;
	}


	virtual ~ManualTicker () throw () { }

	virtual void update () { }
	virtual int getFrame() const { return frameIndex; }
	virtual int getAnimationLength() const {return 20000000;}
	
	virtual void forceFrameAndBounds(const int frame) { forceFrame(frame); } 
	void forceFrame(const int frame) { min=max=frameIndex = frame;};

};

inline ManualTicker::Ptr makeManualTickerPtr(int max_in = 0)
{
    ManualTicker::Ptr ptr (new ManualTicker(max_in));
    return ptr;
}

inline ManualTicker::Ptr makeManualTickerPtr(int min_in, int max_in)
{
    ManualTicker::Ptr ptr (new ManualTicker(min_in, max_in));
    return ptr;
}

}		//	time
}		//	aab
#endif	//	AAB_TIME_MANUAL_TICKER_CLASS




