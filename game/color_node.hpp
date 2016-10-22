
/**
*
*	color_node.hpp
*
*   Color Nodes change the rendering color for their children node in the scene
*   graph hierarchy. Like other nodes they extend SceneNode and implement
*   before() and after(). Use setColor to define the render color that they
*   activate.
**/

#if !defined(AAB_GAME_COLOR_NODE_CLASS)
#define AAB_GAME_COLOR_NODE_CLASS
#include"scene_node.hpp"
#include"../visen/color.hpp"
namespace aab	{
namespace game	{



class ColorNode : public SceneNode
{
	private:

		typedef aab::visen::Colorf Color;

		Color color;
		Color previousColor;

	public:


		explicit ColorNode ();
		explicit ColorNode (const Color&);
		virtual ~ColorNode () ;//throw ();

	public:


	Color getColor () const;
	void setColor (const Color);
	Color & accessColor ();

	virtual void before ();
	virtual void after ();
};



}		//	game
}		//	aab
#endif	//	AAB_GAME_COLOR_NODE_CLASS




