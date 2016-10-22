
/**
*
*	object_ticker.hpp
*
*   An ObjectTicker provides animation information for a mapping of frames,
    similar to a MappedCounter, only with an ObjectTicker the length of each
    frame can be unique, meaning that it ticks uniquely for each frame
    rather than simply counting through the frames at a regular interval.
    Useful in a wider range of animation contexts than the other
    tickers/counters
*    
**/

#if !defined(AAB_TIME_OBJECT_TICKER_CLASS)
#define AAB_TIME_OBJECT_TICKER_CLASS
#include"ticker.hpp"
//#include<exception>
//#include<stdexcept>
#include<vector>
namespace aab	{
namespace time	{

class ObjectTick
{
    public:
    
        explicit ObjectTick (const int frame_in, const int length_in): frame(frame_in), length(length_in)
        {
            //do nothing //
        }
    
        int frame;
        int length;
};

class ObjectTicker: public Ticker
{
    public:
        typedef std::vector<ObjectTick> TickMapping;
	
	protected:

        TickMapping tickMapping;
        int defaultFrameLength;

	public:

	typedef aab::types::Smart <ObjectTicker>::Ptr Ptr;

	explicit ObjectTicker (TimeReporter::Ptr report, const int defaultFrameLength = 60);//_DEBUG std::invalid_argument

	virtual ~ObjectTicker ();// throw ();

	void update ();

	int getFrame () const;
	
	int getCurrentFrameLength() const;
	
	virtual int getAnimationLength() const;

	
    void addTick (const ObjectTick);
    void addTick (const int frame, const int length = -1);
    
    virtual void setIndexRange (int min, int max);//_DEBUG std::invalid_argument

    int getTickCount () const { return tickMapping.size(); }
    
    // call after direct edits to the vector to set min to 0 and max to the end of the size of the vector
    void resetIndexRange() { min = 0; max = tickMapping.size() - 1; if (frameIndex >= max) {frameIndex = max;} };
    TickMapping & accessTickMap() { return tickMapping; }
    
    void clearTicks() { tickMapping.clear(); resetIndexRange(); }
    
    void setDefaultFrameLength(const int defaultFrameLengthIn) { defaultFrameLength = defaultFrameLengthIn; };

};



}		//	time
}		//	aab
#endif	//	AAB_TIME_OBJECT_TICKER_CLASS




