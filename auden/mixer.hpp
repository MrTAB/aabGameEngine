
/**
*
*	mixer.hpp
*
*	Mixer class- Sets up mixing channels required by Sound and Music
*		for sending data to Audio Device.
*
*	The constructor will throw a std::exception if something goes wrong.
*	This may later be amended to a specific subclass of std::exception.
*
*	An instance of Mixer is needed to construct an instance of [Sound]
*	or [Music]. This ensures that the Sounds and Music can play. Also,
*	an instance of [AudioConnector] is required to create an instance
*	of Mixer. This, ensures that there is a connection to the audio device.
*
*	The Mixer is automatically created with certain formats for music,
*	however the values used for these formats may be critical for all
*	sound output in your application. 
*  
*   Use the MixerFactory to define the formats that the mixer is created with.
*   To do so, extend the MixerFactory and overload the get* methods to 
*   return your desired initialisation values. The Mixer may end up with values 
*   other than those requested - use Mixer::get* methods to compare these.
*
*		The attribute [SoundChannelCount], is the number of channels
*	that sounds are played on, hence is the number of sounds that
*	you can have playing at once. This is set in the [MixerFactory],
*	however unlike the other properties of the factory, you can
*	change it after creation. You do not really need to however,
*	because [Sound] automatically creates a new Channel if you request
*	to play a song and no channels are free. However, there is also
*	the case where you may want to reduce the channels available,
*	or even set them to [0], freeing all channels.
*
*	[Mixer] allows you to pause and resume all playing [Sounds]
*	in one go, or to stop all songs, or fade all playing
*	(including paused) songs out so that they finish softly after
*	a certain number of milliseconds (usefull when changing scene
*	or cut-scene and you dont want to abruptly end the currently playing
*   sounds.
*
*	Mixer is a non copyable class. Pass by reference
*	or pointer because you can't copy construct (private)
**/

#if !defined(AAB_AUDEN_MIXER_CLASS)
#define AAB_AUDEN_MIXER_CLASS
#include"mixer_factory.hpp"
#include"audio_connector.hpp"
#include<exception>
namespace aab	{
namespace auden	{

class Mixer
{
	private:

		int frequency;
		MixerFactory::Format format;
		int musicChannelCount;
		int sampleSize;

		Mixer (Mixer &);

	public:

	explicit Mixer (AudioConnector::Ptr, const MixerFactory & factory = MixerFactory());
		// may throw std::invalid_argument, std::runtime_error

	virtual ~Mixer ();// throw ();

	int getFrequency () const;
	MixerFactory::Format getFormat () const;
	int getMusicChannelCount () const;
	int getSampleSize () const;
	int getSoundChannelCount () const;
	void setSoundChannelCount (int);

	void setAllSoundsVolume (int volume_0to128);
	void pauseAllSounds ();
	void resumeAllSounds ();
	void stopAllSounds ();
	void fadeAllSounds (int milliseconds);
	void setPanning(int left0to255, int right0to255);
	
	static inline unsigned int getMaxVolume()
	{
	    return 128;
	}

};






}		//	auden
}		//	aab
#endif	//	AAB_AUDEN_MIXER_CLASS




