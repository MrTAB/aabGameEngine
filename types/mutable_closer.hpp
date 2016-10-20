
/**
*
*	mutable_closer.hpp
*
*	Basically: this will invoke close () on deconstruction, unless you call keep().
*
*	example of why this might be usefull; Your writing an Object
*	Orientated wrapping of some C library, and inside a method
*	you are creating something to stay in that class, unless some
*	other later part of the method fails, in which case you delete
*	everything, including this thing you want to create. A solution
*	is to use std::auto_ptrs for the member, and transfer control
*	to and from at the beginning and end of the method, so if an
*	exception is thrown inbetween, the temporary auto_ptr that
*	took control gets destroyed while in control and takes the
*	created thing with it.
*	For certain simple cases, this MutableCloser seems a little
*	easier to set up and use. Make an object O with operator(), and
*	create a MutableCloser<O>. Your operator() destroys the thing
*	you created. At the end of the method, you call keep () to say
*	that everything went fine, and you can keep it. Before that,
*	any throws out of the function call ~MutableCloser, which
*	chooses to call O::operator() because you haven't called
*	keep() yet. Simple.
*	Seems easier than having some auto_ptr members and transfering
*	control to and from, however it's less general.
*
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




