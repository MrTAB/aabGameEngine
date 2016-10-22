
/**
*
*	mapped_counter.hpp
*
*   Operates in a similar manner to a bounded_counter, except rather than
*    working between bounds [a,b], a mapped counter has a set of values which are
*    considered bounded only by their order in the counters mapping. So rather
*    than animating [1,3] as 1,2,3,1,2,3... you can suggest frames 1,4,2 and the
*    mapped counter will loop through 1,4,2,1,4,2,1,4,2... etc. Use addFrame to
*    add one frame, or addFrames to add frames from a container.
*    
*    The MappedCounter keeps an ordered list of frames, and frame updates cycle
*    through that list of frames. Once at the end the cycle may loop through or
*    it may stick, depending on the chosen SeekPolicy.
*
*   An index range can be set so that a subspace of that set can be looped or
*   bound-animated through based on their indices within the frame mapping. This
*   bound is hard started and soft ended, i.e. b is is excluded, or to 
*   mathematicians, [a,b)
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
    
    //todo: add addFrameRange method for adding a bounded group of frames
    
    void addFrame (const int);
    int getFrameCount () const { return frameMapping.size(); }
    // call after direct edits to the vector to set min to 0 and max to the end of the size of the vector
    void resetIndexRange() { min = 0; max = frameMapping.size() - 1; if (frameIndex >= max) {frameIndex = max;} };
    FrameMapping & accessFrameMap() { return frameMapping; } 
    void clearFrames() { frameMapping.clear(); resetIndexRange(); }    

};


}		//	time
}		//	aab
#endif	//	AAB_TIME_MAPPED_COUNTER_CLASS




