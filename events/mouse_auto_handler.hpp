
/**
*
*	mouse_auto_handler.hpp
*
*   Updates a Mouse object with data from the events invoked (moved, buttonPressed).
*
*   While intended for translating events into updates to client mouse object
*   states, mouse handlers (and other handles) can have these methods invoked
*   intentionally by the client to pretend that an event has occurred.
**/

/* REMOVED */
#if 0
#if !defined(AAB_EVENTS_MOUSE_AUTO_HANDLER_CLASS)
#define AAB_EVENTS_MOUSE_AUTO_HANDLER_CLASS
#include"imports.hpp"
#include"mouse_handler.hpp"
#include"../input/mouse.hpp"
namespace aab	{
namespace events{

class MouseAutoHandler : public MouseHandler
{
	public:

	typedef aab::types::Smart <MouseAutoHandler>::Ptr Ptr;
	typedef input::Mouse Mouse;

	private:

		Mouse mouse;

	public:

	explicit MouseAutoHandler (Mouse);
	virtual ~MouseAutoHandler () throw ();

	void moved (int x, int y, int dx, int dy);
	void buttonPressed (int button, int x, int y);
	void buttonReleased (int button, int x, int y);
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_MOUSE_AUTO_HANDLER_CLASS
#endif

