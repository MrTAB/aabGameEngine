
/**
*
*	display_list_node.cpp"
*
**/

#include"display_list_node.hpp"
#include"../visen/display_absorber.hpp"
namespace aab	{
namespace game	{
using aab::visen::DisplayAbsorber;
using aab::visen::makeDisplayList;


DisplayListNode::DisplayListNode () : // std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
	list (makeDisplayList ())
{
	// nothing to do here //
}

DisplayListNode::~DisplayListNode () //throw ()
{
	// nothing to do here //
}

void DisplayListNode::before ()
{
	list-> render ();
}

void DisplayListNode::after ()
{
	// nothing to do here //
}


void DisplayListNode::setDisplayList (DisplayList list)
{
	this-> list = list;
}

void DisplayListNode::setDisplayListAs (SceneNode * node)// std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
{
	DisplayAbsorber absorber (list);

	node-> update ();
}

DisplayListNode::DisplayList DisplayListNode::getDisplayList ()
{
	return list;
}



}		//	game
}		//	aab






