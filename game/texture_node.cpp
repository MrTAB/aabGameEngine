
/**
*
*	texture_node.cpp
*
*
**/

#include"texture_node.hpp"
#include"../visen/animated_texture.hpp"
namespace aab	{
namespace game	{
using aab::visen::TextureBasePtr;
using aab::visen::TexturePtr;
//using aab::time::FrameTicker;
using aab::visen::makeAnimatedTexture;


TextureNode::TextureNode (TextureBasePtr texture):// throw (std::exception &) : 
texture (texture)
{
	// nothing to do here //
}

TextureNode::TextureNode (TexturePtr texture, //FrameTicker::Ptr ticker,
                          int frameWidth, int frameHeight)
	//throw (std::exception &)
{
	this-> texture = makeAnimatedTexture (texture, /*ticker,*/ frameWidth, frameHeight);
}

TextureNode::~TextureNode () //throw ()
{
	// nothing //
}

void TextureNode::before ()
{
	texture-> render ();
}

void TextureNode::after ()
{
	// nothing //
}

void TextureNode::render ()
{
	texture-> render ();
}

TextureBasePtr TextureNode::getTextureBase ()
{
	return texture;
}



}		//	game
}		//	aab


