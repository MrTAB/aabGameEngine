
/**
*
*	ticker.hpp
*
*   Abstract ticker class: various tickers share its basic behaviour to change
*   some Discrete Tick value based on time. A tickers tick value moves from one
*   starting value to a final value.
*
*   The Tick value moves onto the next tick value once a predetermined amount of
*   time has passed. After moving on from the final value, the ticker may loop
*   (reset) or stick at the final frame.
*
*   Tick values are integers: their ordering in terms of the starting value to
*   the final value are dependant on the subclass implementation.
*
*   A TimeReporter tells the ticker how much time has passed.
*   
*
**/

#if !defined(AAB_TIME_TICKER_CLASS)
#define AAB_TIME_TICKER_CLASS
#include"time_reporter.hpp"
#include"../types/smart_ptr.hpp"
//#include<exception>
//#include<stdexcept>
namespace aab	{
namespace time	{

//abstract
class Ticker
{
	protected:


		TimeReporter::Ptr report;
		double timeInThisFrame;
		int frameIndex;
		int min, max; // inclusive	
		bool rolledBack;	

	public:

	typedef aab::types::Smart <Ticker>::Ptr Ptr;

	enum SeekPolicy
	{
		seek_error,
		seek_bound,
		seek_roll
	};
	


	explicit Ticker (TimeReporter::Ptr report, int min = 0, int max = 0); //_DEBUG std::invalid_argument

	virtual ~Ticker ();// throw ();

	virtual void update () = 0;
	virtual int getFrame() const = 0;
	virtual int getAnimationLength() const = 0;
    inline int getIndex() const;

	inline int getMin () const;
	inline int getMax () const;
	inline TimeReporter::Ptr getTimeReporterPtr () const;

	virtual void setIndexRange (int min, int max);//_DEBUG std::invalid_argument
	void setToStart ();
	void setToEnd ();
	void seekToIndex (int frame, SeekPolicy s = seek_error);//std::invalid_argument
	void seekIntoIndex (int frame, SeekPolicy s = seek_error) ;//std::invalid_argument
	
	inline void enableLoop();
	inline void disableLoop();
	inline bool isLoopEnabled()const;

    /**
    *   Use these to check wether the animation has passed its final frame and been forced to roll back, either to the start (if looping) or back to the last frame (if looping is disabled)
    *   This is useful if you are looking to implement subsequent animations only when the current animation has finished.
    *   It is the responsibility of any Ticker subclass to update rolledBack in their update() method.
    *   Some methods such as setToStart will reset rolledBack
    */
    inline bool hasRolledBack()const;
    inline void forceRolledBack(const bool rolledBackIn = true);
    
    virtual void forceFrameAndBounds(const int frame) { min=max=frameIndex = frame;};

	protected:

		void assertSeekPolicy (int&frame, SeekPolicy);// std::invalid_argument
		SeekPolicy rollOverType;
};


inline
TimeReporter::Ptr Ticker::getTimeReporterPtr () const
{
	return report;
}

inline int Ticker::getIndex() const
{
    return frameIndex-min;
}
inline void Ticker::enableLoop()
{
    rollOverType = seek_roll;
}
inline void Ticker::disableLoop()
{
    rollOverType = seek_bound;
}
inline bool Ticker::isLoopEnabled()const
{
    return seek_roll == rollOverType;
}
inline bool Ticker::hasRolledBack()const
{
    return rolledBack;
}
inline void Ticker::forceRolledBack(const bool rolledBackIn)
{
    rolledBack = rolledBackIn;
}

inline int Ticker::getMin () const
{
	return min;
}

inline int Ticker::getMax () const
{
	return max;
}

}		//	time
}		//	aab
#endif	//	AAB_TIME_TICKER_CLASS




