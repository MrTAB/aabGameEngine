
/**
*
*	smart_ptr.hpp
*
*   Now simply a typedef for the boost shared pointer
*
**/

#if !defined(AAB_TYPES_SMART_POINTER_CLASS)
#define AAB_TYPES_SMART_POINTER_CLASS
#define BOOST_ENABLE_ASSERT_HANDLER
#include<boost/smart_ptr.hpp>
#include<boost/pointer_cast.hpp>
namespace aab	{
namespace types	{

template <typename T>
struct Smart
{
	typedef boost::shared_ptr <T> Ptr;
};

}		//	types
}		//	aab
#endif	//	AAB_TYPES_SMART_POINTER_CLASS




