
/**
*
*	transformation_node.cpp"
*
**/

#include"transformation_node.hpp"
namespace aab	{
namespace game	{

/*
*	later: update to use a single matrix and perform operations on the CPU.
*/

TransformationNode::TransformationNode ()
{
	// nothing to do here //
}

TransformationNode::~TransformationNode ()// throw ()
{
	// nothing to do here //
}

void TransformationNode::before ()
{
	push ();
}

void TransformationNode::after ()
{
	pop ();
}


}		//	game
}		//	aab






