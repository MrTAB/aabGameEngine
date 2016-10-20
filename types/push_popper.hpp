

/**
*
*	push_popper.hpp
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




