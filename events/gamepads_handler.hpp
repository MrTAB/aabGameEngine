
/**
*
*	gamepads_handler.hpp
*
**/


#if !defined(AAB_EVENTS_GAMEPADS_HANDLER_CLASS)
#define AAB_EVENTS_GAMEPADS_HANDLER_CLASS
#include"gamepad_handler.hpp"
#include"gamepad_port_handler.hpp"
#include"imports.hpp"
#include<map>
namespace aab	{
namespace events{

/*
class GamepadsHandler : public GamepadPortHandler
{
	private:

		//typedef std::map <int, GamepadHandler::Ptr> HandlerMap;
		//HandlerMap handlersG;

	public:

	typedef aab::types::Smart <GamepadsHandler>::Ptr Ptr;
	typedef aab::input::HatPosition HatPosition;

	explicit GamepadsHandler (GamepadHandler::Ptr, int id = 0);
	explicit GamepadsHandler ();
	virtual ~GamepadsHandler () throw ();

	//void setHandler (GamepadHandler::Ptr, int id);
	//void clearHandler (int id);
	//void clearHandlers ();
	//GamepadHandler::Ptr getHandler (int id);

	//bool hasHandler (int id) const;
	//int countHandlers () const;

	void buttonPressed (int, int);
	void buttonReleased (int, int);
	void axisMove (int, int, double);
	void ballMove (int, int, double, double);
	void hatMove (int, int, HatPosition);
};
*/


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_GAMEPADS_HANDLER_CLASS

