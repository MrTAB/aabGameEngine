
/**
*
*	display_list.cpp
*
**/

#include"display_list.hpp"
#include"error_trap.hpp"
#include"_include_opengl.hpp"
#include<stdexcept>
namespace aab	{
namespace visen	{


DisplayList makeDisplayList ()// throw (std::exception &)
{
	DisplayList ptr (new DisplayListClass (), DisplayListClass::Deleter ());
	return ptr;
}


DisplayListClass::DisplayListClass ()// std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
{
    ErrorTrap trap("DisplayListClass::DisplayListClass::");
    
	list = glGenLists (1);
	
	trap.tryRaise();

	if (! list)
	{
		throw std::runtime_error ("DisplayListClass::DisplayListClass::\tFailed to generate Display list.");
	}
}

DisplayListClass::~DisplayListClass () //throw ()
{
	glDeleteLists (list, 1);
}

void DisplayListClass::open (bool allow) // std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
{
	ErrorTrap trap ("DisplayListClass::open::\t");

	glNewList (list, allow ? GL_COMPILE_AND_EXECUTE : GL_COMPILE);

	trap.tryRaise ();
}

void DisplayListClass::close ()
{
	glEndList ();
}

void DisplayListClass::render () const
{
	glCallList (list);
}


}	//	visen
}	//	aab


