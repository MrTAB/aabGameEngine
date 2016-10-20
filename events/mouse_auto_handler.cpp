
/**
*
*	mouse_auto_handler.cpp
*
**/

/* REMOVED */
#if 0
#include"mouse_auto_handler.hpp"
namespace aab	{
namespace events{


MouseAutoHandler::MouseAutoHandler (Mouse mouse) : mouse (mouse)
{
	mouse-> disableEventGrabbing ();
	mouse-> disableAsynchronousUpdate ();
}

MouseAutoHandler::~MouseAutoHandler () throw ()
{
	// nothing //
}

void MouseAutoHandler::moved (int x, int y, int dx, int dy)
{
	mouse-> setFakeMove (x, y, dx, dy);
}

void MouseAutoHandler::buttonPressed (int button, int x, int y)
{
	mouse-> setFakeButtonPress (button, x, y);
}

void MouseAutoHandler::buttonReleased (int button, int x, int y)
{
	mouse-> setFakeButtonRelease (button, x, y);
}


}		//	events
}		//	aab

#endif



