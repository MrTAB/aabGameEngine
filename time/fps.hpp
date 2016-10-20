
/**
*
*	fps.hpp
*
*	Fps class	-
*		through looped invokations of update (), counts the number of
*		frames that have passed in the recent second.
*
**/

#if !defined(AAB_TIME_FPS_CLASS)
#define AAB_TIME_FPS_CLASS
#include"../types/smart_ptr.hpp"
namespace aab	{
namespace time	{


class Fps
{
	private:

		unsigned int last;
		int fps;
		int count;
		
		unsigned int updates;
		float totalFps;
		float updateFactor;

	public:

	typedef aab::types::Smart <Fps>::Ptr Ptr;

	explicit Fps ();

	virtual ~Fps ();// throw ();

	int update ();

	int getFps ()const;
	
	float getAverageFps()const;
};







}		//	time
}		//	aab
#endif	//	AAB_TIME_FPS_CLASS




