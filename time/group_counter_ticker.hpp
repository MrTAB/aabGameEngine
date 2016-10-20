
/**
*
*	callback_ticker.hpp
*
*	update should be called in harmony with that of the TimeReporters.
*	Not calling update effectively pauses the ticker.
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
*   Note that because a CallbackTicker does not have a notion of frames, it
*   cannot extend Ticker. This is because Ticker is fundamentally an animation
*   ticker. CallbackTicker is a more abstract ticker, and yet Ticker has no
*   actual counting mechanism.
*
**/

#if !defined(AAB_TIME_GROUP_COUNTER_TICKER_CLASS)
#define AAB_TIME_GROUP_COUNTER_TICKER_CLASS
#include"callback_ticker.hpp"
namespace aab	{
namespace time	{



//two different versions: one for use with non map containers, the other for use with map style containers (i.e. value type is a second of a pair in iteration.
    
// should be called a GroupCounterTicker as it does not count through the group
template<class T_Container>
class GroupCounterTicker : public CallbackTicker 
{
    struct GroupCallback : public Callback
    {
        GroupCounterTicker & group;
        
        explicit GroupCallback(GroupCounterTicker&groupIn):
            group(groupIn)
        {
            // do nothing //
        }
        
        virtual void operator()(int frameCount)
        {
            for (auto itr = group.counters.begin(); itr != group.counters.end(); ++itr)
            {
                itr->notifyFrameIncrease(frameCount);
            }
        }
        

    };
    
    protected:
    
    T_Container counters; // protected access to counters. Use as particular container allows. As such there is no direct ownership of any pointers or any cleanup by the GroupCounterTicker, good practice is to extend this class by specifying the template parameters and then handle the resources as required.
    
    public:
    
    GroupCounterTicker (TimeReporter::Ptr reporterIn, const double frameLengthIn):
        CallbackTicker (reporterIn, new GroupCallback (*this), frameLengthIn)
    {
        // do nothing //
    }
    
    virtual ~GroupCounterTicker()
    {
        // do nothing //
        // note: in subclass deconstructor, look at cleaning up T_Containers
    }
   

};

template<class T_Container>
class MapGroupCounterTicker : public CallbackTicker 
{
    struct GroupCallback : public Callback
    {
        MapGroupCounterTicker & group;
        
        explicit GroupCallback(MapGroupCounterTicker&groupIn):
            group(groupIn)
        {
            // do nothing //
        }
        
        virtual void operator()(int frameCount)
        {
            for (auto itr = group.counters.begin(); itr != group.counters.end(); ++itr)
            {
                itr->second->notifyFrameIncrease(frameCount);
            }
        }
        

    };
    
    protected:
    
    T_Container counters; // protected access to counters. Use as particular container allows. As such there is no direct ownership of any pointers or any cleanup by the GroupCounterTicker, good practice is to extend this class by specifying the template parameters and then handle the resources as required.
    
    public:
    
    MapGroupCounterTicker (TimeReporter::Ptr reporterIn, const double frameLengthIn):
        CallbackTicker (reporterIn, new GroupCallback (*this), frameLengthIn)
    {
        // do nothing //
    }
    
    virtual ~MapGroupCounterTicker()
    {
        // do nothing //
        // note: in subclass deconstructor, look at cleaning up T_Containers
    }
   

};


/*


Example of use:

BoundedCounter should be used as a pointer to as it is non-copyable. MappedCounter can be used in a structure defined this way as ti extends BoundedCounter.

typedef GroupCounterTicker<std::vector<BoundedCounter*> > VectorCounterTicker;

typedef GroupCounterTicker<std::set<BoundedCounter*> > SetCounterTicker;

*/


}		//	time
}		//	aab
#endif	//	AAB_TIME_GROUP_COUNTER_TICKER_CLASS




