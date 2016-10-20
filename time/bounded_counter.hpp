
/**
*
*	bounded_counter.hpp
*
*   For use with a CallbackTicker.
*
*   A BoundedCounter can be updated with the message of how many frams have
*   been counted. It will then keep the frames between those bounds either by
*   looping (reset) or sticking, depending on its fields.
*
*   As a counter, the BoundedCounter has no direct connection to time or time
*   reporters.
*
**/

#if !defined(AAB_TIME_BOUNDED_COUNTER_CLASS)
#define AAB_TIME_BOUNDED_COUNTER_CLASS
namespace aab	{
namespace time	{



class BoundedCounter
{
    private:
        BoundedCounter(BoundedCounter&); //no-copy
        
	public:

	struct Callback 
	{
	    /** Callback operator.
	    * Implement operator()(int frame) to receive messages from the Counter of its current frame.
	    * @param frameCount tells the callback what animation frame the boundedCounter is at.
	    */
        virtual void operator()(int frame) = 0;
        
        virtual bool isInUse()const // override to allow removal of callback subclasses
        {
            return true;
        }    
        
        virtual ~ Callback()
        {
            // do nothing //
        }
	};
	
	
	enum SeekPolicy
	{
		seek_error,
		seek_bound,
		seek_roll
	};
	
	protected:

		int frameIndex;
		int min, max; // inclusive	
		bool rolledBack;
		Callback * callback; // takes ownership	

    public:

	explicit BoundedCounter (int min = 0, int max = 0); //_DEBUG std::invalid_argument

	virtual ~BoundedCounter ();// throw ();

	//virtual
	void notifyFrameIncrease(const int frameIncrease);//todo - does this need to be virtual?
	
	virtual int getFrame() const { return frameIndex; }
	int getBoundDistance() const { return (1+getMax()-getMin()); }
    int getIndex() const { return frameIndex-min; } // Index refers to a relative frame value.

	int getMin () const { return min; }
	int getMax () const { return max; }
	
	void setCallback(Callback *); // takes ownership
	bool hasCallback() const { return callback; }
	const Callback * getCallback() const { return callback; } // may be NULL	
	Callback * getCallback() { return callback; } // may be NULL	
    Callback * removeCallback(); //asserts callback (NDEBUG) or may be NULL
    
	virtual void setIndexRange (int min, int max);//_DEBUG std::invalid_argument
	void setToStart (); // Note that this will not update any timing information and so any remainder of the frame incurred by a timer will not be accounted for.
	void setToEnd (); // Note that this will not update any timing information and so any remainder of the frame incurred by a timer will not be accounted for.
	void seekToIndex (int frame, SeekPolicy s = seek_error);//std::invalid_argument
	void seekIntoIndex (int frame, SeekPolicy s = seek_error) ;//std::invalid_argument // Note that this will not update any timing information and so any remainder of the frame incurred by a timer will not be accounted for.
	
	void enableLoop() {rollOverType = seek_roll; }
	void disableLoop() {rollOverType = seek_bound; }
	bool isLoopEnabled()const { return seek_roll == rollOverType; }

    /**
    *   Use these to check wether the animation has passed its final frame and been forced to roll back, either to the start (if looping) or back to the last frame (if looping is disabled)
    *   This is useful if you are looking to implement subsequent animations only when the current animation has finished.
    *   It is the responsibility of any Ticker subclass to update rolledBack in their update() method.
    *   Some methods such as setToStart will reset rolledBack
    */
    bool hasRolledBack()const { return rolledBack; }
    void forceRolledBack(const bool rolledBackIn = true){ rolledBack = rolledBackIn; }
    
    

	protected:

		void assertSeekPolicy (int&frame, SeekPolicy);// std::invalid_argument
		SeekPolicy rollOverType;
};





}		//	time
}		//	aab
#endif	//	AAB_TIME_BOUNDED_COUNTER_CLASS




