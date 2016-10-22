
/**
*
*	music.hpp
*
*	Music class- Represents a loaded/streamed song that can be played.
*
*	To create an instance of Music, you need a Mixer, and the filename.
*
*		:Loading Music:
*
*	Create an instance of Music, giving the filename you want to load.
*	This can be a file of type WAVE, MOD, MIDI, OGG, MP3 (however note
*	that resetMusic() only works on WAVE, MOD, MIDI, OGG, MP3). Also note
*	that the constructor will throw a [std::exception] if it fails.
*	The play methods (play, playFadingIn) will also throw exceptions
*	if they fail.
*   NOTE: to load mp3's you need libgcc_s_dw2-1.dll & libstdc++-6.dll.
*
*	The music files
*
*		:Playing Music:
*
*	you can play an instance of music with:
*		play(Music::once) or play (Music::forever), to, oddly enough,
*	play it once or forever. This defaults to forever, so you can
*	really just go play().
*		Alternatively, you may want to play the music but fade it
*	in from silence up until its full volume. Use playFadingIn and
*	specify the milliseconds it should take until it reaches its
*	full volume.
*	Things worth noting;
*
*		*	Only one Music can be played at a time, so calling play()
*		on one Music instance will stop another Music (unless its still
*		fading out from a call to stopMusicByFadingOut()) if its
*		currently playing.
*
*		*	Calling playFadingIn while this Music is still playing wont
*		cause it to fade in, however if you call play with another it
*		will fade itself in.
*
*	The methods with 'Music' in them apply to the output of music, i.e.
*	the currently playing music. Thus, you can, setMusicVolume, pauseMusic etc.
*
*	Music is a non copyable class. Pass by reference
*	or pointer because you can't copy construct (private)
**/

#if !defined(AAB_AUDEN_MUSIC_CLASS)
#define AAB_AUDEN_MUSIC_CLASS
#include"audio_connector.hpp"
#include"mixer.hpp"
//#include"../types/smart_ptr.hpp"
#include<string>
#include<memory>
#include<exception>
namespace aab	{
namespace auden	{

/*
*	still to: make looping music sexy and smooth.
*/

enum
{
	zero_volume = 0,
	half_volume = 64,
	max_volume = 128
};

class Music
{
	private:

		struct Data;
		const std::auto_ptr<Data> data;

		Music (Music &);

	public:

	//typedef aab::types::Smart <Music>::Ptr Ptr;

	enum PlayCount
	{
		forever = -1,
		once = 0
	};

	explicit Music (Mixer &, std::string filename);//aab::test::file_not_found_error, std::runtime_error
	virtual ~Music ();// throw ();

	bool play (PlayCount = forever);// std::logic_error in _DEBUG - returns false in release mode if error
	bool playFadingIn (int milliseconds, PlayCount = forever);// std::logic_error in _DEBUG - returns false in release mode if error

	void setMusicVolume (int volume_0to128);

	int getMusicVolume ();

	bool isMusicPaused () const;
	bool isMusicPlaying () const;
	void pauseMusic ();
	void resumeMusic ();
	void stopMusic ();
	void stopMusicByFadingOut (int milliseconds);
	void resetMusic ();	

};








}		//	auden
}		//	aab
#endif	//	AAB_AUDEN_MUSIC_CLASS




