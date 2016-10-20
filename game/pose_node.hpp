
/**
*
*	pose_node.hpp
*
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




