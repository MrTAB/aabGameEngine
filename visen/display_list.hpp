
/**
*
*	display_list.hpp
*
*   DEPRICATED in new opengl specs
**/

#if !defined(AAB_VISEN_DISPLAY_LIST_CLASS)
#define AAB_VISEN_DISPLAY_LIST_CLASS
#include"../types/manager.hpp"
namespace aab	{
namespace visen	{


class DisplayListClass : public aab::types::Manager <DisplayListClass>
{
	public:

		typedef aab::types::Smart <DisplayListClass>::Ptr Ptr;

		void open (bool allowExecutionWhileAbsorbing);// std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
		void close ();

	private:

		unsigned int list;

		DisplayListClass (DisplayListClass &); // no copy

	protected:

		friend class DisplayAbsorber;

		friend class aab::types::Manager <DisplayListClass>::Deleter;

		friend Ptr makeDisplayList ();// std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
		explicit DisplayListClass ();// std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
		virtual ~DisplayListClass ();// throw ();
	public:

	void render () const;
};

typedef DisplayListClass::Ptr DisplayList;

DisplayList makeDisplayList ();// std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error


}		//	visen
}		//	aab
#endif	//	AAB_VISEN_DISPLAY_LIST_CLASS




