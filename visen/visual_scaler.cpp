/**
*
*	visual_scaler.cpp
*
*     todo - gl matrix methods are depricated in new releases: modify to use own matrix manipulation
**/

#include"visual_scaler.hpp"
#include"_include_opengl.hpp"
namespace aab	{
namespace visen	{
typedef VisualScaler V;


V::VisualScaler ():
	scaleX (1),
	scaleY (1)
{
	// nothing //
}

V::~VisualScaler ()// throw ()
{
	// nothing //
}


void V::scale (float x, float y)
{
	this-> scaleX *= x;
	this-> scaleY *= y;
}

void V::setScale (float x, float y)
{
	this-> scaleX = x;
	this-> scaleY = y;
}

float V::getScaleX () const
{
	return scaleX;
}

float V::getScaleY () const
{
	return scaleY;
}


void V::push ()
{
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	glScalef (scaleX, scaleY, 1.0);
}

void V::pop ()
{
	glMatrixMode (GL_MODELVIEW);
	glPopMatrix ();
}

void V::commit ()
{
	glMatrixMode (GL_MODELVIEW);
	glScalef (scaleX, scaleY, 1.0);
}



}		//	visen
}		//	aab

