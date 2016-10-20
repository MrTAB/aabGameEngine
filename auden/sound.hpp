
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
*	version of it.
*
*	Basically, when you play, the sound gets stuck into a channel,
*	in which it plays. If you play it again during this time
*	(withought checking if it isPlaying() still), then a new channel
*	is given the sound samples and starts playing it. Pause() etc,
*	work on the one in this new channel, but the one in the old
*	channel keeps playing regardless.. Its been sent to play and
*	then disconnected by playing into a new channel.
*		Other ways this could have been resolved? Well, we could
*	have made it that play checks if the thing is already playing,
*	and then keep a record of all the channels that are being used
*	with this. The problem with that is all all the extra
*	computation involved in doing basic operations like play and
*	pause=> not deemed worth it when such features are not going
*   to be needed for the common operations, which are to simply play
*   something once, or forever. The other option would be to manually
*   handle and reserve channels, so that a client could request a channel
*   to operate on, and release that channel when it's sound is no longer
*   playing.
*
*	final note: Sound is a non copyable class. Pass by reference
*	or pointer because you can't copy construct (private)
*
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

	//typedef aab::types::Smart <Sound>::Ptr Ptr;

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




