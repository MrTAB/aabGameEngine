
/**
*
*	display_list_node.hpp
*
*   A DisplayList node will render a display list at its position during
*   traversal of the Scene Graph
*
**/

#if !defined(AAB_GAME_DISPLAY_LIST_NODE_CLASS)
#define AAB_GAME_DISPLAY_LIST_NODE_CLASS
#include"scene_node.hpp"
#include"../visen/display_list.hpp"
namespace aab	{
namespace game	{


class DisplayListNode: public SceneNode
{
	public:

	typedef aab::visen::DisplayList DisplayList;

	private:

		DisplayList list;

	public:

		explicit DisplayListNode ();// std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
		virtual ~DisplayListNode ();// throw ();

		virtual void before ();
		virtual void after ();

		void setDisplayList (DisplayList);
		void setDisplayListAs (SceneNode*) ;// std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
		DisplayList getDisplayList ();

};



}		//	game
}		//	aab
#endif	//	AAB_GAME_DISPLAY_LIST_NODE_CLASS




