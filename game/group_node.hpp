
/**
*
*	group_node.hpp
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




