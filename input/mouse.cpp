
/**
*
*	mouse.cpp
*
**/

#include"mouse.hpp"
#include"../time/time.hpp"
#include<sdl.H>
namespace aab	{
namespace input	{


Mouse makeMouse (InputConnector::Ptr inputConnector)
{
	Mouse ptr (new MouseClass (inputConnector), MouseClass::Deleter () );

	return ptr;
}


/*
	change to remove xrel and yrel: too much nonsense from outside perspective.
*/

MouseClass::MouseClass (InputConnector::Ptr) :
	pumpEvents (false),
	asyncUpdate (true)
{
	/* nothing */
}

MouseClass::~MouseClass () throw ()
{
	/* nothing */
}


void MouseClass::update ()
{
	if (pumpEvents)
	{
		SDL_PumpEvents ();
	}

	if (asyncUpdate)
	{

		int prevX = x;
		int prevY = y;

		buttonMask = SDL_GetMouseState (&x, &y);

		xrel = x - prevX;
		yrel = y - prevY;
	}
	else
	{
		xrel = yrel = 0;
	}
}


void MouseClass::enableEventGrabbing ()
{
	pumpEvents = true;
}

void MouseClass::disableEventGrabbing ()
{
	pumpEvents = false;
}

bool MouseClass::isEventGrabbingEnabled () const
{
	return pumpEvents;
}

void MouseClass::enableAsynchronousUpdate ()
{
	asyncUpdate = true;
}

void MouseClass::disableAsynchronousUpdate ()
{
	asyncUpdate = false;
}

bool MouseClass::isAsynchronousUpdateEnabled () const
{
	return asyncUpdate;
}

void MouseClass::setFakeMove (int x, int y, int dx, int dy)
{
	this-> xrel = dx;
	this-> yrel = dy;
	this-> x = x;
	this-> y = y;
}

void MouseClass::setFakeButtonPress (int button, int x, int y)
{
	buttonMask |= SDL_BUTTON (button);
	this-> xrel = x - this-> x;
	this-> yrel = y - this-> y;
	this-> x = x;
	this-> y = y;
}

void MouseClass::setFakeButtonRelease (int button, int x, int y)
{
	buttonMask = ~((~buttonMask) ^ SDL_BUTTON (button));
	this-> xrel = x - this-> x;
	this-> yrel = y - this-> y;
	this-> x = x;
	this-> y = y;
}


}		//	input
}		//	aab





