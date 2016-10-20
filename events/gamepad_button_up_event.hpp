
/**
*
*	gamepad_button_up_event.hpp
*
**/

#if !defined(AAB_EVENTS_GAMEPAD_BUTTON_UP_EVENT_CLASS)
#define AAB_EVENTS_GAMEPAD_BUTTON_UP_EVENT_CLASS
#include"event.hpp"
#include"internal_event.hpp"
#include"imports.hpp"
namespace aab	{
namespace events{


class GamepadButtonUpEvent : public Event
{
	private:

		unsigned int id;
		unsigned int button;

	public:

	typedef aab::types::Smart <GamepadButtonUpEvent>::Ptr Ptr;

	explicit GamepadButtonUpEvent (InternalEvent e);
	virtual ~GamepadButtonUpEvent () throw ();

	int getGamePadId () const;
	int getButton () const;

	static EventType getClassEventType ();
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_GAMEPAD_BUTTON_UP_EVENT_CLASS

