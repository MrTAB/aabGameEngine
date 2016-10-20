
/**
* @file
* @author mentrox@gmail.com
* @version 1.0
* @date
*
* @section DESCRIPTION
*
* A Sprite is an object referring to a 2d image that can be translated, rotated,
* scaled, rendered and animated; this makes it ideal for displaying dynamic game
* objects such as players and enemies.
* Currently, Sprites load images with frame sizes that are a power of two - smallest 64x64.
*
**/


// todos:
//flip method, resizing to exact size methods,
// get width/height, including scales/rotations etc
// methods for loading sprite that create timer for you automatically.
// subanimator selection


#if !defined(AAB_GAME_SPRITE_CLASS)
#define AAB_GAME_SPRITE_CLASS
#include"prototype/sprite.hh"
#include"transformation_node.hpp"
#include"../types/smart_ptr.hpp"
#include"../visen/texture_base.hpp"
#include"../visen/texture.hpp"
#include"../visen/animated_texture.hpp"
#include"../visen/Color.hpp"
//#include"../time/sub_animator.hpp"
//#include<exception>
//#include<vector>
namespace aab	{
namespace game	{


class Sprite : public TransformationNode
{
	public:

	typedef aab::visen::TextureBasePtr TextureBasePtr;
	typedef aab::visen::TexturePtr TexturePtr;
	typedef aab::visen::AnimatedTexturePtr AnimatedTexturePtr;
	typedef aab::visen::Colorub Colorub;
	//typedef aab::time::FrameTicker FrameTicker;

	private:

		TextureBasePtr texture;
		//std::vector<time::SubAnimator> subAnimators;
		//int currentSubAnimator;
		//int frames;
		bool updateFrameSize; //update size if frame size changes
		Colorub color;
		bool useColor;
		
	public:

        
        
		explicit Sprite (TextureBasePtr);
		explicit Sprite (TexturePtr,// FrameTicker::Ptr,
                   int frameWidth, int frameHeight);//std::invalid_argument
		virtual ~Sprite();// throw ();


		// draw includes transformation etc. Render is just a direct output.

		void draw ();
		void render ();

		virtual void before ();
		virtual void after ();

		TextureBasePtr getTextureBase ();
		//time::FrameTicker::Ptr getFrameTickerPtr ();


		/**
		* returns the FrameTicker which animates the Sprite.
		*
		* The FrameTicker is used by the Sprite to choose which frame of animation
		* to render on calls to draw() and before(). This must be updated, either
		* through invoking FrameTicker::update() or by calling
		* Sprite::updateAnimation().
		*
		* @return Handle to frame ticker used by this Sprite.
		*/

		//inline time::FrameTicker::Ptr getAnimator () { return getFrameTickerPtr(); }

		//void updateAnimation ();

		//int getCurrentSubAnimatorIndex () const;
		//void setSubAnimator(int index);// throw (std::exception&); // will only set if its not current
		//void addSubAnimator(const time::SubAnimator);// throw (std::exception&);
		//std::vector<time::SubAnimator> & accessSubAnimators ();

		visen::BlendMethod & accessBlendMethod () { return texture->accessBlendMethod(); }
		
		void setFrame(int frame);
		int getFrame()const;
		int getMaximumFrame()const;
		bool isAnimatable()const;
		
		Colorub getColor()const { return color; }
		void setColor(Colorub colorIn) { color = colorIn; useColor = true; }
		void removeColor() { useColor = false; }
		bool isUsingColor() const { return useColor; }
		
		void setAlpha(const char alpha) {   color.setAlpha(alpha); useColor = true; }
};


}		//	game
}		//	aab
#endif	//	AAB_GAME_SPRITE_CLASS




