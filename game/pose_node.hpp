
/**
*
*	pose_node.hpp
*
*   A PoseNode provides pose transformations to its children in the scene graph
*   The Pose transformations are accessed via the superclass VisualPoser. Pose
*   transformations allow movement and rotation but no scaling.
*
**/

#if !defined(AAB_GAME_POSE_NODE_CLASS)
#define AAB_GAME_POSE_NODE_CLASS
#include"scene_node.hpp"
#include"../visen/visual_poser.hpp"
namespace aab	{
namespace game	{



class PoseNode : public SceneNode, public aab::visen::VisualPoser
{
	public:

		explicit PoseNode ();
		virtual ~PoseNode ();//throw ();

		virtual void before ();
		virtual void after ();
};



}		//	game
}		//	aab
#endif	//	AAB_GAME_TRANSFORMATION_NODE_CLASS




