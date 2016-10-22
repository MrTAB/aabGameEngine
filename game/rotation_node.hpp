
/**
*
*	rotation_node.hpp
*
*   A rotation node rotates the modelview matrix for its children in the scene
*   graph.
**/

#if !defined(AAB_GAME_ROTATION_NODE_CLASS)
#define AAB_GAME_ROTATION_NODE_CLASS
#include"scene_node.hpp"
#include"../visen/visual_rotater.hpp"
//#include"../types/smart_ptr.hpp"
namespace aab	{
namespace game	{



class RotationNode : public SceneNode, public aab::visen::VisualRotater
{

	public:

		explicit RotationNode ();
		virtual ~RotationNode ();//throw ();



		virtual void before ();
		virtual void after ();
};



}		//	game
}		//	aab
#endif	//	AAB_GAME_ROTATION_NODE_CLASS




