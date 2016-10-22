
/**
*
*	mixer_factory.cpp
*
**/

#include"mixer_factory.hpp"
#include<sdl.H>
#include<sdl_Mixer.H>
namespace aab	{
namespace auden	{


const int MixerFactory::unsigned_char = AUDIO_U8; //Unsigned 8-bit samples
const int MixerFactory::signed_char = AUDIO_S8; //Signed 8-bit samples
const int MixerFactory::lsb_unsigned_short = AUDIO_U16LSB; //Unsigned 16-bit samples, in little-endian byte order
const int MixerFactory::lsb_signed_short = AUDIO_S16LSB; //Signed 16-bit samples, in little-endian byte order
const int MixerFactory::msb_unsigned_short = AUDIO_U16MSB; //Unsigned 16-bit samples, in big-endian byte order
const int MixerFactory::msb_signed_short = AUDIO_S16MSB; //Signed 16-bit samples, in big-endian byte order
const int MixerFactory::system_unsigned_short = AUDIO_U16SYS; //Unsigned 16-bit samples, in system byte order
const int MixerFactory::system_signed_short = AUDIO_S16SYS; //Signed 16-bit samples, in system byte order
const int MixerFactory::default_format = MIX_DEFAULT_FORMAT;



MixerFactory::MixerFactory ()
{
	/* nothing */
}

MixerFactory::~MixerFactory()// throw ()
{
	/* nothing */
}

int MixerFactory::getFrequency () const
{
	return 22050;	//22050 - good for games // common; 11025, 22050, 44100, 96000
}

MixerFactory::Format MixerFactory::getFormat () const
{
	return default_format; // or MIX_DEFAULT_FORMAT which is AUDIO_S16SYS
}

int MixerFactory::getMusicChannelCount () const
{
	return 2; //1 to 8. 1 or 2 usually.
}

int MixerFactory::getSampleSize () const
{
	return 2048; // must be a power of 2. use 4096+ if just playing music.
}

int MixerFactory::getSoundChannelCount () const
{
	return 16;
}



}		//	auden
}		//	aab





