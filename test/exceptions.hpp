
/**
*
*	exceptions.hpp
*
*   Some small utility exceptions, as well as inclusion of standard exceptions.
**/

/*

exception notes:

	If you use throw () on deconstructors etc. Anything that is never going to throw, then the program will terminate itself if an exception is thrown within/under that function.
	use references, allowing polymorphic handling
	handle bad_alloc, possible on invocation of new.		


standard exceptions:

	bad_alloc	thrown by new on allocation failure
	bad_cast	thrown by dynamic_cast when fails with a referenced type
	bad_exception	thrown when an exception type doesn't match any catch
	bad_typeid	thrown by typeid
	ios_base::failure	thrown by functions in the iostream library

	logic_errors and runtime_errors take const char* into their constructor args
	generally, make a subclass of logic_error or runtime_error, not its subclasses?

	logic_error	Logic errors represent problems in the internal logic of a program; in theory, these are preventable, and even detectable before the program runs (e.g., violations of class invariants).

		domain_error		Thrown by the library, or by you, to report domain errors (domain in the mathmatical sense).
		invalid_argument	Thrown to report invalid arguments to functions.
		length_error		Thrown when an object is constructed that would exceed its maximum permitted size (e.g., a basic_string instance).
		out_of_range		This represents an argument whose value is not within the expected range (e.g., boundary checks in basic_string).


	runtime_error	Runtime errors represent problems outside the scope of a program; they cannot be easily predicted and can generally only be caught as the program executes.

		overflow_error		//Thrown to indicate arithmetic overflow.
		range_error		//Thrown to indicate range errors in internal computations.
		underflow_error		//Thrown to indicate arithmetic underflow.
		system_error    //Thrown to indicate low level system error. has a code()
*/


#if !defined(AAB_TEST_EXCEPTIONS)
#define AAB_TEST_EXCEPTIONS
#include<exception>
#include<stdexcept>
namespace aab	{
namespace test	{

class file_not_found_error : public std::runtime_error
{
	public: 
	
	explicit file_not_found_error (const std::string& message) : runtime_error (message)
	{
	    // do nothing //
	}
	
	explicit file_not_found_error (const char *message) : runtime_error (message)
	{
	    // do nothing //
	}
};



class already_instantiated_error : public std::runtime_error
{
	public: 
	
	explicit already_instantiated_error (const std::string& message) : runtime_error (message)
	{
	    // do nothing //
	}
	
	explicit already_instantiated_error (const char *message) : runtime_error (message)
	{
	    // do nothing //
	}
};



}		//	test
}		//	aab
#endif	//	AAB_TEST_DIAGNOSTIC_CLASS




