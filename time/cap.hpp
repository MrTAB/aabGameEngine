
/**
*
*	cap.hpp
*
*	Cap class	-	Caps the minimum time passed since the last call to wait ().
*
*	The time to cap to is in milliseconds. Alternatively, it can
*	be given as a number of frames per second (fps).
*
*	Another attribute in use is the SleepInterval. CPU execution
*	is delayed on the process while waiting. This is done in units of
*	'SleepInterval' size of time until the specified minimum Lapse
*	has been met. A value of larger than 10 ms will likely interfere
*	with the accuracy of the timing involved. A value of 0 will mean
*	that no sleeping will be performed, however sleeping does give
*	the cpu a break from your program.
*
**/

#if !defined(AAB_TIME_CAP_CLASS)
#define AAB_TIME_CAP_CLASS
#include"../types/smart_ptr.hpp"
namespace aab	{
namespace time	{

class Cap
{
	private:

		float sleepWait;
		float min;
		float last;

	public:

	typedef aab::types::Smart <Cap>::Ptr Ptr;

	explicit Cap (float fps);

	virtual ~Cap ();// throw ();

	void wait ();

	void setMinimumSleepInterval (float milliseconds);
	void disableMinimumSleepInterval()
	{
	    sleepWait = 0.f;
	}

	void setMinimumLapse (float milliseconds);

	void setMaximumFPS (float fps);

};





}		//	time
}		//	aab
#endif	//	AAB_TIME_CAP_CLASS




