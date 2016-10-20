
/**
*
*	error_trap.cpp
*
**/

#include"error_trap.hpp"
#include"_include_opengl.hpp"
#include<sdl.H>
#include<exception>
#include<stdexcept>
#include<sstream>
namespace aab	{
namespace visen	{

/*
ErrorTrap::ErrorMap ErrorTrap::errorMap;
bool ErrorTrap::initialised (false);

static std::domain_error gl_invalid_enum ("OpenGl: invalid enum");
static std::invalid_argument gl_invalid_value ("OpenGl: invalid value");
static std::logic_error gl_invalid_operation("OpenGl: invalid operation");
static std::runtime_error gl_stack_overflow("OpenGl: stack overflow");
static std::runtime_error gl_stack_underflow("OpenGl: stack underflow");
static std::runtime_error gl_out_of_memory("OpenGl: out of memory");

void ErrorTrap::initialise ()
{
	errorMap[GL_NO_ERROR] = NULL;
	errorMap[GL_INVALID_ENUM] = &gl_invalid_enum;
	errorMap[GL_INVALID_VALUE] = &gl_invalid_value;
	errorMap[GL_INVALID_OPERATION] = &gl_invalid_operation;
	errorMap[GL_STACK_OVERFLOW] = &gl_stack_overflow;
	errorMap[GL_STACK_UNDERFLOW] = &gl_stack_underflow;
	errorMap[GL_OUT_OF_MEMORY] = &gl_out_of_memory;

	initialised = true;
}
*/

/*ErrorTrap::ErrorTrap ()
{
	if (! initialised)
	{
		initialise ();
	}

	clearErrors ();
	
}*/

ErrorTrap::ErrorTrap (std::string method_name_in):
    method_name(method_name_in)
{
    /*
	if (! initialised)
	{
		initialise ();
	}

	clearErrors ();
	*/
}

ErrorTrap::~ErrorTrap ()
{
	// nothing //
}

void ErrorTrap::clearErrors ()
{
	while (glGetError () != GL_NO_ERROR)
	{
		// nothing //
	}
}

void ErrorTrap::tryRaise ()// std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
{
    /*
	std::exception *error = errorMap [glGetError ()];

	if (error != NULL)
	{
		throw *error;
	}*/
	
	std::stringstream error;
	error << method_name << "\t";
	
	switch(glGetError())
    {        
        case GL_INVALID_ENUM:
        {
            error << "OpenGl: invalid enum";
        	throw std::domain_error (error.str());
        }
        case GL_INVALID_VALUE:
        {
            error << "OpenGl: invalid value";
        	throw std::invalid_argument(error.str());
        }
        case GL_INVALID_OPERATION:
        {
            error << "OpenGl: invalid operation";
        	throw std::logic_error(error.str());
        }
        case GL_INVALID_FRAMEBUFFER_OPERATION:
        {
            error << "OpenGl: invalid framebuffer operation.";
            throw std::logic_error(error.str());
        }
        case GL_STACK_OVERFLOW:
        {
            error << "OpenGl: stack overflow";
        	throw std::runtime_error(error.str());
        }
        case GL_STACK_UNDERFLOW:
        {
            error << "OpenGl: stack underflow";
        	throw std::runtime_error(error.str());
        }
        case GL_OUT_OF_MEMORY:
        {
            error << "OpenGl: out of memory";
        	throw std::runtime_error(error.str());
        }
        case GL_NO_ERROR:        
        {
            return;
        }
        default:
        {
            error << "OpenGl: unknown error code reported.";
        	throw std::runtime_error(error.str());
        }
    }
}

}		//	visen
}		//	aab





