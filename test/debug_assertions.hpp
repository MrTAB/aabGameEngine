
/**
*
*	debug_assertions.hpp
*
*   Define _DEBUG and include this file to have _DEBUG_RESPONSE(x) evaluate to x
*   and _RELEASE_RESPONSE(x) to evaluate to nothing.
*   Leave _DEBUG undefined and include this file to have _DEBUG_RESPONSE(x)
*   evaluate to nothing and _RELEASE_RESPONSE(x) to evaluate to x.
*
*   With _DEBUG defined, _DEBUG_ONLY(x) can also be used, e.g. for diagnostic
*   printout.
*
*   Finally, _DEBUG_ASSERTION and _RELEASE_ASSERTION can be used just like
*   _DEBUG_RESPONSE and _RELEASE_RESPONSE, except the second argument is the
*   action to take, and the first argument is a condition which must be true
*   for that action to be taken.
*
*   Examples:
*
*   void set_image_width(int width, int height)
*   {
*       _DEBUG_ASSERTION(width<=0, throw std::invalid_argument("set_image_width:: width must be greater than 0"));
*       _RELEASE_ASSERTION(width<=0, width = DEFAULT_WIDTH); // behave well under release to maintain gameplay: perhaps send warning to layer to save and reload?
*
*       if (height < 0)
*       {
*           _DEBUG_RESPONSE(throw std::invalid_argument("set_image_width:: height must be greater than 0"));
*           _RELEASE_RESPONSE(height = DEFAULT_HEIGHT);
*       }
*
*       _DEBUG_ONLY(::log_file << "set_image_width::\t Image width and height are valid.\n");
*   )
**/

#if !defined(AAB_TEST_DEBUG_ASSERTIONS_CLASS)
#define AAB_TEST_DEBUG_ASSERTIONS_CLASS

#ifdef _DEBUG
    #include<stdexcept>
    #define _DEBUG_RESPONSE(a) a
    #define _RELEASE_RESPONSE(a)
    #define _DEBUG_ONLY(a) a
    #define _RELEASE_ONLY(a)
    #define _DEBUG_ASSERTION(cond, result) if(cond){ result; }
    #define _RELEASE_ASSERTION(cond, result)
    #define _DEBUG_THROW(a) throw(a)
#else
    #define _DEBUG_RESPONSE(a)
    #define _RELEASE_RESPONSE(a) a
    #define _DEBUG_ONLY(a)
    #define _RELEASE_ONLY(a) a
    #define _DEBUG_ASSERTION(cond, result)
    #define _RELEASE_ASSERTION(cond, result) if(cond){ result; }
    #define _DEBUG_THROW(a)
    //disable uses of assert()
    #define NDEBUG
#endif

namespace aab	{
namespace test	{




}		//	test
}		//	aab
#endif	//	AAB_TEST_DEBUG_ASSERTIONS_CLASS




