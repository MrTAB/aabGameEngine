
/**
*
*	mouse.hpp
*
*	Mouse - updates and describes the state of the mouse
*
*	Make an instance of Mouse, calling update () every round, to check
*	the x and y positions of the mouse, and the values of its buttons.
*
*	In general, the buttons are:
*	1-	left
*	2-	middle
*	3-	right
*
*	Use methods like enableEventPumping() to enable and disable eventpumping.
*	If you are using an event handling system alongside this, it will handle
*	the event pumping, and so update() needs to know not to use event pumping.
*	Disable it with disableEventPumping (). Alternatively, you may have multiple
*	systems which have event pumping; Only one of these should have eventpumping
*	enabled, and so it is also wise to invoke its update first, as it will
*	handle the event pumping.
*
*	Mouse is a noncopyable class.
*/

#if !defined(AAB_INPUT_MOUSE_CLASS)
#define AAB_INPUT_MOUSE_CLASS
#include"input_connector.hpp"
#include"mouse_data.hpp"
#include<vector>
namespace aab	{
namespace input	{

class MouseClass : public MouseDataClass
{
	public:

		typedef aab::types::Smart <MouseClass>::Ptr Ptr;

	private:

		bool pumpEvents;
		bool asyncUpdate;

	protected:

		friend Ptr makeMouse (InputConnector::Ptr);
		explicit MouseClass (InputConnector::Ptr);
		virtual ~MouseClass () throw ();


	public:

	void update ();

	void enableEventGrabbing ();
	void disableEventGrabbing ();
	bool isEventGrabbingEnabled () const;

	void enableAsynchronousUpdate ();
	void disableAsynchronousUpdate ();
	bool isAsynchronousUpdateEnabled () const;

	void setFakeMove (int x, int y, int dx, int dy);
	void setFakeButtonPress (int button, int x, int y);
	void setFakeButtonRelease (int button, int x, int y);
};

typedef MouseClass::Ptr Mouse;

Mouse makeMouse (InputConnector::Ptr);


}		//	input
}		//	aab
#endif	//	AAB_INPUT_MOUSE_CLASS




