
/**
*
*	matrix_node.hpp
*
*
**/

#if !defined(AAB_GAME_MATRIX_NODE_CLASS)
#define AAB_GAME_MATRIX_NODE_CLASS
#include"scene_node.hpp"
#include"../visen/matrix_transformer.hpp"
namespace aab	{
namespace game	{



class MatrixNode : public SceneNode, public aab::visen::MatrixTransformer
{
	public:

		explicit MatrixNode ();
		virtual ~MatrixNode ();// throw ();


		virtual void before ();
		virtual void after ();
};



}		//	game
}		//	aab
#endif	//	AAB_GAME_MATRIX_NODE_CLASS




