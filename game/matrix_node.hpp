
/**
*
*	matrix_node.hpp
*
*   A Matrix Node will apply the matrix defined by the MatrixTransformer
*   subclass directly to the modelview matrix during the scene graph traversal.
*   This matrix change will only apply to its children in the scene graph.
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




