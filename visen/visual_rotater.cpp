/**
*
*	visual_rotater.hpp
*
*     todo - gl matrix methods are depricated in new releases: modify to use own matrix manipulation
**/

#include"visual_rotater.hpp"
#include"_include_opengl.hpp"
namespace aab	{
namespace visen	{
typedef VisualRotater VR;


VR::VisualRotater ():
	angle (0)
{
	// nothing //
}


VR::~VisualRotater ()// throw ()
{
	// nothing //
}

void VR::rotate (float angle)
{
	this-> angle += angle;
}


void VR::setAngle (float angle)
{
	this-> angle = angle;
}


float VR::getAngle () const
{
	return angle;
}

void VR::push ()
{
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	glRotatef (angle, 0, 0, 1);
}

void VR::pop ()
{
	glMatrixMode (GL_MODELVIEW);
	glPopMatrix ();
}

void VR::commit ()
{
	glMatrixMode (GL_MODELVIEW);
	glRotatef (angle, 0, 0, 1);
}


}		//	visen
}		//	aab
