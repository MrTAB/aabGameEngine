/**
*
*	visual_scaler.hpp
*
*   commit:
*   Sets the transformation defined by the current modelviewmatrix to scale
*   by the scalers fields.
*
*   Use push and pop, or a PushPopper to apply that scaling (push) and then
*   remove it (after the pop).
**/

#if !defined(AAB_VISEN_VISUAL_SCALER_CLASS)
#define AAB_VISEN_VISUAL_SCALER_CLASS
#include"../types/push_pop.hpp"
namespace aab	{
namespace visen	{


class VisualScaler : public aab::types::PushPop
{
	private:

		float scaleX;
		float scaleY;

	public:

	explicit VisualScaler ();
	virtual ~VisualScaler ();// throw ();

	//implicit VisualScaler (const VisualScaler&);//

	void scale (float x, float y);

	void setScale (float x, float y);

	float getScaleX () const;
	float getScaleY () const;

	void push ();
	void pop ();
	void commit ();
};




}		//	visen
}		//	aab
#endif //AAB_VISEN_VISUAL_SCALER_CLASS
