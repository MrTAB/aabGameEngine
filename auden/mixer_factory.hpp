
/**
*
*	mixer_factory.hpp
*
*	MixerFactory class-	contains factory methods for constructing an
*		instance of Mixer.
*
*	By default, Mixer uses an instance of this MixerFactory, and calls
*	its methods to figure out what values it should set up the audio
*	subsystem with.
*		To specify your own audio attributes, create a subclass of
*	MixerFactory, and redefine the virtual methods that you wish to.
*	For example, say you want a different Frequency:
*
*		class MyMixerFactory : public aab::auden::MixerFactory
*		{
*			public:int getFrequency () const
*			{
*				return 44100;
*			}
*		}
*
*	Description of each attribute:
*
*
*	Frequency: Common frequencies are:
*		11025, 22050, 44100, 96000...
*		44100 is an acceptably high quality frequency, however 22050 requires
*		less processing and is the default.
*
*	Format: 
*		Format specifies the size and type of the sample elements. 
*       Return one of the const static int's specified in the MixerFactory class
*		Default format is system_signed_short.
*
*	*	lsb_ as a prefix means least significant priority, i.e. little endian.
*	*	msb_ as a prefix means most significant priority, i.e. big endian.
*	*	system_ as a prefix means use lsb_ if the system is little endian,
*			and use msb_ if the system is big endian.
*
*	MusicChannelCount: This is the nuber of output channels:1 or 2
*		(mono and stereo) are good and likely to be supported. 8 is if your user
*       has an incredibly super sound system.
*
*	SampleSize: This one is [ V E R Y   I M P O R T A N T ] when it comes to
*		sound quality. It must be a power of 2, e.g. 512, 1024, 2048, 4096, 8192 etc.
*		Too large a value and there will be large gaps inbetween sounds on
*		channels, and looping musics. Too small a value and the sound system won't
*		be able to keep up, and there'll be a big underflow and you'll go "ow" as
*		your ears are torn to shreds. Default is 2048. 4096+ is fine if your just
*		playing music.
*
*	SoundChannelCount: This is the number of channels set up for processing
*		sounds, i.e the number of Sounds that can be played at once. However,
*		Sound automatically allocates more channels if you play a sound and
*		there isnt enough channels. This defaults to 16.
*
*
**/

#if !defined(AAB_AUDEN_MIXER_FACTORY_CLASS)
#define AAB_AUDEN_MIXER_FACTORY_CLASS
namespace aab	{
namespace auden	{


class MixerFactory
{
	public:


	explicit MixerFactory ();
	virtual ~MixerFactory ();

	typedef int Format;
	
    // The following are acceptable values for format
	const static int unsigned_char;
	const static int signed_char;
	const static int lsb_unsigned_short;
	const static int lsb_signed_short;
	const static int msb_unsigned_short;
	const static int msb_signed_short;
	const static int system_unsigned_short;
	const static int system_signed_short;
	const static int default_format;


	virtual int getFrequency () const;
	virtual Format getFormat () const;
	virtual int getMusicChannelCount () const;
	virtual int getSampleSize () const;
	virtual int getSoundChannelCount () const;

};






}		//	auden
}		//	aab
#endif	//	AAB_AUDEN_MIXER_FACTORY_CLASS




