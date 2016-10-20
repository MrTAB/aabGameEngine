
/**
*
*	audio_connector.hpp
*
*	AudioConnector class.
*		Like InputConnector, only for Audio instead of Input.
*
*	This is more a comment for someone choosing to implement
*	their own version of this entire library: The constructor
*	must set up audio devices with respect to the implementation.
*	In other words, do the things that must be done before a
*	Mixer can be created. The deconstructor must undo these
*	things, assuming that the Mixer has undone its own setup
*	from within its deconstructor first.
*
**/

#if !defined(AAB_AUDEN_AUDIO_CONNECTOR_CLASS)
#define AAB_AUDEN_AUDIO_CONNECTOR_CLASS
#include"../types/smart_ptr.hpp"
namespace aab	{
namespace auden	{


class AudioConnector
{
	private:

		AudioConnector (AudioConnector&); //no copy

	protected:

		explicit AudioConnector () {};
		virtual ~AudioConnector()//throw () {};
		{
		}

	public:

	typedef aab::types::Smart <AudioConnector>::Ptr Ptr;

};




}		//	auden
}		//	aab
#endif	//	AAB_AUDEN_AUDIO_CONNECTOR_CLASS
