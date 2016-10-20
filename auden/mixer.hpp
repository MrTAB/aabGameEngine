
/**
*
*	mixer.hpp
*
*	Mixer class- Sets up mixing channels required by Sound and Music
*		for sending data to Audio Device.
*
*	The constructor will throw a std::exception if something goes wrong.
*	This may later be amended to a sexier subclass of std::exception.
*
*	An instance of Mixer is needed to construct an instance of [Sound]
*	or [Music]. This ensures that the Sounds and Music can play. Also,
*	an instance of [AudioConnector] is required to create an instance
*	of Mixer. This, of course, ensures that there is a connection
*	to the audio device.
*
*	The Mixer is automatically created with certain formats for music,
*	however the values used for these formats may be critical for all
*	sound output in your application. It is even wise to let your [user]
*	have a say in some of the things involved, eg if sound output
*	comes out horrible on their computer, a different [sampleSize]
*	might be all thats needed. [SampleSize] you say? All you see below
*	is how to getSampleSize(), and Format, and Frequency etc...
*		Well, these things are set on creation. Rather than have a
*	big set of parameters, you pass in an instance of [MixerFactory],
*	or an instance of a subclass of MixerFactory, and inside it set
*	the values you want. The final result may not be what you request
*	however, and so getFrequency(), getFormat() exist so that you can
*	look and see if you got the ones you wanted.
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
*	[Mixer] also provides you to pause and resume all playing [Sounds]
*	in one go, or to stop all songs, or even fade all playing
*	(including paused) songs out so that they finish softly after
*	a certain number of milliseconds (usefull when changing scene
*	or cut-scene and you dont want to abruptly end the noise of
*	some whining enemy... That would sound bad, and, i wonder how
*	many games do that and yet how little people consciously notice
*	it? Well.. You are more likely to notice (and dislike) if its
*	not there, yeh?)
*
*	Final note: Mixer is a non copyable class. Pass by reference
*	or pointer because you can't copy construct (private)
**/

#if !defined(AAB_AUDEN_MIXER_CLASS)
#define AAB_AUDEN_MIXER_CLASS
#include"mixer_factory.hpp"
#include"audio_connector.hpp"
//#include"../types/smart_ptr.hpp"
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

	//typedef aab::types::Smart <Mixer>::Ptr Ptr;

	explicit Mixer (AudioConnector::Ptr, const MixerFactory & factory = MixerFactory());
		// std::invalid_argument, std::runtime_error

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




