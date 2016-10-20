
/*
*
*	mouse_data.hpp
*
*/

#if !defined(AAB_INPUT_MOUSE_DATA_CLASS)
#define AAB_INPUT_MOUSE_DATA_CLASS
#include"../types/smart_ptr.hpp"
#include"../types/manager.hpp"
namespace aab	{
namespace input	{

class MouseDataClass : public aab::types::Manager <MouseDataClass>
{
	public:

	typedef aab::types::Smart <MouseDataClass>::Ptr Ptr;

	protected:

		int x, y, xrel, yrel;
		unsigned char buttonMask;

		friend class aab::types::Manager <MouseDataClass>::Deleter;
		friend Ptr makeMouseData (int x=0, int y=0, int xrel=0, int yrel=0, unsigned char buttonMask=0);
		explicit MouseDataClass (int x=0, int y=0, int xrel=0, int yrel=0, unsigned char buttonMask=0);
		virtual ~MouseDataClass () throw ();

	public:


	int getX () const;
	int getY () const;
	int getXChange () const;
	int getYChange () const;
	bool isButtonDown (int button) const;
};

typedef MouseDataClass::Ptr MouseData;

MouseData makeMouseData (int x, int y, int xrel, int yrel, unsigned char buttonMask);


}		//	input
}		//	aab
#endif	//	AAB_INPUT_MOUSE_DATA_CLASS




