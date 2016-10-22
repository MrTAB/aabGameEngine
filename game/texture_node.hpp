
/**
*
*	texture_node.hpp
*
*   A TextureNode will render a texture as an image during traversal of the
*   scene graph. This will be rendered at local 0,0 and at the sources pixel
*   size, and will be modified by any ancestors in the graph
*
**/

#if !defined(AAB_GAME_TEXTURE_NODE_CLASS)
#define AAB_GAME_TEXTURE_NODE_CLASS
#include"scene_node.hpp"
#include"../types/smart_ptr.hpp"
#include"../visen/texture_base.hpp"
//#include"../time/frame_ticker.hpp"
#include"../visen/texture.hpp"
//#include<exception>
namespace aab	{
namespace game	{

class TextureNode : public SceneNode
{
	public:

	typedef aab::visen::TextureBasePtr TextureBasePtr;
	typedef aab::visen::TexturePtr TexturePtr;
	//typedef aab::time::FrameTicker FrameTicker;

	private:

		TextureBasePtr texture;

	public:

		explicit TextureNode (TextureBasePtr);// throw (std::exception &);
		explicit TextureNode (TexturePtr, //FrameTicker::Ptr,
                        int frameWidth, int frameHeight);// throw (std::exception &);
		virtual ~TextureNode ();// throw ();

		virtual void before ();
		virtual void after ();

		void render ();

		TextureBasePtr getTextureBase ();

};


}		//	game
}		//	aab
#endif	//	AAB_GAME_TEXTURE_NODE_CLASS


