
/**
*
*	moveable_texture_node.hpp
*
*
**/

#if !defined(AAB_GAME_MOVEABLE_TEXTURE_NODE_CLASS)
#define AAB_GAME_MOVEABLE_TEXTURE_NODE_CLASS
#include"translation_node.hpp"
#include"../visen/texture_base.hpp"
//#include"../time/frame_ticker.hpp"
#include"../visen/texture.hpp"
#include<exception>
namespace aab	{
namespace game	{

class MoveableTextureNode : public TranslationNode
{
	public:

	typedef aab::visen::TextureBasePtr TextureBasePtr;
	typedef aab::visen::TexturePtr TexturePtr;
	//typedef aab::time::FrameTicker FrameTicker;

	private:

		TextureBasePtr texture;

	public:

		explicit MoveableTextureNode (TextureBasePtr) ;
		explicit MoveableTextureNode (TexturePtr,// FrameTicker::Ptr,
                                int frameWidth, int frameHeight) ;//std::invalid_argument
		virtual ~MoveableTextureNode ();//throw ();

		virtual void before ();
		virtual void after ();

		// draw includes transformation etc. Render is just a direct output.

		void draw ();
		void render ();

		TextureBasePtr getTextureBase ();

};


}		//	game
}		//	aab
#endif	//	AAB_GAME_MOVEABLE_TEXTURE_NODE_CLASS


