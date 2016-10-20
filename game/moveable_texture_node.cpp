
/**
*
*	moveable_texture_node.cpp
*
*
**/

#include"moveable_texture_node.hpp"
#include"../visen/animated_texture.hpp"
namespace aab	{
namespace game	{
using aab::visen::TextureBasePtr;
using aab::visen::TexturePtr;
//using aab::time::FrameTicker;
using aab::visen::makeAnimatedTexture;



MoveableTextureNode::MoveableTextureNode (TextureBasePtr texture) 
: texture (texture)
{
	// nothing to do here //
}

MoveableTextureNode::MoveableTextureNode (TexturePtr texture, //FrameTicker::Ptr ticker,
                                          int frameWidth, int frameHeight)
	//std::invalid_argument
{
	this-> texture = makeAnimatedTexture (texture, /*ticker,*/ frameWidth, frameHeight);
}

MoveableTextureNode::~MoveableTextureNode () //throw ()
{
	// nothing to do here //
}

void MoveableTextureNode::draw ()
{
	before ();
	after ();
}

void MoveableTextureNode::before ()
{
	TranslationNode::before ();
	texture-> render ();
}

void MoveableTextureNode::after ()
{
	TranslationNode::after ();
}

void MoveableTextureNode::render ()
{
	texture-> render ();
}

TextureBasePtr MoveableTextureNode::getTextureBase ()
{
	return texture;
}



}		//	game
}		//	aab


