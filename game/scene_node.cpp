
/**
*
*	scene_node.cpp"
*
**/

#include"scene_node.hpp"
//#include<stdexcept>
#include<algorithm>
namespace aab	{
namespace game	{


static void updateChild (SceneNode*);


SceneNode * makeSceneNode ()
{
	//SceneNode px (new SceneNode(), SceneNode::Deleter());
	return new SceneNode();
}


SceneNode::SceneNode ()
{
	// nothing to do here //
}

SceneNode::~SceneNode () //throw ()
{
	// nothing to do here //
}


void SceneNode::update ()
{
	this-> before ();
	updateChildren ();
	this-> after ();
}

void SceneNode::before ()
{
	// nothing to do here //
}

void SceneNode::after ()
{
	// nothing to do here //
}

const SceneNodePtrList& SceneNode::accessChildren () const
{
	return children;
}

void SceneNode::addChild (SceneNode* node)
{
	//if (node != this)
	{
		children.push_back (node);
	}
}

SceneNode* SceneNode::removeChild (SceneNode* node)
{
	children.remove (node);

	return node;
}

void SceneNode::clearChildren ()
{
	children.clear ();
}

SceneNode* SceneNode::removeAnyChild ()
{
	if (children.empty ())
	{
		//SceneNode* null ((SceneNode*) NULL, NullDeleter ());
		return 0;
	}

	SceneNode* back = children.back ();

	children.pop_back ();

	return back;
}


void SceneNode::updateChildren ()
{
	std::for_each (children.begin(), children.end(), updateChild);
}

void updateChild (SceneNode* node)
{
	node-> update ();
}




}		//	game
}		//	aab






