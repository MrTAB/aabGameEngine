
/**
*
*	millisecond_reporter.hpp
*
*
**/

#if !defined(AAB_TIME_MILLISECOND_REPORTER_CLASS)
#define AAB_TIME_MILLISECOND_REPORTER_CLASS
#include"time_reporter.hpp"
#include"../types/smart_ptr.hpp"
namespace aab	{
namespace time	{


class MillisecondReporter : public TimeReporter
{
	private:

		unsigned int last;
		double change;

	public:

	typedef aab::types::Smart<MillisecondReporter>::Ptr Ptr;

	explicit MillisecondReporter ();
	virtual ~MillisecondReporter ()// throw()
	{
	    //do nothing //
	}

	double getChange () const;

	void update ();
	void updateTo (unsigned int);

};





}		//	time
}		//	aab
#endif	//	AAB_TIME_MILLISECOND_REPORTER_CLASS




