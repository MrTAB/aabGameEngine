
/**
*
*	gamepad_axis_event.hpp
*
**/

#if !defined(AAB_EVENTS_GAMEPAD_AXIS_EVENT_CLASS)
#define AAB_EVENTS_GAMEPAD_AXIS_EVENT_CLASS
#include"event.hpp"
#include"internal_event.hpp"
#include"imports.hpp"
namespace aab	{
namespace events{


class GamepadAxisEvent : public Event
{
	private:

		int id;
		int axis;
		GamepadAxisValue value;

	public:

	typedef aab::types::Smart <GamepadAxisEvent>::Ptr Ptr;

	explicit GamepadAxisEvent (InternalEvent e);
	virtual ~GamepadAxisEvent () throw ();

	int getGamePadId () const;
	bool isXAxis () const;
	bool isYAxis () const;
	int getWhichAxis () const;
	int16_t getRawValue () const;
	GamepadAxisValue getAxisValue () const;

	static EventType getClassEventType ();
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_GAMEPAD_AXIS_EVENT_CLASS

