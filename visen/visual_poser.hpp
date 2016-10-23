/**
*
*	visual_poser.hpp
*
*   commit:
*   Sets the transformation defined by the current modelviewmatrix to translate
*   (move) by x,y,z and also to rotate. No scaling is performed.
*
*   Use push and pop, or a PushPopper to apply that posing (push) and then
*   remove it (after the pop).
*
*	Defaults to a 2D rotational axis (0, 0, 1)
**/

#if !defined(AAB_VISEN_VISUAL_POSER_CLASS)
#define AAB_VISEN_VISUAL_POSER_CLASS
#include"../types/push_pop.hpp"
namespace aab	{
namespace visen	{


class VisualPoser : public aab::types::PushPop
{
	private:

		float x;
		float y;
		float z;
		float angle;
		float rx, ry, rz;

	public:

	explicit VisualPoser ();
	virtual ~VisualPoser ();// throw ();

	//implicit VisualPoser (const VisualPoser&);//

	void move (float x, float y);
	void move (float x, float y, float z);
	void rotate (float angle);

	void setPosition (float x, float y);
	void setPosition (float x, float y, float z);
	void setAngle (float angle);
	void setX (float);
	void setY (float);
	void setZ (float);
	void setRotationAxis (float rx, float ry, float rz);
	void set2DRotationAxis() { setRotationAxis(0, 0, 1); }

	float getX () const;
	float getY () const;
	float getZ () const;
	float getAngle () const;

	void push ();
	void pop ();
	void commit ();
};




}		//	visen
}		//	aab
#endif //AAB_VISEN_VISUAL_TRANSFORMER_CLASS
