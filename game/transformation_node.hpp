
/**
*
*	transformation_node.hpp
*
*   A transformation node will provide the given transformation to the modelview
*   matrix, which will then apply to its children in the scene graph.
**/

#if !defined(AAB_GAME_TRANSFORMATION_NODE_CLASS)
#define AAB_GAME_TRANSFORMATION_NODE_CLASS
#include"scene_node.hpp"
#include"../types/smart_ptr.hpp"
#include"../visen/visual_transformer.hpp"
namespace aab	{
namespace game	{



class TransformationNode : public SceneNode, public aab::visen::VisualTransformer
{

	public:


		explicit TransformationNode ();
		virtual ~TransformationNode ();// throw ();


		virtual void before ();
		virtual void after ();
};



}		//	game
}		//	aab
#endif	//	AAB_GAME_TRANSFORMATION_NODE_CLASS




