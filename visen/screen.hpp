
/**
*
*	catch exceptions by reference.
*
*	Screen is a singleton. Use startScreen (i.e. there is  no makeScreen()).
*
*	todo - allow different "views", allow changing of size etc? multiple states etc
**/

#if !defined(AAB_VISEN_SCREEN_CLASS)
#define AAB_VISEN_SCREEN_CLASS
#include"color.hpp"
#include"context_definition.hpp"
#include"../auden/audio_connector.hpp"
#include"../events/event_connector.hpp"
#include"../input/input_connector.hpp"
#include"../types/byte.hpp"
#include"../types/smart_ptr.hpp"
#include"prototype/screen.hh"
#include<memory>
#include<string>
namespace aab	{
namespace visen	{

/*
*	Perhaps screen should be called window?
*	then it'd make more sense to add SDL_WM_SetCaption etc.
*	next to add: resize, etc.
*
*	consider adding multi-threaded protection inside startScreen
*	and other methods (eg resize if it ocmes to it).
*/

class ScreenClass :	public aab::types::Manager <ScreenClass>,
					public aab::input::InputConnector,
					public aab::auden::AudioConnector,
					public aab::events::EventConnector
{
	public:

	typedef aab::types::byte_t byte_t;
	typedef aab::types::Smart <ScreenClass>::Ptr Ptr;

	private:

		struct Data;
		const std::auto_ptr <Data> data;

		ScreenClass (ScreenClass &);

		static bool exists;

	protected:

		friend class aab::types::Manager <ScreenClass>::Deleter;
		friend Ptr startScreen (int, int, ScreenMode);// aab::test::already_instantiated_error, std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
		friend Ptr startScreen (const ContextDefinition&);// aab::test::already_instantiated_error, std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
		ScreenClass (const ContextDefinition&);// std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
		virtual ~ScreenClass ();//throw ();


	public:

	void update ();
	void clear ();
	int getContextWidth () const;
	int getContextHeight () const;	
	inline int getScaledWidth () const {return getContextWidth() * getScaleX();};
	inline int getScaledHeight () const {return getContextHeight() * getScaleY();};
	
	void setClearColor (byte_t red, byte_t green, byte_t blue);
	void setClearColor (Colorf);
	void setCaption (const std::string);
	void showCursor ();
	void hideCursor ();
	void minimise ();
	float getScaleX() const;
	float getScaleY() const;
	
	bool hasDoubleBuffering()const;
	
	bool saveScreenShotPNG(const std::string filename)const;
	
	void resetProjection();

};


typedef ScreenClass::Ptr Screen;
Screen startScreen (int width, int height, ScreenMode = windowed_mode);// aab::test::already_instantiated_error, std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error
Screen startScreen (const ContextDefinition&);// aab::test::already_instantiated_error, std::domain_error, std::invalid_argument, std::logic_error, std::runtime_error


}		//	visen
}		//	aab
#endif	//	AAB_VISEN_SCREEN_CLASS




