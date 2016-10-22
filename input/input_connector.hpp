
/**
*
*	input_connector.hpp
*
*	InputConnector class	-
        Various input classes require a connection to input devices be prepared
        before they are instantiated. An InputConnector creates this connection,
        and is thus required to create objects of said type.
        
        InputConnector is a semi-abstract, non-copyable interface which can be
        implemented by classes which establish or verify the input connection
        themselves, and can thus be supplied to the input classes demanding
        a connection to verify that a connection has been established. The
        InputConnector should then maintain the connection for its lifetime,
        which is naturally longer than the dependent input classes on the stack.
        This is a Resource Acquisition Is Initialisation  library format, rather
        than approach of having a "Device" object from which all resources are
        demanded. The idea is to use RAII to avoid a God-class anti-pattern
        emerging form the ever growing would be "Device".
        
        An example of this kind of class is the visen::Screen, which sets up
        the required input subsystem.
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
