
/**
*
*	auden.hpp
*
*	Include this to include all headers under the auden namespace.
*	link to the static library libauden.a to define the classes.
*
*	To use auden:
*
*	You need an AudioConnector, (i.e a valid sublass of AudioConnector)
*	to begin with. visen::ScreenClass is an example of this.
*   Use this to create an instance of Mixer, which sets
*	up the mixing channels. Then you can create Music objects, and Sound
*	objects. You can attempt to play as many Sound objects as you like,
*	however only one Music object can be playing at a time, and playing
*	another will stop the one that was already playing. General settings
*	on musics and sounds can be modified via the mixer.
*
**/

#if !defined(AAB_AUDEN)
#define AAB_AUDEN
#include"audio_connector.hpp"
#include"mixer.hpp"
#include"mixer_factory.hpp"
#include"music.hpp"
#include"sound.hpp"
namespace aab	{
namespace auden	{

	// nothing //

}		//	auden
}		//	aab
#endif	//	AAB_AUDEN
