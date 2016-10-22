
/**
*
*	hat_position.hpp
*
*   HatPosition is used to store and query a joysticks hat based on a singular
*   value
*/

#if !defined(AAB_INPUT_HAT_POSITION_CLASS)
#define AAB_INPUT_HAT_POSITION_CLASS
#include"../types/smart_ptr.hpp"
#include"hat_value.hpp"
namespace aab	{
namespace input	{

class HatPosition
{
	private:

		int value;

	public:

	//typedef aab::Smart<HatPosition>::Ptr Ptr;

	explicit HatPosition ();

	/*implicit*/
    HatPosition (int value):
        value (value)
    {
        // nothing //
    }

	/*implicit copy construction and assingment in use*/

	static const int centered;
	static const int up;
	static const int right;
	static const int down;
	static const int left;
	static const int rightup;
	static const int rightdown;
	static const int leftup;
	static const int leftdown;

	//upright means the same as rightup etc:
	static const int upright;
	static const int downright;
	static const int upleft;
	static const int downleft;

	operator int& () { return value; }
	operator int () const { return value; }
	
	int getX()const;
	
	int getY()const;
	
	HatValue as_hat_value()const;
};



}		//	input
}		//	aab
#endif	//	AAB_INPUT_HAT_POSITION_CLASS




