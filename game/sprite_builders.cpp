
/**
*
*	sprite_builders.cpp
*
**/

#include"sprite_builders.hpp"
#include<stdexcept>
namespace aab	{
namespace game	{

//[1]
game::Sprite * loadSprite (visen::Screen window, std::string filename)
{
	visen::TexturePtr texture = makeTexture (window, filename);
	return new Sprite (texture);
}

//[2]
game::Sprite * loadSprite (visen::Screen window, std::string filename, const visen::Colorf mask)
{
	visen::TexturePtr texture = makeTexture (window, filename, mask);
	return new Sprite (texture);
}

//[3]
game::Sprite * loadSprite (visen::Screen window, std::string filename, std::string maskfilename)
{
	visen::TexturePtr texture = makeTexture (window, filename, maskfilename);
	return new Sprite (texture);
}

//[4]
game::Sprite * loadSprite (visen::Screen window, std::string filename, const visen::Colorf mask, int frameWidth, int frameHeight, int frames)//, aab::time::TimeReporter::Ptr deltaTime)
{
	visen::TexturePtr texture = makeTexture (window, filename, mask);
	//time::FrameTicker::Ptr ticker (new time::FrameTicker(deltaTime, 60, 0, frames - 1)); // defaults to one frame per 60 reports
	return new Sprite (texture, /*ticker,*/ frameWidth, frameHeight);
}

//[5]
game::Sprite * loadSprite (visen::Screen window, std::string filename, std::string maskfilename, int frameWidth, int frameHeight, int frames)//, aab::time::TimeReporter::Ptr deltaTime)
{
	visen::TexturePtr texture = makeTexture (window, filename, maskfilename);
	//time::FrameTicker::Ptr ticker (new time::FrameTicker (deltaTime, 60, 0, frames - 1)); // defaults to one frame per 60 reports
	return new Sprite (texture, /*ticker,*/ frameWidth, frameHeight);
}

//[6]
game::Sprite * loadSprite (visen::Screen window, std::string filename, const visen::Colorf mask, int frameWidth, int frameHeight)//, time::FrameTicker::Ptr ticker)
{
	visen::TexturePtr texture = makeTexture (window, filename, mask);
	return new Sprite (texture, /*ticker,*/ frameWidth, frameHeight);
}

//[7]
game::Sprite * loadSprite (visen::Screen window, std::string filename, std::string maskfilename, int frameWidth, int frameHeight)//, time::FrameTicker::Ptr ticker)
{
	visen::TexturePtr texture = makeTexture (window, filename, maskfilename);
	return new Sprite (texture, /*ticker,*/ frameWidth, frameHeight);
}





}		//	game
}		//	aab






