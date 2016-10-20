
/**
*
*	viewport.cpp"
*
**/

#include"viewport.hpp"
/*#include"gl/gl.h"
#include"gl/glu.h"
#include"gl/glext.h"*/
#include"../visen/_include_opengl.hpp"
#include<exception>
#include<stdexcept>
namespace aab	{
namespace game	{



Viewport::Viewport(visen::Screen screen) ://throw (std::exception &) :
	usingBounds (false), screen (screen), rx(0), ry(0), rz(1.0)
{
	float half_width = screen-> getScaledWidth() / 2;
	float half_height = screen-> getScaledHeight() / 2;
	leftBound = -half_width;
	rightBound = half_width;
	topBound = -half_height;
	bottomBound = half_height;
}

Viewport::~Viewport()// throw ()
{
	// nothing to do here //
}

int Viewport::getContextWidth()const
{
    return screen->getContextWidth();
}
int Viewport::getContextHeight()const
{
    return screen->getContextHeight();
}

int Viewport::getViewWidth()const
{
    return screen->getScaledWidth();
}
int Viewport::getViewHeight()const
{
    return screen->getScaledHeight();
}

int Viewport:: getWidth()const
{
	return getScaleX() * screen->getScaledWidth();
}

int Viewport:: getHeight()const
{
	return getScaleY() * screen->getScaledHeight();
}


int Viewport:: getLeft()const
{
	return getX() - getWidth()/2;
}

int Viewport:: getTop()const
{
	return getY() - getHeight()/2;
}

int Viewport:: getRight()const
{
	return getX() + getWidth()/2;
}

int Viewport:: getBottom()const
{
	return getY() + getHeight()/2;
}

		
void Viewport::checkBounds ()
{
	if (usingBounds)
	{
		const float hw = screen-> getScaledWidth()/2.0;
		const float hh = screen-> getScaledHeight()/2.0;
		float sx = getScaleX(), sy = getScaleY();

		if (rightBound - leftBound <= sx*hw*2)
		{
			if (bottomBound - topBound <= sy*hh*2)
			{
				float vsx = (rightBound - leftBound)/(hw*2);
				float vsy = (bottomBound - topBound)/(hh*2);

				sx = sy = (vsx < vsy ? vsx : vsy);
				setScale (sx, sy);
			}
			else
			{
				sx = sy = (rightBound - leftBound)/(hw*2);
				setScale (sx, sy);
			}
		}
		else if (bottomBound - topBound <= sy*hh*2)
		{
			sx = sy = (bottomBound - topBound)/(hh*2);
			setScale (sx, sy);
		}

		if (getX() < leftBound + sx*hw)
		{
			setX(leftBound + sx*hw);
		}
		else if (getX() > rightBound - sx*hw)
		{
			setX(rightBound - sx*hw);
		}

		if (getY() < topBound + sy*hh)
		{
			setY(topBound + sy*hh);
		}
		else if (getY() > bottomBound - sy*hh)
		{
			setY(bottomBound - sy*hh);
		}
	}
}

void Viewport::setBounds(float leftBoundIn, float topBoundIn, float rightBoundIn, float bottomBoundIn) //std::invalid_argument
{
	usingBounds = true;

    #ifdef _DEBUG
	if (leftBoundIn >= rightBoundIn)
		throw std::invalid_argument ("game::ViewportClass::setBounds(): leftBound must be left of rightBound.");

	if (topBoundIn >= bottomBoundIn)
		throw std::invalid_argument ("game::ViewportClass::setBounds(): topBound must be above bottomBound.");
		
    #else
        if (leftBoundIn > rightBoundIn)
            std::swap(leftBoundIn,rightBoundIn);
            
        if (topBoundIn > bottomBoundIn)
            std::swap(topBoundIn,bottomBoundIn);
            
        if (leftBoundIn == rightBoundIn)
            rightBoundIn += 640;
            
        if (topBoundIn == bottomBoundIn)
            bottomBoundIn += 480;
            
    #endif
    
    
	leftBound = leftBoundIn;
	topBound = topBoundIn;
	rightBound = rightBoundIn;
	bottomBound = bottomBoundIn;
}

void Viewport::clearBounds()
{
	usingBounds = false;
}


void Viewport::push()
{
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	commit();
	/*
	glLoadIdentity();
	//gluLookAt(0,0,0,0,0,-1,0,1,0);
	checkBounds();
	glTranslatef (screen->getWidth()/2,screen->getHeight()/2,0);
	glScalef (screen->getScaleX()/getScaleX(), screen->getScaleY()/getScaleY(), 1.0);
	//glScalef (1.0/getScaleX(), 1.0/getScaleY(), 1.0);
	glRotatef (- getAngle(), 0,0,1);
	glTranslatef ( - getX(), - getY(), 0);
	*/
}

void Viewport::pop()
{
	glMatrixMode (GL_MODELVIEW);
	glPopMatrix ();
}

void Viewport::commit ()
{
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(0,0,0,0,0,-1,0,1,0);
	checkBounds();
	glTranslatef (screen-> getScaledWidth()/2,screen-> getScaledHeight()/2,0);
	glScalef (1.0/getScaleX(), 1.0/getScaleY(), 1.0);
	//glScalef (screen->getScaleX()/getScaleX(), screen->getScaleY()/getScaleY(), screen->getScaleX());
	glRotatef (- getAngle(), 0,0,1);
	glTranslatef ( - getX(), - getY(), 0);
}

void Viewport::setRotationAxis(float rxi, float ryi, float rzi)
{
	rx = rxi;
	ry = ryi;
	rz = rzi;
}


}		//	game
}		//	aab






