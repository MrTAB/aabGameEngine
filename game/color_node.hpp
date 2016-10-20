
/**
*
*	color_node.hpp
*
*
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




