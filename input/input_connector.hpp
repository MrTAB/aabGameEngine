
/**
*
*	input_connector.hpp
*
*	InputConnector class	-
*		certain input classes depend on there being a connection to input devices.
*		certain classes can create this connection automatically, such as Screen.
*		Thus, it is sensible to enforce creation of a connecting class before
*		those that need it by making an argument in their constructors one or
*		all or some of those classes.. Or more conveniently, a superclass;
*		This is that superclass, and it is known as an InputConnector.
*			Proper use requires that the constructor of the subclass makes the
*		required connection, and keeps it as available as possible until its
*		deconstruction. Failure to make the connection should result in some
*		exception being thrown to the client module.
*
*	InputConnector is noncopy-constuctable.
**/

#if !defined(AAB_INPUT_INPUT_CONNECTOR_CLASS)
#define AAB_INPUT_INPUT_CONNECTOR_CLASS
#include"../types/smart_ptr.hpp"
namespace aab	{
namespace input	{


class InputConnector
{
	private:

		InputConnector (InputConnector&); //no copy

	protected:

		explicit InputConnector ()
		{
            // do nothing //
        };
		virtual ~InputConnector()// throw () 
		{
		    // do nothing //
		}

	public:

	typedef aab::types::Smart <InputConnector>::Ptr Ptr;


};




}		//	input
}		//	aab
#endif	//	AAB_INPUT_INPUT_CONNECTOR_CLASS
