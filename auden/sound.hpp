
/**
*
*	sound.hpp
*
*	Sound class	-	represents a loaded sound that can be played.
*
*	The constructor requires a Mixer, and the filename. It may throw a
*	std::exception if it cannot find or load the file.
*	Can load WAVE, AIFF, RIFF, OGG, and VOC files.
*
*	Play with play() or playFor(): play(Sound::once) to play it once,
*	or play(Sound::forever) to play it forever, though this isn't
*	usually required with sounds. playFor() allows you to play it for
*	a certain number of milliseconds, after which it stops playing.
*
*	You can set the volume associated with the Sound; a value between
*		0 and 128.
*
*	You can also pause, resime, stop etc, however these will do
*	nothing if this Sound is not playing, and note that if you play
*	a sound while it is still playing, it becomes assigned to a new
*	channel, and so pause() etc only work on the most recent playing
*	version of it; the one that is tied to the channel it is playing on
*
*	Basically, when you play, the sound gets stuck into a channel,
*	in which it plays. If you play it again during this time
*	(withought checking if it isPlaying() still), then a new channel
*	is given the sound samples and starts playing it, allowing you to play
*   the song over itself if you wish. Methods such as Pause() etc,
*	work on the one in this new channel, and the old channel is no longer
*   associated with this Sound object. An alternative implementation may
*   have chosen to open channels up for you, but this implementation is
*   designed as a simple sound.play() system to let the library worry
*   about channels for the majority of cases. For specific cases where
*   channel control is desired, Sound has a group of static methods for
*   channel query. Developer note: Another alternative implementation could have
*   Sound maintain and manage all the channels, or have a Sound object and a 
*   PlayingSound object, where playing a Sound generates a PlayingSound bound to
*   a channel. However, such approaches were deemed over the top for the 
*   simple user requirements of this library; the most common use cases have been
*   prioritised.
*   
*   Sound is a non copyable class. Pass by reference
*	or pointer because you can't copy construct (private)
**/

#if !defined(AAB_AUDEN_SOUND_CLASS)
#define AAB_AUDEN_SOUND_CLASS
#include"mixer.hpp"
#include"audio_connector.hpp"
//#include"../types/smart_ptr.hpp"
#include<string>
#include<memory>
#include<exception>
namespace aab	{
namespace auden	{

/*
	later update might be to allow constructing a Sound from sound
	data held in memory, or even copying of sounds, with a reference
	to the same sound data held between each.
*/

class Sound
{
	private:

		struct Data;
		const std::auto_ptr<Data> data;

		Sound (Sound &);

		bool isChannelValid () const;

	public:

	enum PlayCount
	{
		forever = -1,
		once = 0
	};

	explicit Sound (Mixer &, std::string filename); // aab::test::file_not_found_error, std::runtime_error

	virtual ~Sound ();// throw ();

	int play (PlayCount = once);

	int playFor (int milliseconds, PlayCount = forever);

	void setVolume (int volume_0to128);	
	int getVolume ();

	bool isPaused () const;
	bool isPlaying () const;
	void setPlayingPanning(int left0to255, int right0to255); // sets panning for the sound IF it is playing. This is removed when it has stopped playing on that channel.

	void pause ();
	void resume ();
	void stop ();
	
	static bool isChannelAllocated(const int channel);
	static bool isChannelPaused(const int channel);
	static bool isChannelPlaying(const int channel);
	static void pauseChannel(const int channel);
	static void resumeChannel(const int channel);
	static void stopChannel(const int channel);
	static void pauseAllSounds();
	static void resumeAllSounds();
	static void stopAllSounds();
	static void setMasterVolume(const int volume_0to128);

};






}		//	auden
}		//	aab
#endif	//	AAB_AUDEN_SOUND_CLASS




