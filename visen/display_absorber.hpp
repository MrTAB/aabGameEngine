
/**
*
*	display_absorber.hpp
*
*   On construction, a displayAbsorber will "absorb" everything that is rendered
*   and can be put into a display list, and compact it into that display list.
    This will occur until stop() is called. That DisplayList can then be used to
    render a graphics-processor optimised version of what was rendered during
    the display absorbing time.
*
**/

#if !defined(AAB_VISEN_DISPLAY_ABSORBER_CLASS)
#define AAB_VISEN_DISPLAY_ABSORBER_CLASS
#include"display_list.hpp"
namespace aab	{
namespace visen	{



class DisplayAbsorber
{
	private:

		DisplayList list;
		bool stopped;

		DisplayAbsorber (const DisplayAbsorber &); // no copy

	public:

	explicit DisplayAbsorber (DisplayList, bool renderWhileAbsorbing = false);// std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
	virtual ~DisplayAbsorber ();// throw ();

	void stop ();
};



}		//	visen
}		//	aab
#endif	//	AAB_VISEN_DISPLAY_ABSORBER_CLASS




