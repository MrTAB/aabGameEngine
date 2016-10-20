
/**
*
*	texture_node.hpp
*
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


