
/**
*
*	internal_event.cpp
*
*
**/

#include"internal_event.hpp"
#include<sdl.h>
namespace aab	{
namespace events{


struct InternalEventClass::Data
{
	SDL_Event event;
};



InternalEvent makeInternalEvent ()
{
	InternalEvent ptr (new InternalEventClass (), InternalEventClass::Deleter ());
	return ptr;
}

InternalEventClass::InternalEventClass () : data (new Data ())
{
	// nothing //
}

InternalEventClass::~InternalEventClass ()
{
	// nothing //
}

void * InternalEventClass::getReference ()
{
	return static_cast <void *> (&(data-> event));
}

bool InternalEventClass::waitOn ()
{
	return SDL_WaitEvent  (static_cast <SDL_Event *> (&(data-> event)));
}

bool InternalEventClass::pollOn ()
{
	return SDL_PollEvent  (static_cast <SDL_Event *> (&(data-> event)));
}

int InternalEventClass::getType () const
{
	return data-> event.type;
}

}		//	events
}		//	aab



