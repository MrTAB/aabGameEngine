
/**
*
*	key_codes.hpp
*
*   Use these key codes and utility methods with Keyboard objects.
*    The SDL keycodes are wrapped in order to maintain a layer
*   of independence and separation between the engine and the underlying
*   library, allowing theat library to be abstract.
*
*
**/

#if !defined(AAB_INPUT_KEY_CODES)
#define AAB_INPUT_KEY_CODES
#include<SDL_keysym.h>
#include<string>
namespace aab	{
namespace input	{

enum KeyCode
{
	key_backspace =	SDLK_BACKSPACE,
	key_tab =	SDLK_TAB,
	key_clear =	SDLK_CLEAR,
	key_return =	SDLK_RETURN,
	key_pause =	SDLK_PAUSE,
	key_escape =	SDLK_ESCAPE,
	key_space =	SDLK_SPACE,
	key_exclaim =	SDLK_EXCLAIM,
	key_doublequote =	SDLK_QUOTEDBL,
	key_hash =	SDLK_HASH,
	key_dollar =	SDLK_DOLLAR,
	key_ampersand =	SDLK_AMPERSAND,
	key_quote =	SDLK_QUOTE,
	key_leftparenthesis =	SDLK_LEFTPAREN,
	key_rightparenthesis =	SDLK_RIGHTPAREN,
	key_asterisk =	SDLK_ASTERISK,
	key_plus =	SDLK_PLUS,
	key_comma =	SDLK_COMMA,
	key_minus =	SDLK_MINUS,
	key_period =	SDLK_PERIOD,
	key_slash =	SDLK_SLASH,
	key_0 =	SDLK_0,
	key_1 =	SDLK_1,
	key_2 =	SDLK_2,
	key_3 =	SDLK_3,
	key_4 =	SDLK_4,
	key_5 =	SDLK_5,
	key_6 =	SDLK_6,
	key_7 =	SDLK_7,
	key_8 =	SDLK_8,
	key_9 =	SDLK_9,
	key_colon =	SDLK_COLON,
	key_semicolon =	SDLK_SEMICOLON,
	key_less =	SDLK_LESS,
	key_equals =	SDLK_EQUALS,
	key_greater =	SDLK_GREATER,
	key_question =	SDLK_QUESTION,
	key_at =	SDLK_AT,
	key_leftbracket =	SDLK_LEFTBRACKET,
	key_backslash =	SDLK_BACKSLASH,
	key_rightbracket =	SDLK_RIGHTBRACKET,
	key_caret =	SDLK_CARET,
	key_underscore =	SDLK_UNDERSCORE,
	key_backquote =	SDLK_BACKQUOTE,
	key_a =	SDLK_a,
	key_b =	SDLK_b,
	key_c =	SDLK_c,
	key_d =	SDLK_d,
	key_e =	SDLK_e,
	key_f =	SDLK_f,
	key_g =	SDLK_g,
	key_h =	SDLK_h,
	key_i =	SDLK_i,
	key_j =	SDLK_j,
	key_k =	SDLK_k,
	key_l =	SDLK_l,
	key_m =	SDLK_m,
	key_n =	SDLK_n,
	key_o =	SDLK_o,
	key_p =	SDLK_p,
	key_q =	SDLK_q,
	key_r =	SDLK_r,
	key_s =	SDLK_s,
	key_t =	SDLK_t,
	key_u =	SDLK_u,
	key_v =	SDLK_v,
	key_w =	SDLK_w,
	key_x =	SDLK_x,
	key_y =	SDLK_y,
	key_z =	SDLK_z,
	key_delete =	SDLK_DELETE,
	key_pad0 =	SDLK_KP0,
	key_pad1 =	SDLK_KP1,
	key_pad2 =	SDLK_KP2,
	key_pad3 =	SDLK_KP3,
	key_pad4 =	SDLK_KP4,
	key_pad5 =	SDLK_KP5,
	key_pad6 =	SDLK_KP6,
	key_pad7 =	SDLK_KP7,
	key_pad8 =	SDLK_KP8,
	key_pad9 =	SDLK_KP9,
	key_padperiod =	SDLK_KP_PERIOD,
	key_paddivide =	SDLK_KP_DIVIDE,
	key_padmultiply =	SDLK_KP_MULTIPLY,
	key_padminus =	SDLK_KP_MINUS,
	key_padplus =	SDLK_KP_PLUS,
	key_padenter =	SDLK_KP_ENTER,
	key_padequals =	SDLK_KP_EQUALS,
	key_up =	SDLK_UP,
	key_down =	SDLK_DOWN,
	key_right =	SDLK_RIGHT,
	key_left =	SDLK_LEFT,
	key_insert =	SDLK_INSERT,
	key_home =	SDLK_HOME,
	key_end =	SDLK_END,
	key_pageup =	SDLK_PAGEUP,
	key_pagedown =	SDLK_PAGEDOWN,
	key_f1 =	SDLK_F1,
	key_f2 =	SDLK_F2,
	key_f3 =	SDLK_F3,
	key_f4 =	SDLK_F4,
	key_f5 =	SDLK_F5,
	key_f6 =	SDLK_F6,
	key_f7 =	SDLK_F7,
	key_f8 =	SDLK_F8,
	key_f9 =	SDLK_F9,
	key_f10 =	SDLK_F10,
	key_f11 =	SDLK_F11,
	key_f12 =	SDLK_F12,
	key_f13 =	SDLK_F13,
	key_f14 =	SDLK_F14,
	key_f15 =	SDLK_F15,
	key_numlock =	SDLK_NUMLOCK,
	key_capslock =	SDLK_CAPSLOCK,
	key_scrolllock =	SDLK_SCROLLOCK,
	key_rightshift =	SDLK_RSHIFT,
	key_leftshift =	SDLK_LSHIFT,
	key_rightcontrol =	SDLK_RCTRL,
	key_leftcontrol =	SDLK_LCTRL,
	key_rightalt =	SDLK_RALT,
	key_leftalt =	SDLK_LALT,
	key_rightmeta =	SDLK_RMETA,
	key_leftmeta =	SDLK_LMETA,
	key_leftsuper =	SDLK_LSUPER,
	key_rightsuper =	SDLK_RSUPER,
	key_mode =	SDLK_MODE,
	key_help =	SDLK_HELP,
	key_print =	SDLK_PRINT,
	key_sysrq =	SDLK_SYSREQ,
	key_break =	SDLK_BREAK,
	key_menu =	SDLK_MENU,
	key_power =	SDLK_POWER,
	key_euro =	SDLK_EURO
};


enum
{
	//mod_none	=	KMOD_NONE,	//  	No modifiers applicable
	mod_num	=	KMOD_NUM,	//  	Numlock is down
	mod_caps	=	KMOD_CAPS,	//  	Capslock is down
	mod_leftcontrol	=	KMOD_LCTRL,	//  	Left Control is down
	mod_rightcontrol	=	KMOD_RCTRL,	//  	Right Control is down
	mod_rightshift	=	KMOD_RSHIFT,	//  	Right Shift is down
	mod_leftshift	=	KMOD_LSHIFT,	//  	Left Shift is down
	mod_rightalt	=	KMOD_RALT,	//  	Right Alt is down
	mod_leftalt	=	KMOD_LALT,	//  	Left Alt is down
	mod_control	=	KMOD_CTRL,	//  	A Control key is down
	mod_shift	=	KMOD_SHIFT ,	// 	A Shift key is down
	mod_alt	=	KMOD_ALT	// 	An Alt key is down
};

typedef int ModCode;


std::string getKeyName (KeyCode);

inline KeyCode key_number (int number)
{
	if (number <= 0 || number > 9)
		return key_0;

	return static_cast<KeyCode>(key_1 + number - 1);
}

inline KeyCode key_padnumber (int number)
{
	if (number < 0 || number > 9)
		return key_0;

	return static_cast<KeyCode>(key_pad0 + number);
}

}		//	input
}		//	aab
#endif	//	AAB_INPUT_KEY_CODES




