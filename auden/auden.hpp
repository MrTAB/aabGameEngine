
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
*	to begin with. Use this to create an instance of Mixer, which sets
*	up the mixing channels. Then you can create Music objects, and Sound
*	objects. You can play as many Sound objects as you like, at a time,
*	however only one Music object can be playing at a time, and playing
*	another will stop the one that was already playing. General settings
*	on musics and sounds can be modified via the mixer. That is all..
*	Oh and one more thing.. Deconstruction handles all, so no need for
*	you to do any cleanup apart from in whatever Audio Connector
*	subclass you make, unlesss you use someone elses
*		*cough* visen::Screen *cough*.
*
*		^__^. That is all.
*
*
*	..though, if you need more detail, look in the headers of each class.
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
