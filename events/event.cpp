
/**
*
*	event.cpp
*
*
**/

#include"event.hpp"
namespace aab	{
namespace events{


Event::Event (EventType type) : type (type)
{
	// nothing //
}

Event::~Event () throw ()
{
	// nothing //
}

EventType Event::getType () const
{
	return type;
}


}		//	events
}		//	aab



