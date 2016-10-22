
/**
*
*	viewport.hpp
*
*	The viewport is like a box in the modelview world. Moving a viewport left,
*	will move everything in the world to the right.
*
*	The game world has a viewport defining the relative motion of everything else.
*	For a HUD, define a new blank viewport, and switch between it and the world
*	viewport by pushing the hud viewport to use it and popping it to return to the world.
*
*	todo - choosing to have some edges defined and others not
*	todo - clipping the viewport edges in for rotated views
**/

#if !defined(AAB_GAME_VIEWPORT_CLASS)
#define AAB_GAME_VIEWPORT_CLASS
#include"prototype/viewport.hh"
#include"transformation_node.hpp"
#include"../visen/screen.hpp"
namespace aab	{
namespace game	{



class Viewport : public TransformationNode
{
	private:

		bool usingBounds;
		float leftBound,topBound,rightBound,bottomBound;
		visen::Screen screen;
		float rx,ry,rz;


	public:

		explicit Viewport (visen::Screen);// throw (std::exception &);
		virtual ~Viewport ();//throw ();

		void checkBounds ();

		void setBounds(float leftBound, float topBound, float rightBound, float bottomBound);// std::invalid_argument
		void clearBounds();

		void push ();
		void pop ();
		void commit ();

		void setRotationAxis(float x=0,float y=0,float z=1);
		
		int getContextWidth()const;
		int getContextHeight()const;
		int getViewWidth()const;
		int getViewHeight()const;
		
		int getWidth()const;
		int getHeight()const;
		
		int getLeft()const;
		int getTop()const;
		int getRight()const;
		int getBottom()const;
};


}		//	game
}		//	aab
#endif	//	AAB_GAME_VIEWPORT_CLASS




