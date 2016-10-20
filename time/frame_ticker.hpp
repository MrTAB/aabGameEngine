
/**
*
*	frame_ticker.hpp
*
*	update should be called in harmony with that of the TimeReporters.
*	Not calling update effectively pauses the FrameTicker.
*
*	FrameTicker counts up the values stored on its check of
*	TimeReporters::getChange. Once the value stored is over frameLength
*	in size, the frame is increased, and the time inbetween this frames start
*   time and the next is stored so that there is no delays. If time moves on,
*   several frames may be counted forward. Works well within a game using
*   delta time as well as one without
*
*	A millisecond reporter can be used, but for more efficient game coverage,
*	a better system might have the time reporter update frame tickers by one when
*	one unit of time (as that reporter sees it) has passed. This would combine
*	all checks for say things that happen 5 times per second, together, by allowing
*	the game programmer to use the same timer reporter and different frame tickers
**/

#if !defined(AAB_TIME_FRAME_TICKER_CLASS)
#define AAB_TIME_FRAME_TICKER_CLASS
#include"ticker.hpp"
//#include<exception>
//#include<stdexcept>
namespace aab	{
namespace time	{

class FrameTicker: public Ticker
{
	protected:

		double frameLength;
		
		void assertFrameLength ();//std::invalid_argument 

	public:

	typedef aab::types::Smart <FrameTicker>::Ptr Ptr;

	explicit FrameTicker (TimeReporter::Ptr report, double frameLength = 0xffffff, int min = 0, int max = 0); //std::invalid_argument 

	virtual ~FrameTicker () throw ();

	virtual void update ();
	virtual int getFrame () const;
	double getFrameLength () const;
	virtual int getAnimationLength() const {return getFrameLength()*(1+getMax()-getMin());}
	
	void setFrameLength (double frameLength) ;//std::invalid_argument 
		
};



}		//	time
}		//	aab
#endif	//	AAB_TIME_FRAME_TICKER_CLASS




