/**
*
*	visual_rotater.hpp
*
**/

#if !defined(AAB_VISEN_VISUAL_ROTATER_CLASS)
#define AAB_VISEN_VISUAL_ROTATER_CLASS
#include"../types/push_pop.hpp"
namespace aab	{
namespace visen	{


class VisualRotater : public aab::types::PushPop
{
	private:

		float angle;

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
