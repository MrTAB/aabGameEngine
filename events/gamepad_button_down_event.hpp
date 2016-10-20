
/**
*
*	gamepad_button_down_event.hpp
*
**/

#if !defined(AAB_EVENTS_GAMEPAD_BUTTON_DOWN_EVENT_CLASS)
#define AAB_EVENTS_GAMEPAD_BUTTON_DOWN_EVENT_CLASS
#include"event.hpp"
#include"internal_event.hpp"
#include"imports.hpp"
namespace aab	{
namespace events{


class GamepadButtonDownEvent : public Event
{
	private:

		unsigned int id;
		unsigned int button;

	public:

	typedef aab::types::Smart <GamepadButtonDownEvent>::Ptr Ptr;

	explicit GamepadButtonDownEvent (InternalEvent e);
	virtual ~GamepadButtonDownEvent () throw ();

	int getGamePadId () const;
	int getButton () const;

	static EventType getClassEventType ();
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_GAMEPAD_BUTTON_DOWN_EVENT_CLASS

