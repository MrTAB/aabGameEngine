
/**
*
*	close_handler.cpp
*
**/

#include"close_handler.hpp"
namespace aab	{
namespace events{

CloseHandler::CloseHandler () : quitYet (false)
{
	// nothing //
}

bool CloseHandler::hasClosed () const
{
	return quitYet;
}

void CloseHandler::close ()
{
	quitYet = true;
}

void CloseHandler::handleEvent (const EventData)
{
	close ();
}

}		//	events
}		//	aab



