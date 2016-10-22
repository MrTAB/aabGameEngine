
/**
*
*	audio_connector.hpp
*
*   An AudioConnector represents an object which initialises audio subsystems.
*   An audio Mixer request a valid AudioConnector be supplied to them in their
*   constructor.
*
*   Extend AudioConnector to create an object which initialises the audio 
*   systems, or more preferably use an existing implementation such as
*   visen::ScreenClass
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
