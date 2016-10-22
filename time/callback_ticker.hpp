
/**
*
*   @file callback_ticker.hpp
*
*	Invokes user defined callback every time a frame ticks over.
*
*	CallbackTicker counts up the values stored on its check of
*	TimeReporters::getChange. Once the value stored is over frameLength
*	in size, the callback is invoked, and the time inbetween this frames start
*   time and the next is stored so that there is no delays. If time moves on,
*   several increases in frame will be reported: this is why the callback has a
*   count argument. In normal use count should be one, but this may not always be true.
*
*	A millisecond reporter can be used, but for more efficient game coverage,
*	a better system might have the time reporter update tickers by one when
*	one unit of time (as that reporter sees it) has passed. This would combine
*	all checks for say things that happen 5 times per second, together, by allowing
*	the game programmer to use the same timer reporter and different tickers.
*
*	Update should be called in harmony with that of the TimeReporters.
*	Not calling update effectively pauses the ticker.
*
*   Note that because a CallbackTicker does not have a notion of frames, it
*   cannot extend Ticker. This is because Ticker is fundamentally an animation
*   ticker. CallbackTicker is a more abstract ticker, and yet Ticker has no
*   actual counting mechanism.
*
**/

#if !defined(AAB_TIME_CALLBACK_TICKER_CLASS)
#define AAB_TIME_CALLBACK_TICKER_CLASS
#include"time_reporter.hpp"
#include"../types/smart_ptr.hpp"
namespace aab	{
namespace time	{

class CallbackTicker
{
    private:
        CallbackTicker(CallbackTicker&); //no-copy
        
	public:

    /** Utility smart pointer typedef.
    */
	typedef aab::types::Smart <CallbackTicker>::Ptr Ptr;	
	
	/** The Callback base class.
	*   Extend Callback implementing operator()(int frameCount) and provide an
	*   instance to a CallbackTicker to receive reports of frame increases.
    *   Example:
    *
    *    class MyTickedCallback : aab::time::CallbackTicker::TickedCallback
    *    {
    *        void operator()(int ticks)
    *        {
    *            // update animations by ticks frames.
    *        }
    *    }
	*/
	struct Callback 
	{
	    /** Callback operator.
	    * Implement operator()(int frameCount) to receive messages from the CallbackTicker.
	    * @param frameCount tells the callback how many animation frames to update their animation.
	    */
        virtual void operator()(int frameCount) = 0;
	};
	
	protected:

        TimeReporter::Ptr report; /**< Smart pointer to report providing a sense of time to the CallbackTicker. */
        Callback * callback;      /**< Pointer to the callback. User supplies a pointer to a subclass. CallbackTicker takes ownership of the Callback, so user should access it via CallbackTickers methods. */
        double frameLength;       /**< The length of a frame is entirely with respect to the TimeReporter. */
		double timeInThisFrame;   /**< Used in update() to track how far the ticker is into this frame, allowing rollovers to be accounted for. */
		
		/** Internal method for checking that supplied frame lengths are valid.
		*/
		void assertFrameLength ();//std::invalid_argument

	public:

    /** Constructor. May throw std::invalid_argument if frameLength is invalid.
    * @param Smart pointer to TimeReporter providing a sense of time to the CallbackTicker. Share the same one throughout your tickers for equal notion of the passage of time.
    * @param Pointer to an instance of a subclass of Callback; ownership will be taken by the CallbackTicker, so access the callback only through the CallbackTicker.
    * @param The length of the frame in units of time. Units of time is dependant on the TimeReporter. Example usage is for TimeReporter to report milliseconds, and frameLengths to be in milliseconds. Alternative use is to have TimeReport report in expected frames per second, allowing frameLength to be defined as the ideal number of frames that will have passed.
    * @see getCallback()
    */
	CallbackTicker (TimeReporter::Ptr, Callback*, const double frameLength); //std::invalid_argument 

    /** Deconstructor.
    * Deletes the callback provided to CallbackTicker. Does not throw
    * @see CallbackTicker(TimeReporter::Ptr, Callback*, const double frameLength)
    */
	virtual ~CallbackTicker ();// throw ();

    /** Updates the ticker, potentially invoking a callback.
    * Call after each update to the TimeReporter. update() will check how much time has passed, and if the boundary of n frames has been passed, Callback will be invoked with n as an argument.
    */
	void update ();
	
    /** Use to change the length of the frames that the Ticker is checking.
    * @param The length of a frame is entirely with respect to the TimeReporter. May throw std::invalid_argument if frameLength is invalid.
    */
	void setFrameLength (double frameLength);//std::invalid_argument 
	
	
    /** Get smart pointer to TimeReporter object used by this ticker.
    * @return The TimeReporter being used by this ticker.
    */
	inline TimeReporter::Ptr getTimeReporterPtr () const;
	
    /** Get pointer to this tickers Callback object.    
    * @return pointer to the Callback object maintained by this CallbackTicker. 
    * @warning Do not delete the callback.
    */
    inline Callback * getCallback();
    
    /** Get the frame length in use by this CallbackTicker.
    * @return Length of the frames used by the CallbackTicker
    * @see setFrameLength(double frameLength)
    */
	inline double getFrameLength () const;	
};



inline
TimeReporter::Ptr CallbackTicker::getTimeReporterPtr () const
{
    return report;
}

inline 
CallbackTicker::Callback * CallbackTicker::getCallback()
{
    return callback;
}

inline
double CallbackTicker::getFrameLength () const
{
	return frameLength;
}



}		//	time
}		//	aab
#endif	//	AAB_TIME_CALLBACK_TICKER_CLASS




