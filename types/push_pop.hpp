
/**
*
*	push_pop.hpp
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




