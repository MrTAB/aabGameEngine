
/**
*
*	event_handlers.hpp
*
*   This header collects together all the event handlers in the API
*
**/

#if !defined(AAB_EVENTS_EVENT_HANDLERS)
#define AAB_EVENTS_EVENT_HANDLERS
#include"event_handler_template.hpp"

/* NOT REMOVED */
//#if 0
#include"mouse_move_event.hpp"
#include"mouse_button_down_event.hpp"
#include"mouse_button_up_event.hpp"
//#endif

#include"quit_event.hpp"
#include"key_up_event.hpp"
#include"key_down_event.hpp"
#include"window_restored_event.hpp"
#include"window_minimised_event.hpp"
#include"mouse_focus_gained_event.hpp"
#include"mouse_focus_lost_event.hpp"
#include"keyboard_focus_gained_event.hpp"
#include"keyboard_focus_lost_event.hpp"
#include"gamepad_axis_event.hpp"
#include"gamepad_ball_event.hpp"
#include"gamepad_hat_event.hpp"
#include"gamepad_button_up_event.hpp"
#include"gamepad_button_down_event.hpp"
#include"video_resize_event.hpp"
namespace aab	{
namespace events{

/* REMOVED -  ADDED BACK IN TO TEST*/
//#if 0
typedef EventHandlerTemplate <MouseMoveEvent> MouseMoveHandler;
typedef EventHandlerTemplate <MouseButtonDownEvent> MouseButtonDownHandler;
typedef EventHandlerTemplate <MouseButtonUpEvent> MouseButtonUpHandler;
//#endif

typedef EventHandlerTemplate <QuitEvent> QuitHandler;
typedef EventHandlerTemplate <KeyUpEvent> KeyUpHandler;
typedef EventHandlerTemplate <KeyDownEvent> KeyDownHandler;
typedef EventHandlerTemplate <WindowRestoredEvent> WindowRestoredHandler;
typedef EventHandlerTemplate <WindowMinimisedEvent> WindowMinimisedHandler;
typedef EventHandlerTemplate <MouseFocusGainedEvent> MouseFocusGainedHandler;
typedef EventHandlerTemplate <MouseFocusLostEvent> MouseFocusLostHandler;
typedef EventHandlerTemplate <KeyboardFocusGainedEvent> KeyboardFocusGainedHandler;
typedef EventHandlerTemplate <KeyboardFocusLostEvent> KeyboardFocusLostHandler;
typedef EventHandlerTemplate <GamepadAxisEvent> GamepadAxisHandler;
typedef EventHandlerTemplate <GamepadBallEvent> GamepadBallHandler;
typedef EventHandlerTemplate <GamepadHatEvent> GamepadHatHandler;
typedef EventHandlerTemplate <GamepadButtonUpEvent> GamepadButtonUpHandler;
typedef EventHandlerTemplate <GamepadButtonDownEvent> GamepadButtonDownHandler;
typedef EventHandlerTemplate <VideoResizeEvent> VideoResizeHandler;



/*
	-Handlers-

*WindowRestoredHandler
*WindowMinimisedHandler
*MouseFocusGainedHandler
*MouseFocusLostHandler
*KeyboardFocusGainedHandler
*KeyboardFocusLostHandler
*KeyDownHandler
*KeyUpHandler
*MouseMoveHandler
*MouseButtonDownHandler
*MouseButtonUpHandler
*GamepadAxisHandler
*GamepadBallHandler
*GamepadHatHandler
*GamePadButtonDownHandler
*GamePadButtonUpHandler
*QuitHandler
WindowManagerHandler	// Do later: Special Case.
*VideoResizeHandler
UserEventHandler	// Do later: Special Case.

	-MultiHandlers-

*MouseHandler:
	*MouseFocusGainedHandler
	*MouseFocusLostHandler
	*MouseMoveHandler
	*MouseButtonDownHandler
	*MouseButtonUpHandler
	*use of input::Mouse
*GamepadHandler:
	*GamepadAxisHandler
	*GamepadBallHandler
	*GamepadHatHandler
	*GamePadButtonDownHandler
	*GamePadButtonUpHandler
	use of input::Gamepad
*KeyboardHandler
	*KeyboardFocusGainedHandler
	*KeyboardFocusLostHandler
	*KeyDownHandler
	*KeyUpHandler
	*use of input::KeyState
VideoResizeAutoHandler (takes a Screen)	// Do ltaer: Special Case.
*/


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_EVENT_HANDLERS

