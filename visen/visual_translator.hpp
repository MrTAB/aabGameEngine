/**
*
*	visual_translater.hpp
*
*   commit:
*   Sets the transformation defined by the current modelviewmatrix to translate
*   (move) by x and y.
*
*   Use push and pop, or a PushPopper to apply that translation (push) and then
*   remove it (after the pop).
*
**/

#if !defined(AAB_VISEN_VISUAL_TRANSLATER_CLASS)
#define AAB_VISEN_VISUAL_TRANSLATER_CLASS
#include"../types/push_pop.hpp"
namespace aab	{
namespace visen	{


class VisualTranslater : public aab::types::PushPop
{
	private:

		float x;
		float y;

	public:

	explicit VisualTranslater ();
	virtual ~VisualTranslater ();// throw ();

	//implicit VisualTranslater (const VisualTranslater&);//

	void move (float x, float y);

	void setPosition(float x, float y);
	void setX (float);
	void setY (float);

	float getX () const;
	float getY () const;


	void push ();
	void pop ();
	void commit ();
};
typedef VisualTranslater VisualTranslator; // typedef to correct spelling for now.



}		//	visen
}		//	aab
#endif //AAB_VISEN_VISUAL_TRANSLATER_CLASS
