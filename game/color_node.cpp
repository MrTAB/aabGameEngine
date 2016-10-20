
/**
*
*	color_node.cpp"
*
**/

#include"color_node.hpp"
//#include"gl/gl.h"
//#include"gl/glu.h"
//#include"gl/glext.h"
namespace aab	{
namespace game	{


ColorNode::ColorNode ()
{
	// nothing to do here //
}

ColorNode::ColorNode (const Color & color):
	color (color)
{
	// nothing to do here //
}


ColorNode::~ColorNode () //throw ()
{
	// nothing to do here //
}


ColorNode::Color ColorNode::getColor () const
{
	return color;
}

void ColorNode::setColor (const Color color)
{
	this-> color = color;
}

ColorNode::Color & ColorNode::accessColor ()
{
	return color;
}


void ColorNode::before ()
{
	previousColor.setFromAppliedColor ();
	color.apply ();
}

void ColorNode::after ()
{
	previousColor.apply ();
}


}		//	game
}		//	aab






