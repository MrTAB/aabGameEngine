
/**
*
*	push_pop.hpp
*
*   An abstract class for actions which represent a temporary change in state.
*
**/

#if !defined(AAB_TYPES_PUSH_POP_CLASS)
#define AAB_TYPES_PUSH_POP_CLASS
namespace aab	{
namespace types	{

//abstract//
class PushPop
{
	public:

	virtual ~PushPop ()
	{
		// nothing //
	}

	virtual void push () = 0;
	virtual void pop () = 0;
};


}		//	types
}		//	aab
#endif	//	AAB_TYPES_PUSH_POP_CLASS




