
/**
*	sprite_builders.hpp
*
**/




#if !defined(AAB_GAME_SPRITE_BUILDERS)
#define AAB_GAME_SPRITE_BUILDERS
#include"sprite.hpp"
#include<string>
namespace aab	{
namespace game	{

// methods which do not ask for a ticker will require the ticker being updated once per loop
// Pull out and Update - can pull them all into a list and run through that list each loop.

//anticipate:
//  aab::test::file_not_found_error, std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error

Sprite * loadSprite (visen::Screen, std::string filename);
Sprite * loadSprite (visen::Screen, std::string filename, const visen::Colorf mask);
Sprite * loadSprite (visen::Screen, std::string filename, std::string maskfilename);
Sprite * loadSprite (visen::Screen, std::string filename, const visen::Colorf mask, int frameWidth, int frameHeight, int frames);//, aab::time::TimeReporter::Ptr);
Sprite * loadSprite (visen::Screen, std::string filename, std::string maskfilename, int frameWidth, int frameHeight, int frames);//, aab::time::TimeReporter::Ptr);
Sprite * loadSprite (visen::Screen, std::string filename, const visen::Colorf mask, int frameWidth, int frameHeight);//, time::FrameTicker::Ptr ticker);
Sprite * loadSprite (visen::Screen, std::string filename, std::string maskfilename, int frameWidth, int frameHeight);//, time::FrameTicker::Ptr ticker);
inline Sprite * clearSprite (Sprite * sprite) { delete sprite; return 0; }




}		//	game
}		//	aab
#endif	//	AAB_GAME_SPRITE_BUILDERS




