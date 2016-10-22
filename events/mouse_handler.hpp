
/**
*
*	mouse_handler.hpp
*
**/

/* REMOVED - PUT BACK IN FOR TESTING */
//#if 0
#if !defined(AAB_EVENTS_MOUSE_HANDLER_CLASS)
#define AAB_EVENTS_MOUSE_HANDLER_CLASS
#include"imports.hpp"
#include"multi_event_handler.hpp"
namespace aab	{
namespace events{


class MouseHandler : public MultiEventHandler
{
	private:

	class MovedEventHandler;
	class PressedEventHandler;
	class ReleasedEventHandler;
	class FocusGainedHandler;
	class FocusLostHandler;

	public:

	typedef aab::types::Smart <MouseHandler>::Ptr Ptr;

	explicit MouseHandler ();
	virtual ~MouseHandler () throw ();

	virtual void moved (int x, int y, int dx, int dy);
	virtual void buttonPressed (int button, int x, int y);
	virtual void buttonReleased (int button, int x, int y);
	virtual void focusGained ();
	virtual void focusLost ();
};




}		//	events
}		//	aab
#endif	//	AAB_EVENTS_MOUSE_HANDLER_CLASS
//#endif

