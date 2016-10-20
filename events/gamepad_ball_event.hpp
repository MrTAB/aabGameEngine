
/**
*
*	gamepad_ball_event.hpp
*
**/

#if !defined(AAB_EVENTS_GAMEPAD_BALL_EVENT_CLASS)
#define AAB_EVENTS_GAMEPAD_BALL_EVENT_CLASS
#include"event.hpp"
#include"internal_event.hpp"
#include"imports.hpp"
namespace aab	{
namespace events{


class GamepadBallEvent : public Event
{
	private:

		int id;
		int ball;
		short int xrel;
		short int yrel;

	public:

	typedef aab::types::Smart <GamepadBallEvent>::Ptr Ptr;

	explicit GamepadBallEvent (InternalEvent e);
	virtual ~GamepadBallEvent () throw ();

	int getGamePadId () const;
	int getBallId () const;
	int16_t getRawXChange () const;
	int16_t getRawYChange () const;
	GamepadAxisValue getXChange () const;
	GamepadAxisValue getYChange () const;

	static EventType getClassEventType ();
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_GAMEPAD_BALL_EVENT_CLASS

