
/**
*
*	scene_node.hpp
*
*
**/

#if !defined(AAB_GAME_SCENE_NODE_CLASS)
#define AAB_GAME_SCENE_NODE_CLASS
#include"../types/manager.hpp"
#include"../types/smart_ptr.hpp"
#include<list>
//#include<exception>
namespace aab	{
namespace game	{

class SceneNode;
typedef std::list <SceneNode*> SceneNodePtrList;

class SceneNode
{
	private:

		SceneNodePtrList children;

		SceneNode (const SceneNode &);

	public:

		explicit SceneNode ();

		virtual ~SceneNode ();// throw ();

		virtual void before ();
		virtual void after ();

		void update ();

		const SceneNodePtrList& accessChildren () const;

		void addChild (SceneNode*);
		SceneNode * removeChild (SceneNode*);
		void clearChildren ();
		SceneNode * removeAnyChild ();

		void updateChildren ();
};

SceneNode * makeSceneNode ();



}		//	game
}		//	aab
#endif	//	AAB_GAME_SCENE_NODE_CLASS




