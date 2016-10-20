
/**
*
*	music.cpp
*
**/

#include"music.hpp"
#include<sdl.H>
#include<sdl_Mixer.H>
#include<boost/filesystem.hpp>
#include<sstream>
#include"../test/exceptions.hpp"
#include"../test/debug_assertions.hpp"
namespace aab	{
namespace auden	{

struct Music::Data
{
	Mix_Music * music;
};

Music::Music (Mixer &, std::string filename):
	//aab::test::file_not_found_error, std::runtime_error
	data (new Data())
{
    if (!boost::filesystem::exists(filename))
    {
        std::string error;
        error += "Music::Music::\tfile " + filename + " does not exist.\n";
        throw aab::test::file_not_found_error(error);
    }
    
	data-> music = Mix_LoadMUS (filename.c_str ());  //WAVE, MOD, MIDI, OGG, MP3

	if (! data-> music)
	{
	    std::stringstream error;
	    error   << "Music::Music::\tfile "
                << filename
                << " failed to load. Mix_GetError="
                << Mix_GetError ();
		throw std::runtime_error (error.str());
	}
}

Music::~Music ()// throw ()
{
	Mix_FreeMusic (data-> music);
}

bool Music::play (PlayCount pc)// std::logic_error in _DEBUG
{
	if (Mix_PlayMusic (data-> music, (int) pc) == -1)
	{
	    _DEBUG_RESPONSE(throw std::logic_error (Mix_GetError ()));
	    _RELEASE_RESPONSE(return false);
	}
	return true;
}

bool Music::playFadingIn (int milliseconds, PlayCount pc) // std::logic_error in _DEBUG
{
	if (Mix_FadeInMusic (data-> music, (int) pc, milliseconds) == -1)
	{
		_DEBUG_RESPONSE(throw std::logic_error (Mix_GetError ()));
		_RELEASE_RESPONSE(return false);
	}
	return true;
}

void Music::setMusicVolume (int volume)
{
	Mix_VolumeMusic (volume);
}

int Music::getMusicVolume ()
{
	return Mix_VolumeMusic (-1);
}

void Music::pauseMusic ()
{
	Mix_PauseMusic ();
}

void Music::resumeMusic ()
{
	Mix_ResumeMusic ();
}

bool Music::isMusicPaused () const
{
	return Mix_PausedMusic () && Mix_PlayingMusic ();
}

bool Music::isMusicPlaying () const
{
	return (! Mix_PausedMusic ()) && Mix_PlayingMusic ();
}


void Music::stopMusic ()
{
	Mix_HaltMusic ();
}

void Music::stopMusicByFadingOut (int milliseconds)
{
	Mix_FadeOutMusic (milliseconds);
}

void Music::resetMusic ()
{
	Mix_RewindMusic ();
}

}		//	auden
}		//	aab





