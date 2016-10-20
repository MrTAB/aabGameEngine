
/**
*
*	matrix_node.cpp"
*
**/

#include"matrix_node.hpp"
namespace aab	{
namespace game	{

/*
*	todo: combine matrix node and transformation node once transformation node uses matrix!
*/



MatrixNode::MatrixNode ()
{
	// nothing to do here //
}

MatrixNode::~MatrixNode ()// throw ()
{
	// nothing to do here //
}

void MatrixNode::before ()
{
	push ();
}

void MatrixNode::after ()
{
	pop ();
}


}		//	game
}		//	aab






