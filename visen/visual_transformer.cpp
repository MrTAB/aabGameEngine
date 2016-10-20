/**
*
*	visual_transformer.cpp
*
*
*   todo: should a VisualTransformer allow changing the texture matrix instead of the model view matrix? May allow some interesting changes to textures from that perspective.
*
*   todo: applications will have model view matrix alot of the time by default: is the call to set it really needed?
*
*   todo - gl matrix methods are depricated in new releases: modify to use own matrix manipulation
**/

#include"visual_transformer.hpp"
#include"_include_opengl.hpp"
namespace aab	{
namespace visen	{


VisualTransformer::VisualTransformer ():
	x (0),
	y (0),
	z (0),
	scaleX (1),
	scaleY (1),
	angle (0),
	scaled(false),
	rotated(false)
	//matrixMode(GL_MODELVIEW)
{
	// nothing //
}


VisualTransformer::~VisualTransformer ()// throw ()
{
	// nothing //
}

void VisualTransformer::move (float x, float y)
{
	this-> x += x;
	this-> y += y;
}

void VisualTransformer::move (float x, float y, float z)
{
	this-> x += x;
	this-> y += y;
	this-> z += z;
}


void VisualTransformer::scale (float x, float y)
{
	this-> scaleX *= x;
	this-> scaleY *= y;
	scaled = true;
}

void VisualTransformer::rotate (float angle)
{
	this-> angle += angle;
	rotated = true;
}

void VisualTransformer::setPosition (float x, float y)
{
	this-> x = x;
	this-> y = y;
}

void VisualTransformer::setPosition (float x, float y, float z)
{
	this-> x = x;
	this-> y = y;
	this-> z = z;
}


void VisualTransformer::setScale (float x, float y)
{
	this-> scaleX = x;
	this-> scaleY = y;
	scaled = true;
}


void VisualTransformer::setAngle (float angle)
{
	this-> angle = angle;
	rotated = true;
}

void VisualTransformer::setX (float x)
{
	this-> x = x;
}

void VisualTransformer::setY (float y)
{
	this-> y = y;
}

void VisualTransformer::setZ (float z)
{
	this-> z = z;
}

void VisualTransformer::resetScale()
{
	this-> scaleX = this-> scaleY = 1.0;
	scaled = false;
}

void VisualTransformer::resetAngle()
{
	this-> angle = 0;
	rotated = false;
}
	
float VisualTransformer::getX () const
{
	return x;
}

float VisualTransformer::getY () const
{
	return y;
}

float VisualTransformer::getZ () const
{
	return z;
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

void VisualTransformer::push ()
{
	//glMatrixMode (matrixMode);
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	glTranslatef (x, y, z);
	if(scaled)
	{
        glScalef (scaleX, scaleY, 1.0);
	}
	if(rotated)
	{
        glRotatef (angle, 0, 0, 1);
	}
}

void VisualTransformer::pop ()
{
	//glMatrixMode (matrixMode);
	glMatrixMode (GL_MODELVIEW);
	glPopMatrix ();
}

void VisualTransformer::commit ()
{
	//glMatrixMode (matrixMode);
	glMatrixMode (GL_MODELVIEW);	
	glTranslatef (x, y, z);
	if(scaled)
	{
        glScalef (scaleX, scaleY, 1.0);
	}
	if(rotated)
	{
        glRotatef (angle, 0, 0, 1);
	}
}


/*
void VisualTransformer::useTextureMatrix()
{
    matrixMode = GL_TEXTURE;
}
void VisualTransformer::useModelViewMatrix()
{
    matrixMode = GL_MODELVIEW;
}
void VisualTransformer::useProjectionMatrix()
{
    matrixMode = GL_PROJECTION;
}
*/

}		//	visen
}		//	aab

