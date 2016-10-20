
/**
*
*	translation_node.cpp"
*
**/

#include"translation_node.hpp"
namespace aab	{
namespace game	{



TranslationNode::TranslationNode ()
{
	// nothing to do here //
}

TranslationNode::~TranslationNode () //throw ()
{
	// nothing to do here //
}


void TranslationNode::before ()
{
	push ();
}

void TranslationNode::after ()
{
	pop ();
}


}		//	game
}		//	aab






