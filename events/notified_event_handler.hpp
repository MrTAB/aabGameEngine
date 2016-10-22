
/**
*
*	notified_event_handler.hpp
*
*   Event Handlers for lost focus
**/

#if !defined(AAB_EVENTS_KEYBOARD_NOTIFIED_EVENT_HANDLER)
#define AAB_EVENTS_KEYBOARD_NOTIFIED_EVENT_HANDLER
#include"empty_event.hpp"
#include"keyboard_focus_monitor.hpp"
namespace aab	{
namespace events{

class NotifiedKeyboardFocusGainedHandler : public KeyboardFocusGainedHandler
{
	KeyboardFocusMonitor* keyboardFocusMonitor;

	public:

	explicit NotifiedKeyboardFocusGainedHandler (KeyboardFocusMonitor * keyboardFocusMonitorIn): keyboardFocusMonitor(keyboardFocusMonitorIn)
	{	// nothing to do here //
	}

	void handleEvent (const EventData)
	{
		keyboardFocusMonitor-> notifyFocusGained();
	}
};

class NotifiedKeyboardFocusLostHandler : public KeyboardFocusLostHandler
{
	KeyboardFocusMonitor * keyboardFocusMonitor;

	public:

	explicit NotifiedKeyboardFocusLostHandler (KeyboardFocusMonitor * keyboardFocusMonitorIn): keyboardFocusMonitor(keyboardFocusMonitorIn)
	{	// nothing to do here //
	}

	void handleEvent (const EventData)
	{
		keyboardFocusMonitor-> notifyFocusLost();
	}
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_KEYBOARD_NOTIFIED_EVENT_HANDLER

