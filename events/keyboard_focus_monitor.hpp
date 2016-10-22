
/**
*
*	keyboard_focus_checker.hpp
*
*   Simple class for recording changes in keyboard focus
**/

#if !defined(AAB_EVENTS_KEYBOARD_FOCUS_MONITOR_CLASS)
#define AAB_EVENTS_KEYBOARD_FOCUS_MONITOR_CLASS
#include"empty_event.hpp"
namespace aab	{
namespace events{

class KeyboardFocusMonitor
{
	bool focus_lost;

public:

	void notifyFocusLost () { focus_lost = true; }
	void notifyFocusGained () { focus_lost = false; }

	KeyboardFocusMonitor () : focus_lost(false)
	{	// nothing to do here//
	}

	bool isFocusLost() const
	{
		return focus_lost;
	}

};

}		//	events
}		//	aab
#endif	//	AAB_EVENTS_KEYBOARD_FOCUS_MONITOR_CLASS

