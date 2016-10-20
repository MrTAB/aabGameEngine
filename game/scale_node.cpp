
/**
*
*	scale_node.cpp"
*
**/

#include"scale_node.hpp"
namespace aab	{
namespace game	{



ScaleNode::ScaleNode()
{
	/* nothing */
}

ScaleNode::~ScaleNode () //throw ()
{
	/* nothing */
}


void ScaleNode::before ()
{
	push ();
}

void ScaleNode::after ()
{
	pop ();
}



}		//	game
}		//	aab






