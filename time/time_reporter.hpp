
/**
*
*	time_reporter.hpp
*
*	TimeReporter	-	abstract class for classes which report some change in time.
*
*	use	-	extend, specifying getChange() method.
*
**/

#if !defined(AAB_TIME_TIMEREPORTER_CLASS)
#define AAB_TIME_TIMEREPORTER_CLASS
#include"../types/smart_ptr.hpp"
namespace aab	{
namespace time	{


class TimeReporter
{
	public:

	typedef aab::types::Smart <TimeReporter>::Ptr Ptr;

	virtual ~TimeReporter ();// throw ()


	virtual double getChange () const = 0;

	virtual void update () = 0;
	virtual void updateTo (unsigned int) = 0;

};


class StuckTimeReporter : public TimeReporter
{
    unsigned int time;
    
  public:
    
    typedef aab::types::Smart <StuckTimeReporter>::Ptr Ptr;
    
    StuckTimeReporter();

    double getChange () const;
	void update ();
	void updateTo (unsigned int time_in);
};







inline TimeReporter::
~TimeReporter()//throw()
{
    // do nothing //
}

inline StuckTimeReporter::
StuckTimeReporter(): time(0)
{
    // do nothing //
}

inline double StuckTimeReporter::
getChange () const
{
    return time;
}

inline void StuckTimeReporter::
update ()
{
    // do nothing //
}

inline void StuckTimeReporter::
updateTo (unsigned int time_in)
{
    time = time_in - time;
}



}		//	time
}		//	aab
#endif	//	AAB_TIME_TIMEREPORTER_CLASS




