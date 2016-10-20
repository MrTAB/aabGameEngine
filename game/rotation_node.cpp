
/**
*
*	rotation_node.cpp"
*
**/

#include"rotation_node.hpp"
namespace aab	{
namespace game	{


RotationNode::RotationNode ()
{
	// nothing //
}

RotationNode::~RotationNode ()// throw ()
{
	// nothing //
}


void RotationNode::before ()
{
	push ();
}

void RotationNode::after ()
{
	pop ();
}


}		//	game
}		//	aab






