
/**
*
*	event_type.hpp
*
*
**/

#if !defined(AAB_EVENTS_EVENT_TYPE_CLASS)
#define AAB_EVENTS_EVENT_TYPE_CLASS
namespace aab	{
namespace events{

enum EventType
{
	null_event,
	window_restored_event,
	window_minimised_event,
	mouse_focus_gained_event,
	mouse_focus_lost_event,
	keyboard_focus_gained_event,
	keyboard_focus_lost_event,
	key_down_event,
	key_up_event,
	mouse_move_event,
	mouse_button_down_event,
	mouse_button_up_event,
	gamepad_axis_event,
	gamepad_ball_event,
	gamepad_hat_event,
	gamepad_button_down_event,
	gamepad_button_up_event,
	quit_event,
	window_manager_event,
	video_resize_event,
	user_event
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_EVENT_TYPE_CLASS

