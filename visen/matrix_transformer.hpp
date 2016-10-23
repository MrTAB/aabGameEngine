/**
*
*	matrix_transformer.hpp
*
*   Transforms the modelview matrix based on the internally stored matrix.
*
*	In the future, functionality in visual_transformer will be implemented with
*	matrices, and this and it will be combined into one class. The name will then
*	be referring to the same class. This is due to changes in support within OpenGL
*
**/

#if !defined(AAB_VISEN_MATRIX_TRANSFORMER_CLASS)
#define AAB_VISEN_MATRIX_TRANSFORMER_CLASS
#include"../types/push_pop.hpp"
#include"../types/matrix.hpp"
namespace aab	{
namespace visen	{

typedef types::Matrix Matrix;

class MatrixTransformer : public aab::types::PushPop
{
	protected:

		Matrix matrix;

	public:

	explicit MatrixTransformer ();
	virtual ~MatrixTransformer ();// throw ();

	//implicit MatrixTransformer (const MatrixTransformer&);//

	void setMatrix (const Matrix&); // must be no less than 16 elements

	//void move (float x, float y);
	//void move (float x, float y, float z);
	//void scale (float x, float y);
	//void rotate (float angle);

	//void setPosition (float x, float y);
	//void setPosition (float x, float y, float z);
	//void setScale (float x, float y);
	//void setAngle (float angle);
	//void setX (float);
	//void setY (float);
	//void setZ (float);

	//float getX () const;
	//float getY () const;
	//float getZ () const;
	//float getScaleX () const;
	//float getScaleY () const;
	//float getAngle () const;

	void push ();
	void pop ();
	void commit ();
	
	
	static void pushIdentity();
	static void loadIdentity();
	static void pushMatrix();
	static void popMatrix();
};


}		//	visen
}		//	aab
#endif //AAB_VISEN_MATRIX_TRANSFORMER_CLASS
