
/**
*
*	manager.hpp
*
*   Manager is a base class for classes wishing to be constructed as safe
*   pointers in a way such that they cannot be deleted by client code.
*
**/

#if !defined(AAB_TYPES_MANAGER_CLASS)
#define AAB_TYPES_MANAGER_CLASS
#include"smart_ptr.hpp"
namespace aab	{
namespace types	{

template <class T_Class>
class Manager
{
	protected:

	class Deleter;  // deleter prevents client code from deleting pointer managed by Manager when use din combination with smart pointer.
	friend class Deleter;
	class Deleter
	{
		public:

		void operator () (T_Class *t)
		{
			delete t;
		}
	};

	class NullDeleter
	{
		public:

		void operator () (T_Class *)
		{
			// nothing //
		}
	};


	public:

	virtual ~Manager ()
	{
		// nothing //
	}
};

}		//	types
}		//	aab
#endif	//	AAB_TYPES_MANAGER_CLASS




