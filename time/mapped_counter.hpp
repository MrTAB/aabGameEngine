
/**
*
*	mapped_counter.hpp
*
*   Operates in a similar manner to a bounded_counter, except rather than
*    working between bounds [a,b], a mapped counter has a set of values which are
*    considered bounded only by their order in the counters mapping.
*    
*    The MappedCounter keeps an ordered list of frames, and frame updates cycle
*    through that list of frames. Once at the end the cycle may loop through or
*    it may stick, depending on the SeekPolicy.
*
*   An index range can be set so that a subspace of that set can be looped or
*   bound-animated through.
*
**/

#if !defined(AAB_TIME_MAPPED_COUNTER_CLASS)
#define AAB_TIME_MAPPED_COUNTER_CLASS
#include"bounded_counter.hpp"
#include<vector>
namespace aab	{
namespace time	{




class MappedCounter : public BoundedCounter
{
    public:
        typedef std::vector<int> FrameMapping;    
        
	protected:

        FrameMapping frameMapping;

	public:

	explicit MappedCounter (int min = 0, int max = 0);

	virtual ~MappedCounter ();// throw ();

	virtual int getFrame () const;

	virtual void setIndexRange (int min, int max);//_DEBUG std::invalid_argument

    template<class InputIterator>
    void addFrames(InputIterator first, InputIterator last)
    {
        if (min == 0 && (0==max || max == frameMapping.size()-1))
        {
            max += (last-first)-1;
        } 
        frameMapping.insert(frameMapping.end(), first,last);
       
    }
    
    void addFrame (const int);
    int getFrameCount () const { return frameMapping.size(); }
    // call after direct edits to the vector to set min to 0 and max to the end of the size of the vector
    void resetIndexRange() { min = 0; max = frameMapping.size() - 1; if (frameIndex >= max) {frameIndex = max;} };
    FrameMapping & accessFrameMap() { return frameMapping; } 
    void clearFrames() { frameMapping.clear(); resetIndexRange(); }    

};



/*
class MappedCounter
{
    public:
        typedef std::vector<int> FrameMapping;
        
        enum SeekPolicy
        {
            seek_error,
            seek_bound,
            seek_roll
        };
        
	protected:

        FrameMapping frameMapping;
		int frameIndex; // the index will be used to find the actual value from the FrameMapping
		int min, max; // inclusive	
		bool rolledBack;

	public:

	MappedCounter ();

	virtual ~MappedCounter ();// throw ();

	void notifyFrameIncrease(const int frameIncrease);

	int getFrame () const;
	
	int getBoundDistance() const { return (1+getMax()-getMin()); }
	
    void addFrame (const int);
    

    int getFrameCount () const { return frameMapping.size(); }
    
    // call after direct edits to the vector to set min to 0 and max to the end of the size of the vector
    void resetIndexRange() { min = 0; max = frameMapping.size() - 1; if (frameIndex >= max) {frameIndex = max;} };
    FrameMapping & accessFrameMap() { return frameMapping; }
    
    void clearTicks() { frameMapping.clear(); resetIndexRange(); }
    
    int getIndex() const { return frameIndex-min; }

	int getMin () const;
	int getMax () const;

	void setIndexRange (int min, int max);//_DEBUG std::invalid_argument
	void setToStart ();
	void setToEnd ();
	void seekToIndex (int frame, SeekPolicy s = seek_error);//std::invalid_argument
	void seekIntoIndex (int frame, SeekPolicy s = seek_error) ;//std::invalid_argument
	
	void enableLoop() {rollOverType = seek_roll; }
	void disableLoop() {rollOverType = seek_bound; }
	bool isLoopEnabled()const { return seek_roll == rollOverType; }
	

    //
    //   Use these to check wether the animation has passed its final frame and been forced to roll back, either to the start (if looping) or back to the last frame (if looping is disabled)
    //   This is useful if you are looking to implement subsequent animations only when the current animation has finished.
    //   It is the responsibility of any Ticker subclass to update rolledBack in their update() method.
    //   Some methods such as setToStart will reset rolledBack

    bool hasRolledBack()const { return rolledBack; }
    void forceRolledBack(const bool rolledBackIn = true){ rolledBack = rolledBackIn; }

	protected:

		void assertSeekPolicy (int frame, SeekPolicy);// std::invalid_argument
		SeekPolicy rollOverType;

};
*/


}		//	time
}		//	aab
#endif	//	AAB_TIME_MAPPED_COUNTER_CLASS




