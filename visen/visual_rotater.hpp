/**
*
*	visual_rotater.hpp
*
*   commit:
*   Sets the transformation defined by the current modelviewmatrix to rotate
*   by the stored angle.
*
*   Use push and pop, or a PushPopper to apply that rotation (push) and then
*   remove it (after the pop).
**/

#if !defined(AAB_VISEN_VISUAL_ROTATER_CLASS)
#define AAB_VISEN_VISUAL_ROTATER_CLASS
#include"../types/push_pop.hpp"
namespace aab	{
namespace visen	{


class VisualRotater : public aab::types::PushPop
{
	private:

		float angle; // angle in degrees

	public:

	explicit VisualRotater ();
	virtual ~VisualRotater ();// throw ();

	//implicit VisualRotater (const VisualRotater&);//

	void rotate (float angle);

	void setAngle (float angle);

	float getAngle () const;

	void push ();
	void pop ();
	void commit ();
};




}		//	visen
}		//	aab
#endif //AAB_VISEN_VISUAL_ROTATER_CLASS
