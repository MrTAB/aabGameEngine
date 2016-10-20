
/**
*
*	scale_node.hpp
*
*
**/

#if !defined(AAB_GAME_SCALE_NODE_CLASS)
#define AAB_GAME_SCALE_NODE_CLASS
#include"scene_node.hpp"
#include"../visen/visual_scaler.hpp"
//#include"../types/smart_ptr.hpp"
namespace aab	{
namespace game	{



class ScaleNode : public SceneNode, public aab::visen::VisualScaler
{
	public:

		explicit ScaleNode ();
		virtual ~ScaleNode ();// throw ();



		virtual void before ();
		virtual void after ();
};


}		//	game
}		//	aab
#endif	//	AAB_GAME_SCALE_NODE_CLASS




