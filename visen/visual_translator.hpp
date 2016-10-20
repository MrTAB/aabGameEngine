/**
*
*	visual_translater.hpp
*
*	should provide methods to commit to current state.
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
