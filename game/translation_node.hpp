
/**
*
*	translation_node.hpp
*
*
**/

#if !defined(AAB_GAME_TRANSLATION_NODE_CLASS)
#define AAB_GAME_TRANSLATION_NODE_CLASS
#include"scene_node.hpp"
#include"../visen/visual_translator.hpp"
//#include"../types/smart_ptr.hpp"
namespace aab	{
namespace game	{



class TranslationNode: public SceneNode, public aab::visen::VisualTranslater
{
	public:

		explicit TranslationNode ();
		virtual ~TranslationNode () ;//throw ();

		virtual void before ();
		virtual void after ();
};



}		//	game
}		//	aab
#endif	//	AAB_GAME_TRANSLATION_NODE_CLASS




