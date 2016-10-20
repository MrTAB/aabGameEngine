
/**
*
*	gamepad_hat_event.hpp
*
**/

#if !defined(AAB_EVENTS_GAMEPAD_HAT_EVENT_CLASS)
#define AAB_EVENTS_GAMEPAD_HAT_EVENT_CLASS
#include"event.hpp"
#include"internal_event.hpp"
#include"imports.hpp"
#include"../input/hat_position.hpp"
namespace aab	{
namespace events{


class GamepadHatEvent : public Event
{

	public:

	typedef aab::types::Smart <GamepadHatEvent>::Ptr Ptr;
	typedef aab::input::HatPosition HatPosition;

	private:

		int id;
		unsigned char hat;
		HatPosition value;

	public:

	explicit GamepadHatEvent (InternalEvent e);
	virtual ~GamepadHatEvent () throw ();

	int getGamePadId () const;
	int getHatId () const;
	HatPosition getHatPosition () const;

	static EventType getClassEventType ();
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_GAMEPAD_HAT_EVENT_CLASS

