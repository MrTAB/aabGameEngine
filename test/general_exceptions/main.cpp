
#include<exception>
#include<iostream>
#include<string>

/*

exception notes:

	use throw () on deconstructors etc. Anything that is never going to throw.
	use references, allowing polymorphic handling
	handle bad_alloc, possible on invokcation of new.
	mind n make constructors explicit!
	use Foo::Ptr rather than FooPtr for your smart pointers!
	use smart pointers for your D pointer rather than relying on having
		to delete things yourself. Or amke a D pointer which wraps std::auto_ptr
	extending privately, wrapping only construction and deconstruction
	(hence using the same safe deallocation). EDIT: const auto_ptr will do this.

questions:
	should i make the instances that are to be thrown, and throw them,
		or should i construct a new exception to throw each time?
	should i make an exception with a string parameter so that library
		error messages can be transimiited through the error system?



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
*/

using std::exception;

class my_exception : public exception
{
	public: virtual const char * what () const throw ()
	{
		return "my_exception";
	}
};

void method () throw (exception)
{
	throw my_exception ();
}


int main ()
{
	using std::cout;
	using std::cin;
	using std::endl;

	try
	{
		method ();
	}
	catch (exception &e)
	{
		cout << e.what ();
	}
	catch (int)
	{
		cout <<" int";
	}
	catch (...)
	{
		cout << "Unknown exception";
	}

	cin.get ();

	return 0;
}
