/**
*
*	visual_transformer.hpp
*
**/

#if !defined(AAB_VISEN_VISUAL_TRANSFORMER_CLASS)
#define AAB_VISEN_VISUAL_TRANSFORMER_CLASS
#include"../types/push_pop.hpp"
namespace aab	{
namespace visen	{


class VisualTransformer : public aab::types::PushPop
{
	private:

		float x;
		float y;
		float z;
		float scaleX;
		float scaleY;
		float angle;
		bool scaled;
		bool rotated;
		
		//unsigned int matrixMode;

	public:

	explicit VisualTransformer ();
	virtual ~VisualTransformer ();// throw ();

	//implicit VisualTransformer (const VisualTransformer&);//

	void move (float x, float y);
	void move (float x, float y, float z);
	void scale (float x, float y);
	void rotate (float angle);

	void setPosition (float x, float y);
	void setPosition (float x, float y, float z);
	void setScale (float x, float y);
	void setAngle (float angle);
	void setX (float);
	void setY (float);
	void setZ (float);
	void resetScale();
	void resetAngle();

	float getX () const;
	float getY () const;
	float getZ () const;
	float getScaleX () const;
	float getScaleY () const;
	float getAngle () const;

	void push ();
	void pop ();
	void commit ();
	
	/*
	void useTextureMatrix();
	void useModelViewMatrix();
	void useProjectionMatrix();
	*/
};




}		//	visen
}		//	aab
#endif //AAB_VISEN_VISUAL_TRANSFORMER_CLASS
