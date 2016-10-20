
/**
*
*	pose_node.cpp"
*
**/

#include"pose_node.hpp"
namespace aab	{
namespace game	{

/*
*	todo: update to use a single matrix and perform operations on the CPU.
*/



PoseNode::PoseNode ()
{
	// nothing to do here //
}

PoseNode::~PoseNode ()// throw ()
{
	// nothing to do here //
}

void PoseNode::before ()
{
	push ();
}

void PoseNode::after ()
{
	pop ();
}


}		//	game
}		//	aab






