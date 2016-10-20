
/**
*
*	delta_time.hpp
*
*	DeltaTime class	-
*			calculates how much time has passed through looped invokations of update().
*		DeltaTime then uses this information to provide a 'Change' or 'Delta', which
*		represents the amount of time that has passed as a fraction of how much time
*		you wanted to pass. Call getChange() to get this value.
*			Set the 'how much time you wanted to pass' as an expected number of frames
*		per second (expectedFps) through the constructors argument, or later through
*		setFps().
*			example: if the expectedFps is 60 frames per second, and update is called
*		30 times in that second, then the getChange() will return around 60/30 = 2.0.
*
*	bounding:
*
*		it is wise to bound the delta value between a minimum and maximum to avoid
*		ridiculous values caused by computer slowdown. Use setBound or setMin/setMax
*		for this. Now the value returned by getDelta is confined to between Min and Max.
*		Use removeBound to remove the bounds you have applied.
*
*	advanced use:
*		frames per interval : FPI. This is the number of frames that are processed
*		before the Delta Timer calculates the new delta timing unit. Rather than
*		calculating one each frame, it can be more efficient to calculate one every
*		FPI frames, (which is in essence the average of those times).
*
*
*	DeltaTime is also a subclass of TimeReporter
*
*
**/

#if !defined(AAB_TIME_DELTATIME_CLASS)
#define AAB_TIME_DELTATIME_CLASS
#include"time_reporter.hpp"
#include"../types/smart_ptr.hpp"
namespace aab	{
namespace time	{


class DeltaTime : public TimeReporter
{
	private:

		unsigned int fpi;
		unsigned int framesThisFpi;
		unsigned int last;

		double delta;
		double expectedChange;
		double min;
		double max;
		double multiplier;

	public:

	typedef aab::types::Smart <DeltaTime>::Ptr Ptr;

	explicit DeltaTime (double expectedFps);
	virtual ~DeltaTime ()// throw()
	{
	    // do nothing //
	}

	double getChange () const;
	unsigned int getFpi () const;
	double getExpectedFps () const;
	double getMin () const;
	double getMax () const;
	bool isBounded () const;

	void setFpi (unsigned int);
	void setExpectedFps (double fps);

	void update ();
	virtual void updateTo (unsigned int);

	void setBound (double min, double max);

	void setMin (double);
	void setMax (double);

	void removeBound ();

};





}		//	time
}		//	aab
#endif	//	AAB_TIME_DELTATIME_CLASS




