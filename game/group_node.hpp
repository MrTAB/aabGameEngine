
/**
*
*	group_node.hpp
*
*   A group node can collect several SceneNodes together at the one position in
*   the scene graph. This prevents lots of empty children pointers from being
*   made.
*
*	SceneNodes are updated in First In order.
*
**/

#if !defined(AAB_GAME_GROUP_NODE_CLASS)
#define AAB_GAME_GROUP_NODE_CLASS
#include"scene_node.hpp"
namespace aab	{
namespace game	{


class GroupNode : public SceneNode
{

	private:

		SceneNodePtrList group;

	public:

		explicit GroupNode ();
		virtual ~GroupNode ();// throw ();



		virtual void before ();
		virtual void after ();

		const SceneNodePtrList& accessGroup () const;
		void addToGroup (SceneNode*);
		SceneNode * removeFromGroup (SceneNode*);
		void clearGroupList ();
};



}		//	game
}		//	aab
#endif	//	AAB_GAME_GROUP_NODE_CLASS




