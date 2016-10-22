

/**
*
*	push_popper.hpp
*
*   A push popper accepts and pushes an abstract pushpop on construction, and
*   pops that pushpop on deconstruction, ensuring that the pushpop will be both
*   pushed and popped.
*
**/

#if !defined(AAB_TYPES_PUSH_POPPER_CLASS)
#define AAB_TYPES_PUSH_POPPER_CLASS
#include"push_pop.hpp"
namespace aab	{
namespace types	{

class PushPopper
{
	private:

		PushPop & pushPop;

	public:

	explicit PushPopper (PushPop &);
	virtual ~PushPopper () throw ();
};


}		//	types
}		//	aab
#endif	//	AAB_TYPES_PUSH_POPPER_CLASS




