
/**
*
*	events.hpp
*
*	Include this to include all headers under the events namespace.
*	link to the static library libevent.a to define the classes.
*
*
**/

#if !defined(AAB_EVENTS)
#define AAB_EVENTS
#include"dispatcher.hpp"
#include"event.hpp"
#include"event_connector.hpp"
#include"event_handler.hpp"
#include"event_handler_template.hpp"
#include"event_handlers.hpp"
#include"event_queue.hpp"
#include"event_type.hpp"
#include"internal_event.hpp"
#include"mouse_move_event.hpp"
#include"mouse_handler.hpp"
#include"mouse_auto_handler.hpp"
#include"quit_event.hpp"
#include"close_handler.hpp"
#include"keyboard_handler.hpp"
#include"keyboard_auto_handler.hpp"
#include"gamepads_handler.hpp"
#include"gamepad_port_handler.hpp"
#include"gamepads_auto_handler.hpp"
#include"keyboard_focus_monitor.hpp"
#include"notified_event_handler.hpp"
namespace aab	{
namespace events{

	// nothing //

}		//	events
}		//	aab
#endif	//	AAB_EVENTS




