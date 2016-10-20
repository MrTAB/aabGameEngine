
/**
*
*	sound.cpp
*
**/

#include"sound.hpp"
#include<sdl.H>
#include<sdl_Mixer.H>
#include<boost/filesystem.hpp>
#include<sstream>
#include"../test/exceptions.hpp"
namespace aab	{
namespace auden	{

struct Sound::Data
{
	Mix_Chunk * chunk;
	int channel;
};

void channelFinishedCallback (int channel)
{
    Mix_SetPanning(channel, 255, 255);
}

//consider adding Mix_SetPosition support

Sound::Sound (Mixer &, std::string filename):
	//aab::test::file_not_found_error, std::runtime_error
	data (new Data)
{
    if (!boost::filesystem::exists(filename))
    {
        std::string error;
        error += "Sound::Sound::\tfile " + filename + " does not exist.";
        throw aab::test::file_not_found_error(error);
    }
    
	data-> chunk = Mix_LoadWAV (filename.c_str ());
	data-> channel = -1;

	if (! data-> chunk)
	{
	    std::stringstream error;
	    error   << "Sound::Sound::\tfile "
                << filename
                << " failed to load. Mix_GetError="
                << Mix_GetError ();
		throw std::runtime_error (error.str());
	}
}

Sound::~Sound ()// throw ()
{
	//stop sound first?

	// free sound chunk
	Mix_FreeChunk (data-> chunk);
}

int Sound::play (PlayCount pc)
{
	data->channel = Mix_PlayChannel (-1, data-> chunk, pc);

	if (data-> channel == -1)
	{
		//unable to play sound: not enough channels: allocate a new channel and call again:

		Mix_AllocateChannels (Mix_AllocateChannels (-1) + 1); // Yes, this *does* inc num channels by 1. >_>

		play (pc);
	}
	
	return data->channel;

}

int Sound::playFor (int milliseconds, PlayCount pc)
{
	data->channel = Mix_PlayChannelTimed (-1, data-> chunk, pc, milliseconds);

	if (data-> channel == -1)
	{
		//unable to play sound: not enough channels: allocate a new channel and call again:

		Mix_AllocateChannels (Mix_AllocateChannels (-1) + 1); // Yes, this *does* inc num channels by 1. >_>

		playFor (milliseconds, pc);
	}
	
	return data->channel;

}

void Sound::setVolume (int volume_0to128)
{
	Mix_VolumeChunk (data-> chunk, volume_0to128);
}

int Sound::getVolume ()
{
	return Mix_VolumeChunk (data-> chunk, -1);
}

void Sound::pause ()
{
	if (isChannelValid ())
	{
		Mix_Pause (data-> channel);
	}
}

void Sound::resume ()
{
	if (isChannelValid ())
	{
		Mix_Resume (data-> channel);
	}
}

bool Sound::isPaused () const
{
	if (isChannelValid ())
	{
		return Mix_Paused (data-> channel) && Mix_Playing (data-> channel);
	}

	return false;
}

bool Sound::isPlaying () const
{
	if (isChannelValid ())
	{
		return (! Mix_Paused (data-> channel)) && Mix_Playing (data-> channel);
	}

	return false;
}

void Sound::setPlayingPanning(int left0to255, int right0to255)
{
    if (isChannelValid ())
    {
        if (Mix_SetPanning(data->channel,left0to255, right0to255))
        {
            Mix_ChannelFinished(&channelFinishedCallback); // should really be done once for all sounds, perhaps in Mixer. A more elaborate system could use a channel callback to allow the client to receive a callback when their sound has finished playing.
        }
    }
}


void Sound::stop ()
{
	if (isChannelValid ())
	{
		Mix_HaltChannel (data-> channel);
	}
}

bool Sound::isChannelValid () const
{
	if (data-> channel == -1)
	{
		return false;
	}

	if (data-> chunk == Mix_GetChunk (data-> channel))
	{
		return true;
	}

	/*
	*	reset and return false; the sound must have stopped playing
	*	and had its channel reclaimed and given to another song.
	*/

	data-> channel = -1;
	return false;

}



bool Sound::isChannelAllocated(const int channel)
{
    return Mix_GetChunk(channel);
}
	
bool Sound::isChannelPaused(const int channel)
{
    return Mix_Paused (channel) && Mix_Playing (channel);
}
	
bool Sound::isChannelPlaying(const int channel)
{
    return (! Mix_Paused (channel)) && Mix_Playing (channel);
}
	
void Sound::pauseChannel(const int channel)
{
    Mix_Pause (channel);
}
	
void Sound::resumeChannel(const int channel)
{
    Mix_Resume (channel);
}
	
void Sound::stopChannel(const int channel)
{
    Mix_HaltChannel (channel);
}

void Sound::pauseAllSounds()
{
    Mix_Pause(-1);
}

void Sound::resumeAllSounds()
{
    Mix_Resume(-1);
}

void Sound::stopAllSounds()
{
    Mix_HaltChannel(-1);
}

void Sound::setMasterVolume(const int volume_0to128)
{
    Mix_Volume(-1, volume_0to128); // set all channels to have master volume, mixed into the existing volume
}

}		//	auden
}		//	aab





