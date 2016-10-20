/**
*
*	matrix_transformer.cpp
*
**/

#include"matrix_transformer.hpp"
#include"_include_opengl.hpp"
namespace aab	{
namespace visen	{


MatrixTransformer::MatrixTransformer ()
{
	matrix.setAsIdentity ();
}


MatrixTransformer::~MatrixTransformer ()// throw ()
{
	// nothing to do here //
}


void MatrixTransformer::setMatrix (const Matrix& matrix_in)
{
	std::copy(matrix_in.e, matrix_in.e + 16, matrix.e);
}

/*
void VisualTransformer::move (float x, float y)
{
	this-> x += x;
	this-> y += y;
}

void VisualTransformer::scale (float x, float y)
{
	this-> scaleX *= x;
	this-> scaleY *= y;
}

void VisualTransformer::rotate (float angle)
{
	this-> angle += angle;
}

void VisualTransformer::setPosition (float x, float y)
{
	this-> x = x;
	this-> y = y;
}

void VisualTransformer::setScale (float x, float y)
{
	this-> scaleX = x;
	this-> scaleY = y;
}


void VisualTransformer::setAngle (float angle)
{
	this-> angle = angle;
}

void VisualTransformer::setX (float x)
{
	this-> x = x;
}

void VisualTransformer::setY (float y)
{
	this-> y = y;
}

float VisualTransformer::getX () const
{
	return x;
}

float VisualTransformer::getY () const
{
	return y;
}

float VisualTransformer::getScaleX () const
{
	return scaleX;
}

float VisualTransformer::getScaleY () const
{
	return scaleY;
}

float VisualTransformer::getAngle () const
{
	return angle;
}
*/

void MatrixTransformer::push ()
{
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	glMultMatrixf (matrix.e);
}

void MatrixTransformer::pop ()
{
	glMatrixMode (GL_MODELVIEW);
	glPopMatrix ();
}

void MatrixTransformer::commit ()
{
	glMatrixMode (GL_MODELVIEW);
	glMultMatrixf (matrix.e);
}

void MatrixTransformer::pushIdentity()
{
    glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	glLoadIdentity();
}
void MatrixTransformer::loadIdentity()
{
    glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
void MatrixTransformer::pushMatrix()
{
    glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
}
void MatrixTransformer::popMatrix()
{
    glMatrixMode (GL_MODELVIEW);
	glPopMatrix ();
}

}		//	visen
}		//	aab

