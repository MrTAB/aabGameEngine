/**
*
*	visual_poser.cpp
*
*   todo - gl matrix methods are depricated in new releases: modify to use own matrix manipulation
**/

#include"visual_poser.hpp"
#include"_include_opengl.hpp"
namespace aab	{
namespace visen	{


VisualPoser::VisualPoser ():
	x (0),
	y (0),
	z (0),
	angle (0),
	rx (0),
	ry (0),
	rz (1)
{
	// nothing to do here //
}


VisualPoser::~VisualPoser () //throw ()
{
	// nothing to do here //
}

void VisualPoser::move (float x, float y)
{
	this-> x += x;
	this-> y += y;
}

void VisualPoser::move (float x, float y, float z)
{
	this-> x += x;
	this-> y += y;
	this-> z += z;
}


void VisualPoser::rotate (float angle)
{
	this-> angle += angle;
}

void VisualPoser::setPosition (float x, float y)
{
	this-> x = x;
	this-> y = y;
}

void VisualPoser::setPosition (float x, float y, float z)
{
	this-> x = x;
	this-> y = y;
	this-> z = z;
}


void VisualPoser::setAngle (float angle)
{
	this-> angle = angle;
}

void VisualPoser::setX (float x)
{
	this-> x = x;
}

void VisualPoser::setY (float y)
{
	this-> y = y;
}

void VisualPoser::setZ (float z)
{
	this-> z = z;
}

void VisualPoser::setRotationAxis (float rx, float ry, float rz)
{
	this-> rx = rx;
	this-> ry = ry;
	this-> rz = rz;
}

float VisualPoser::getX () const
{
	return x;
}

float VisualPoser::getY () const
{
	return y;
}

float VisualPoser::getZ () const
{
	return z;
}

float VisualPoser::getAngle () const
{
	return angle;
}

void VisualPoser::push ()
{
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	glTranslatef (x, y, z);
	glRotatef (angle, rx, ry, rz);
}

void VisualPoser::pop ()
{
	glMatrixMode (GL_MODELVIEW);
	glPopMatrix ();
}

void VisualPoser::commit ()
{
	glMatrixMode (GL_MODELVIEW);
	glTranslatef (x, y, z);
	glRotatef (angle, rx, ry, rz);
}

}		//	visen
}		//	aab

