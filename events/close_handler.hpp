
/**
*
*	close_handler.hpp - Handles window close events
*
**/


#if !defined(AAB_EVENTS_CLOSE_HANDLER_CLASS)
#define AAB_EVENTS_CLOSE_HANDLER_CLASS
#include"imports.hpp"
#include"event_handlers.hpp"
namespace aab	{
namespace events{

class CloseHandler : public QuitHandler
{
	private:

		bool quitYet;

	public:

	typedef aab::types::Smart <CloseHandler>::Ptr Ptr;

	CloseHandler ();

	bool hasClosed () const;

	void close ();

	void handleEvent (const EventData);
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_CLOSE_HANDLER_CLASS

