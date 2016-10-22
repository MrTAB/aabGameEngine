/**
*
*	maybe.hpp
*
*   This is a quick implementation of a Maybe type - something which may or
*   may not be a valuable instance of the given type. Used to return an object
*   from a method conditionally. A default blank instance of the type will be
*   supplied, and in debug mode, an exception will be thrown for access of this
*   blank instance.
*
**/

#if !defined(AAB_TYPES_MAYBE_CLASS)
#define AAB_TYPES_MAYBE_CLASS
#include<test/debug_assertions.hpp>
namespace aab	{
namespace types	{



template <typename T_Type>
class Maybe
{
	private:

		T_Type value;
		bool has;

	public:

	explicit Maybe () : has (false)
	{
		// nothing //
	}

	explicit Maybe (T_Type value_in, bool has_in) : value (value_in), has (has_in)
	{
		// nothing //
	}

	// implicit //
	Maybe (T_Type value_in) : value (value_in), has (true)
	{
		// nothing //
	}

	/* implicit */ Maybe (bool has_in) : has (has_in)
	{
		// nothing //
	}

	//implicit Maybe (const Maybe);
	//implicit Maybe& operator = (const Maybe);
	/*
	Maybe & operator = (T_Type)
	{
		//
	}*/

	bool exists () const
	{
		return has;
	}

	T_Type get () const
	{
		return value;
	}

	operator T_Type () const// _DEBUG_THROW(std::logic_error&)
	{
		if (! has)
		{
			_DEBUG_RESPONSE(throw std::logic_error ("Accessed Maybe<T> object does not exist. "));
		}
		return value;
	}
	
	T_Type & operator = (const T_Type& other)
	{
	    value = other;
	    has = true;
	}

	void clear ()
	{
		has = false;
		value = (T_Type());
	}

};

template<>
class Maybe <bool>
{
	static void undefined_because_of_invalid_typename ();
};


}	// types
}	// aab
#endif // AAB_TYPES_MAYBE_CLASS

