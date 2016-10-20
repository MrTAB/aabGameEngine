
/**
*
*	push_popper.cpp
*
**/


#include"push_popper.hpp"
namespace aab	{
namespace types	{
typedef PushPopper PP;


PP::PushPopper (PushPop & pushPop) : pushPop (pushPop)
{
	pushPop.push ();
}

PP::~PushPopper () throw ()
{
	pushPop.pop ();
}


}		//	types
}		//	aab





