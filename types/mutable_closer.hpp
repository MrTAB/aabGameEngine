
/**
*
*	mutable_closer.hpp
*
*	This will invoke close () on deconstruction, unless you call keep().
*   close is a supplied object with the function operator () implemented.
*
*   This is useful when you are allocating a series of objects in a method and
*   any one of them may throw an exception - an object supplied as the template
*   argument to mutable closer can be set up to deallocate the generated objects
*   on operator(). If an exception is thrown, they will all be deallocated, but
*   if not keep() can be called after all the objects have been allocated, and
*   thus the MutableCloser will do nothing.
**/

#if !defined(AAB_TYPES_MUTABLE_CLOSER_CLASS)
#define AAB_TYPES_MUTABLE_CLOSER_CLASS
namespace aab	{
namespace types	{

template <typename T>
class MutableCloser
{
	private:

		bool destroy;
		T &close;

	public:

	explicit MutableCloser (T &close_in) throw () : destroy (true), close (close_in)
	{
	}

	virtual ~MutableCloser () throw ()
	{
		if (destroy)
		{
			close ();
		}
	}

	void keep () throw ()
	{
		destroy = false;
	}
};

}		//	types
}		//	aab
#endif	//	AAB_TYPES_MUTABLE_CLOSER_CLASS




