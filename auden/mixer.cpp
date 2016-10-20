
/**
*
*	mixer.cpp
*
**/

#include"mixer.hpp"
#include"../maths/power_of_2.hpp"
#include<sdl.H>
#include<sdl_Mixer.H>
#include<sstream>
#include"../test/exceptions.hpp"
#include"../test/debug_assertions.hpp"
namespace aab	{
namespace auden	{
using aab::maths::isPowerOf2;

Mixer::Mixer (AudioConnector::Ptr, const MixerFactory &factory)// std::invalid_argument, std::runtime_error
{
	frequency = factory.getFrequency ();
	Uint16 u16format = factory.getFormat ();
	musicChannelCount = factory.getMusicChannelCount ();
	sampleSize = factory.getSampleSize ();
	int soundChannels = factory.getSoundChannelCount ();
    _RELEASE_ONLY(MixerFactory default_factory);
    
	if (frequency < 1)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("Mixer::Mixer::\tinvalid frequency for audio Mixer"));
		_RELEASE_RESPONSE(frequency = default_factory.getFrequency());
	}
	if (musicChannelCount < 1 || musicChannelCount > 8)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("Mixer::Mixer::\tinvalid musicChannelCount for audio Mixer"));
		_RELEASE_RESPONSE(musicChannelCount = default_factory.getMusicChannelCount());
	}
	if (! isPowerOf2 (sampleSize))
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("Mixer::Mixer::\tinvalid sampleSize for audio Mixer (must be a power of 2)"));
		_RELEASE_RESPONSE(sampleSize = default_factory.getSampleSize());
	} 
	if (soundChannels < 0)
	{
		_DEBUG_RESPONSE(throw std::invalid_argument ("Mixer::Mixer::\ttoo few soundChannels for audio Mixer (minimum 0)"));
		_RELEASE_RESPONSE(soundChannels = default_factory.getSoundChannelCount());
	}
	
	//switch not allowed for these static const 
    if(u16format == MixerFactory::unsigned_char);
    else if(u16format == MixerFactory::signed_char);
    else if(u16format == MixerFactory::lsb_unsigned_short);
    else if(u16format == MixerFactory::lsb_signed_short);
    else if(u16format == MixerFactory::msb_unsigned_short);
    else if(u16format == MixerFactory::msb_signed_short);
    else if(u16format == MixerFactory::system_unsigned_short);
    else if(u16format == MixerFactory::system_signed_short);
    else if(u16format == MixerFactory::default_format);
    else
    {
        _DEBUG_RESPONSE(throw std::invalid_argument ("Mixer::Mixer::\tInvalid audio format for audio Mixer."));
        _RELEASE_RESPONSE(soundChannels = default_factory.getFormat());
    }


	if (Mix_OpenAudio (frequency, u16format, musicChannelCount, sampleSize) == -1)
	{
	    std::stringstream error;
	    error   << "Mixer::Mixer::\tMix_OpenAudio failed. Mix_GetError = "
                << Mix_GetError ();
		throw std::runtime_error (Mix_GetError ());
	}

	if (Mix_QuerySpec(&frequency, &u16format, &musicChannelCount) == 0)
	{
	    std::stringstream error;
	    error   << "Mixer::Mixer::\tMix_QuerySpec failed. Mix_GetError = "
                << Mix_GetError ();
		throw std::runtime_error (Mix_GetError ());
	}

	format = static_cast<MixerFactory::Format> (u16format);

	Mix_AllocateChannels (soundChannels);
}

Mixer::~Mixer ()// throw ()
{
	Mix_CloseAudio ();
}

int Mixer::getFrequency () const
{
	return frequency;
}

MixerFactory::Format Mixer::getFormat () const
{
	return format;
}

int  Mixer::getMusicChannelCount () const
{
	return musicChannelCount;
}

int  Mixer::getSampleSize () const
{
	return sampleSize;
}

int Mixer::getSoundChannelCount  () const
{
	return Mix_AllocateChannels (-1);
}

void Mixer::setSoundChannelCount (int count)
{
	Mix_AllocateChannels (count);
}

void Mixer::setAllSoundsVolume (int volume_0to128)
{
	Mix_Volume (-1, volume_0to128);
}

void Mixer::pauseAllSounds ()
{
	Mix_Pause (-1);
}

void Mixer::resumeAllSounds ()
{
	Mix_Resume (-1);
}

void Mixer::stopAllSounds ()
{
	Mix_HaltChannel (-1);
}

void Mixer::fadeAllSounds (int milliseconds)
{
	Mix_FadeOutChannel (-1, milliseconds);
}

void Mixer::setPanning(int left, int right)
{
	Mix_SetPanning(MIX_CHANNEL_POST, left, right);
}

}		//	auden
}		//	aab





