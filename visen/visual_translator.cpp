/**
*
*	visual_translater.cpp
*
*     todo - gl matrix methods are depricated in new releases: modify to use own matrix manipulation
**/

#include"visual_translator.hpp"
#include"_include_opengl.hpp"
namespace aab	{
namespace visen	{
typedef VisualTranslater VT;

VT::VisualTranslater () :
	x (0),
	y (0)
{
	// nothing //
}

VT::~VisualTranslater ()// throw ()
{
	// nothing //
}




void VT::setPosition (float x, float y)
{
	this-> x = x;
	this-> y = y;
}

void VT::setX (float x)
{
	this-> x = x;
}

void VT::setY (float y)
{
	this-> y = y;
}

float VT::getX () const
{
	return x;
}

float VT::getY () const
{
	return y;
}



void VT::move (float x, float y)
{
	this-> x += x;
	this-> y += y;
}

void VT::push ()
{
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	glTranslatef (x, y, 0);
}

void VT::pop ()
{
	glMatrixMode (GL_MODELVIEW);
	glPopMatrix ();
}

void VT::commit ()
{
	glMatrixMode (GL_MODELVIEW);
	glTranslatef (x, y, 0);
}


}		//	visen
}		//	aab
