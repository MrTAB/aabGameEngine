
/**
*
*	group_node.cpp"
*
**/

#include"group_node.hpp"
#include<algorithm>
namespace aab	{
namespace game	{



void singleBefore (SceneNode*);
void singleUpdate (SceneNode*);
void singleAfter (SceneNode*);


GroupNode::GroupNode ()
{
	// nothing to do here //
}

GroupNode::~GroupNode () //throw ()
{
	// nothing to do here //
	//Deleter ();
}



void GroupNode::before ()
{
	std::for_each (group.begin(), group.end(), singleBefore);
	std::for_each (group.begin(), group.end(), singleUpdate);
}

void GroupNode::after ()
{
	std::for_each (group.begin(), group.end(), singleAfter);
}



const SceneNodePtrList& GroupNode::accessGroup () const
{
	return group;
}

void GroupNode::addToGroup (SceneNode * node)
{
	if (node != this)
	{
		group.push_back (node);
	}
}



SceneNode * GroupNode::removeFromGroup (SceneNode * node)
{
	group.remove (node);

	return node;
}

void GroupNode::clearGroupList ()
{
	group.clear ();
}



void singleBefore (SceneNode * node)
{
	node-> before ();
}

void singleUpdate (SceneNode * node)
{
	node-> updateChildren ();
}

void singleAfter (SceneNode * node)
{
	node-> after ();
}



}		//	game
}		//	aab






