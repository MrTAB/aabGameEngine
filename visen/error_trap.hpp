
/**
*
*	error_trap.hpp
*
*	Various internally used commands revolve around C libraries with
*	GetError () mechanisms. Rather than having the internal code
*	either a) oblivious to these errors or b) cluttered trying to
*	check them, internal methods in visen use an instance of this
*	class. They create an ErrorTrap before calling the methods;
*	This clears these libraries error codes. They then call tryRaise()
*	which throws an exception if the libraries GetError() code
*	returns that something has went wrong. This exception is then
*	either caught and handled by the method using the ErrorTrap,
*	or is propagated up to user code as an exception.
*
**/

#if !defined(AAB_VISEN_ERROR_TRAP_CLASS)
#define AAB_VISEN_ERROR_TRAP_CLASS
#include"../types/smart_ptr.hpp"
#include<string>
//#include<memory>
//#include<exception>
//#include<map>
namespace aab	{
namespace visen	{

class ErrorTrap
{
	private:

        /*
		typedef std::map < int, std::exception*> ErrorMap;

		static ErrorMap errorMap;
		static bool initialised;

		static void initialise ();*/
		
		std::string method_name;

	public:

	typedef aab::types::Smart <ErrorTrap>::Ptr Ptr;

	//explicit ErrorTrap ();
	explicit ErrorTrap (std::string method_name);

	virtual ~ErrorTrap ();

	void clearErrors ();

	void tryRaise ();// std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
};


}		//	visen
}		//	aab
#endif	//	AAB_VISEN_ERROR_TRAP_CLASS




