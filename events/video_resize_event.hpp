
/**
*
*	video_resize_event.hpp
*
**/

#if !defined(AAB_EVENTS_VIDEO_RESIZE_EVENT_CLASS)
#define AAB_EVENTS_VIDEO_RESIZE_EVENT_CLASS
#include"event.hpp"
#include"internal_event.hpp"
#include"imports.hpp"
namespace aab	{
namespace events{


class VideoResizeEvent : public Event
{
	private:

		int width, height;

	public:

	typedef aab::types::Smart <VideoResizeEvent>::Ptr Ptr;

	explicit VideoResizeEvent (InternalEvent e);
	virtual ~VideoResizeEvent () throw ();

	int getNewWidth () const;
	int getNewHeight () const;

	static EventType getClassEventType ();
};


}		//	events
}		//	aab
#endif	//	AAB_EVENTS_VIDEO_RESIZE_EVENT_CLASS

