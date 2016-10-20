
/**
*
*	input_codes.hpp
*
*
**/

#if !defined(AAB_INPUT_UNIVERSAL_INPUT_CODES)
#define AAB_INPUT_UNIVERSAL_INPUT_CODES
#include<SDL_keysym.h>
#include<string>
#include"hat_value.hpp"
namespace aab	{
namespace input	{
namespace universal	{
 
 
enum
{
    input_code_gap = 128
};


enum InputCode
{
    invalid_input_code = 0,
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
	key_euro =	SDLK_EURO,
	
	mouse_button_1, mouse_button_2, mouse_button_3,
	mouse_button_4, mouse_button_5, mouse_button_6,mouse_button_7,
    mouse_button_8,mouse_button_9,mouse_button_10,mouse_button_11,
    mouse_button_12,mouse_button_13,mouse_button_14,mouse_button_15,
    mouse_button_16,mouse_button_17,mouse_button_18,mouse_button_19,
    mouse_button_20,mouse_button_21,mouse_button_22,mouse_button_23,
    mouse_button_24,mouse_button_25,mouse_button_26,mouse_button_27,
    mouse_button_28,mouse_button_29,mouse_button_30,mouse_button_31,
    mouse_button_32,
    
    mouse_x, mouse_y,
    
    mouse_x_change, mouse_y_change,
    
    //gamepad_0
    gamepad_0_button_0, gamepad_0_button_1,	gamepad_0_button_2,
    gamepad_0_button_3,	gamepad_0_button_4,	gamepad_0_button_5,
	gamepad_0_button_6,	gamepad_0_button_7,	gamepad_0_button_8,
	gamepad_0_button_9,	gamepad_0_button_10,gamepad_0_button_11,
	gamepad_0_button_12,gamepad_0_button_13,gamepad_0_button_14,
	gamepad_0_button_15,gamepad_0_button_16,gamepad_0_button_17,
	gamepad_0_button_18,gamepad_0_button_19,gamepad_0_button_20,
	gamepad_0_button_21,gamepad_0_button_22,gamepad_0_button_23,
	gamepad_0_button_24,gamepad_0_button_25,gamepad_0_button_26,
	gamepad_0_button_27,gamepad_0_button_28,gamepad_0_button_29,
   	gamepad_0_button_30,gamepad_0_button_31,gamepad_0_button_32,
	
	
	// Normally:
	// axis 0 -> x-axis of first joystick/d-pad
	// axis 1 -> y-axis of first joystick/d-pad
	// axis 2 -> x-axis of second joystick/d-pad
	// axis 3 -> y-axis of second joystick/d-pad
	gamepad_0_axis_0,gamepad_0_axis_1,gamepad_0_axis_2,gamepad_0_axis_3,
	gamepad_0_axis_4,gamepad_0_axis_5,gamepad_0_axis_6,gamepad_0_axis_7,
	gamepad_0_axis_8,
	
	//todo - add to input controller
	//These are 1 or zero, rather than 0-gamepad_axis_min or 0-gamepad_axis_max
	gamepad_0_axis_0_left,gamepad_0_axis_1_up,gamepad_0_axis_3_left,
	gamepad_0_axis_4_up,gamepad_0_axis_5_left,gamepad_0_axis_6_up,
	gamepad_0_axis_7_left,gamepad_0_axis_8_up,
	gamepad_0_axis_0_right,gamepad_0_axis_1_down,gamepad_0_axis_3_right,
	gamepad_0_axis_4_down,gamepad_0_axis_5_right,gamepad_0_axis_6_down,
	gamepad_0_axis_7_right,gamepad_0_axis_8_down,
	
	gamepad_0_ball_0_x, gamepad_0_ball_1_x,	gamepad_0_ball_2_x,
    gamepad_0_ball_3_x,	gamepad_0_ball_4_x,
    
	gamepad_0_ball_0_y,	gamepad_0_ball_1_y,	gamepad_0_ball_2_y,
    gamepad_0_ball_3_y,	gamepad_0_ball_4_y,

	gamepad_0_hat_0, gamepad_0_hat_1, gamepad_0_hat_2,
	gamepad_0_hat_3, gamepad_0_hat_4,
	
	gamepad_0_hat_0_x, gamepad_0_hat_1_x,	gamepad_0_hat_2_x,
    gamepad_0_hat_3_x,	gamepad_0_hat_4_x,
    
	gamepad_0_hat_0_y,	gamepad_0_hat_1_y,	gamepad_0_hat_2_y,
    gamepad_0_hat_3_y,	gamepad_0_hat_4_y,
	
	gamepad_0_hat_0_centered, gamepad_0_hat_0_up, gamepad_0_hat_0_right,
	gamepad_0_hat_0_down, gamepad_0_hat_0_left,	gamepad_0_hat_0_rightup,
	gamepad_0_hat_0_rightdown, gamepad_0_hat_0_leftup, gamepad_0_hat_0_leftdown,
	
	gamepad_0_hat_1_centered, gamepad_0_hat_1_up, gamepad_0_hat_1_right,
	gamepad_0_hat_1_down, gamepad_0_hat_1_left,	gamepad_0_hat_1_rightup,
	gamepad_0_hat_1_rightdown, gamepad_0_hat_1_leftup, gamepad_0_hat_1_leftdown,
	
	gamepad_0_hat_2_centered, gamepad_0_hat_2_up, gamepad_0_hat_2_right,
	gamepad_0_hat_2_down, gamepad_0_hat_2_left,	gamepad_0_hat_2_rightup,
	gamepad_0_hat_2_rightdown, gamepad_0_hat_2_leftup, gamepad_0_hat_2_leftdown,
	
	gamepad_0_hat_3_centered, gamepad_0_hat_3_up, gamepad_0_hat_3_right,
	gamepad_0_hat_3_down, gamepad_0_hat_3_left,	gamepad_0_hat_3_rightup,
	gamepad_0_hat_3_rightdown, gamepad_0_hat_3_leftup, gamepad_0_hat_3_leftdown,
	
	gamepad_0_hat_4_centered, gamepad_0_hat_4_up, gamepad_0_hat_4_right,
	gamepad_0_hat_4_down, gamepad_0_hat_4_left,	gamepad_0_hat_4_rightup,
	gamepad_0_hat_4_rightdown, gamepad_0_hat_4_leftup, gamepad_0_hat_4_leftdown,
	
	
	
	//gamepad_0_hat_0_x_
	
    //gamepad_1
    gamepad_1_button_0, gamepad_1_button_1,	gamepad_1_button_2,
    gamepad_1_button_3,	gamepad_1_button_4,	gamepad_1_button_5,
	gamepad_1_button_6,	gamepad_1_button_7,	gamepad_1_button_8,
	gamepad_1_button_9,	gamepad_1_button_10,gamepad_1_button_11,
	gamepad_1_button_12,gamepad_1_button_13,gamepad_1_button_14,
	gamepad_1_button_15,gamepad_1_button_16,gamepad_1_button_17,
	gamepad_1_button_18,gamepad_1_button_19,gamepad_1_button_20,
	gamepad_1_button_21,gamepad_1_button_22,gamepad_1_button_23,
	gamepad_1_button_24,gamepad_1_button_25,gamepad_1_button_26,
	gamepad_1_button_27,gamepad_1_button_28,gamepad_1_button_29,
   	gamepad_1_button_30,gamepad_1_button_31,gamepad_1_button_32,
	
	gamepad_1_axis_0,gamepad_1_axis_1,gamepad_1_axis_2,gamepad_1_axis_3,
	gamepad_1_axis_4,gamepad_1_axis_5,gamepad_1_axis_6,gamepad_1_axis_7,
	gamepad_1_axis_8,
	
	gamepad_1_axis_0_left,gamepad_1_axis_1_up,gamepad_1_axis_3_left,
	gamepad_1_axis_4_up,gamepad_1_axis_5_left,gamepad_1_axis_6_up,
	gamepad_1_axis_7_left,gamepad_1_axis_8_up,
	gamepad_1_axis_0_right,gamepad_1_axis_1_down,gamepad_1_axis_3_right,
	gamepad_1_axis_4_down,gamepad_1_axis_5_right,gamepad_1_axis_6_down,
	gamepad_1_axis_7_right,gamepad_1_axis_8_down,
	
	gamepad_1_ball_0_x, gamepad_1_ball_1_x,	gamepad_1_ball_2_x,
    gamepad_1_ball_3_x,	gamepad_1_ball_4_x,
    
	gamepad_1_ball_0_y,	gamepad_1_ball_1_y,	gamepad_1_ball_2_y,
    gamepad_1_ball_3_y,	gamepad_1_ball_4_y,

	gamepad_1_hat_0, gamepad_1_hat_1, gamepad_1_hat_2,
	gamepad_1_hat_3, gamepad_1_hat_4,
	
	gamepad_1_hat_0_x, gamepad_1_hat_1_x,	gamepad_1_hat_2_x,
    gamepad_1_hat_3_x,	gamepad_1_hat_4_x,
    
	gamepad_1_hat_0_y,	gamepad_1_hat_1_y,	gamepad_1_hat_2_y,
    gamepad_1_hat_3_y,	gamepad_1_hat_4_y,
    
    // Note: the hat thing might be useful, as would a similar thing for gamepad axis mapped negatively or positively.
    // This would allow simultaneous use of two of WASD, directional keys, D-pads, hats and joysticks
    
	gamepad_1_hat_0_centered, gamepad_1_hat_0_up, gamepad_1_hat_0_right,
	gamepad_1_hat_0_down, gamepad_1_hat_0_left,	gamepad_1_hat_0_rightup,
	gamepad_1_hat_0_rightdown, gamepad_1_hat_0_leftup, gamepad_1_hat_0_leftdown,
	
	gamepad_1_hat_1_centered, gamepad_1_hat_1_up, gamepad_1_hat_1_right,
	gamepad_1_hat_1_down, gamepad_1_hat_1_left,	gamepad_1_hat_1_rightup,
	gamepad_1_hat_1_rightdown, gamepad_1_hat_1_leftup, gamepad_1_hat_1_leftdown,
	
	gamepad_1_hat_2_centered, gamepad_1_hat_2_up, gamepad_1_hat_2_right,
	gamepad_1_hat_2_down, gamepad_1_hat_2_left,	gamepad_1_hat_2_rightup,
	gamepad_1_hat_2_rightdown, gamepad_1_hat_2_leftup, gamepad_1_hat_2_leftdown,
	
	gamepad_1_hat_3_centered, gamepad_1_hat_3_up, gamepad_1_hat_3_right,
	gamepad_1_hat_3_down, gamepad_1_hat_3_left,	gamepad_1_hat_3_rightup,
	gamepad_1_hat_3_rightdown, gamepad_1_hat_3_leftup, gamepad_1_hat_3_leftdown,
	
	gamepad_1_hat_4_centered, gamepad_1_hat_4_up, gamepad_1_hat_4_right,
	gamepad_1_hat_4_down, gamepad_1_hat_4_left,	gamepad_1_hat_4_rightup,
	gamepad_1_hat_4_rightdown, gamepad_1_hat_4_leftup, gamepad_1_hat_4_leftdown,
	
    //gamepad_2
    gamepad_2_button_0, gamepad_2_button_1,	gamepad_2_button_2,
    gamepad_2_button_3,	gamepad_2_button_4,	gamepad_2_button_5,
	gamepad_2_button_6,	gamepad_2_button_7,	gamepad_2_button_8,
	gamepad_2_button_9,	gamepad_2_button_10,gamepad_2_button_11,
	gamepad_2_button_12,gamepad_2_button_13,gamepad_2_button_14,
	gamepad_2_button_15,gamepad_2_button_16,gamepad_2_button_17,
	gamepad_2_button_18,gamepad_2_button_19,gamepad_2_button_20,
	gamepad_2_button_21,gamepad_2_button_22,gamepad_2_button_23,
	gamepad_2_button_24,gamepad_2_button_25,gamepad_2_button_26,
	gamepad_2_button_27,gamepad_2_button_28,gamepad_2_button_29,
   	gamepad_2_button_30,gamepad_2_button_31,gamepad_2_button_32,
	
	gamepad_2_axis_0,gamepad_2_axis_1,gamepad_2_axis_2,gamepad_2_axis_3,
	gamepad_2_axis_4,gamepad_2_axis_5,gamepad_2_axis_6,gamepad_2_axis_7,
	gamepad_2_axis_8,
	
	gamepad_2_axis_0_left,gamepad_2_axis_1_up,gamepad_2_axis_3_left,
	gamepad_2_axis_4_up,gamepad_2_axis_5_left,gamepad_2_axis_6_up,
	gamepad_2_axis_7_left,gamepad_2_axis_8_up,
	gamepad_2_axis_0_right,gamepad_2_axis_1_down,gamepad_2_axis_3_right,
	gamepad_2_axis_4_down,gamepad_2_axis_5_right,gamepad_2_axis_6_down,
	gamepad_2_axis_7_right,gamepad_2_axis_8_down,
	
	gamepad_2_ball_0_x, gamepad_2_ball_1_x,	gamepad_2_ball_2_x,
    gamepad_2_ball_3_x,	gamepad_2_ball_4_x,
    
	gamepad_2_ball_0_y,	gamepad_2_ball_1_y,	gamepad_2_ball_2_y,
    gamepad_2_ball_3_y,	gamepad_2_ball_4_y,

	gamepad_2_hat_0, gamepad_2_hat_1, gamepad_2_hat_2,
	gamepad_2_hat_3, gamepad_2_hat_4,
	
	gamepad_2_hat_0_x, gamepad_2_hat_1_x,	gamepad_2_hat_2_x,
    gamepad_2_hat_3_x,	gamepad_2_hat_4_x,
    
	gamepad_2_hat_0_y,	gamepad_2_hat_1_y,	gamepad_2_hat_2_y,
    gamepad_2_hat_3_y,	gamepad_2_hat_4_y,
    
	gamepad_2_hat_0_centered, gamepad_2_hat_0_up, gamepad_2_hat_0_right,
	gamepad_2_hat_0_down, gamepad_2_hat_0_left,	gamepad_2_hat_0_rightup,
	gamepad_2_hat_0_rightdown, gamepad_2_hat_0_leftup, gamepad_2_hat_0_leftdown,
	
	gamepad_2_hat_1_centered, gamepad_2_hat_1_up, gamepad_2_hat_1_right,
	gamepad_2_hat_1_down, gamepad_2_hat_1_left,	gamepad_2_hat_1_rightup,
	gamepad_2_hat_1_rightdown, gamepad_2_hat_1_leftup, gamepad_2_hat_1_leftdown,
	
	gamepad_2_hat_2_centered, gamepad_2_hat_2_up, gamepad_2_hat_2_right,
	gamepad_2_hat_2_down, gamepad_2_hat_2_left,	gamepad_2_hat_2_rightup,
	gamepad_2_hat_2_rightdown, gamepad_2_hat_2_leftup, gamepad_2_hat_2_leftdown,
	
	gamepad_2_hat_3_centered, gamepad_2_hat_3_up, gamepad_2_hat_3_right,
	gamepad_2_hat_3_down, gamepad_2_hat_3_left,	gamepad_2_hat_3_rightup,
	gamepad_2_hat_3_rightdown, gamepad_2_hat_3_leftup, gamepad_2_hat_3_leftdown,
	
	gamepad_2_hat_4_centered, gamepad_2_hat_4_up, gamepad_2_hat_4_right,
	gamepad_2_hat_4_down, gamepad_2_hat_4_left,	gamepad_2_hat_4_rightup,
	gamepad_2_hat_4_rightdown, gamepad_2_hat_4_leftup, gamepad_2_hat_4_leftdown,
	
    //gamepad_3
    gamepad_3_button_0, gamepad_3_button_1,	gamepad_3_button_2,
    gamepad_3_button_3,	gamepad_3_button_4,	gamepad_3_button_5,
	gamepad_3_button_6,	gamepad_3_button_7,	gamepad_3_button_8,
	gamepad_3_button_9,	gamepad_3_button_10,gamepad_3_button_11,
	gamepad_3_button_12,gamepad_3_button_13,gamepad_3_button_14,
	gamepad_3_button_15,gamepad_3_button_16,gamepad_3_button_17,
	gamepad_3_button_18,gamepad_3_button_19,gamepad_3_button_20,
	gamepad_3_button_21,gamepad_3_button_22,gamepad_3_button_23,
	gamepad_3_button_24,gamepad_3_button_25,gamepad_3_button_26,
	gamepad_3_button_27,gamepad_3_button_28,gamepad_3_button_29,
   	gamepad_3_button_30,gamepad_3_button_31,gamepad_3_button_32,
	
	gamepad_3_axis_0,gamepad_3_axis_1,gamepad_3_axis_2,gamepad_3_axis_3,
	gamepad_3_axis_4,gamepad_3_axis_5,gamepad_3_axis_6,gamepad_3_axis_7,
	gamepad_3_axis_8,
	
	gamepad_3_axis_0_left,gamepad_3_axis_1_up,gamepad_3_axis_3_left,
	gamepad_3_axis_4_up,gamepad_3_axis_5_left,gamepad_3_axis_6_up,
	gamepad_3_axis_7_left,gamepad_3_axis_8_up,
	gamepad_3_axis_0_right,gamepad_3_axis_1_down,gamepad_3_axis_3_right,
	gamepad_3_axis_4_down,gamepad_3_axis_5_right,gamepad_3_axis_6_down,
	gamepad_3_axis_7_right,gamepad_3_axis_8_down,
	
	gamepad_3_ball_0_x, gamepad_3_ball_1_x,	gamepad_3_ball_2_x,
    gamepad_3_ball_3_x,	gamepad_3_ball_4_x,
    
	gamepad_3_ball_0_y,	gamepad_3_ball_1_y,	gamepad_3_ball_2_y,
    gamepad_3_ball_3_y,	gamepad_3_ball_4_y,

	gamepad_3_hat_0, gamepad_3_hat_1, gamepad_3_hat_2,
	gamepad_3_hat_3, gamepad_3_hat_4,
	
	gamepad_3_hat_0_x, gamepad_3_hat_1_x,	gamepad_3_hat_2_x,
    gamepad_3_hat_3_x,	gamepad_3_hat_4_x,
    
	gamepad_3_hat_0_y,	gamepad_3_hat_1_y,	gamepad_3_hat_2_y,
    gamepad_3_hat_3_y,	gamepad_3_hat_4_y,
    
	gamepad_3_hat_0_centered, gamepad_3_hat_0_up, gamepad_3_hat_0_right,
	gamepad_3_hat_0_down, gamepad_3_hat_0_left,	gamepad_3_hat_0_rightup,
	gamepad_3_hat_0_rightdown, gamepad_3_hat_0_leftup, gamepad_3_hat_0_leftdown,
	
	gamepad_3_hat_1_centered, gamepad_3_hat_1_up, gamepad_3_hat_1_right,
	gamepad_3_hat_1_down, gamepad_3_hat_1_left,	gamepad_3_hat_1_rightup,
	gamepad_3_hat_1_rightdown, gamepad_3_hat_1_leftup, gamepad_3_hat_1_leftdown,
	
	gamepad_3_hat_2_centered, gamepad_3_hat_2_up, gamepad_3_hat_2_right,
	gamepad_3_hat_2_down, gamepad_3_hat_2_left,	gamepad_3_hat_2_rightup,
	gamepad_3_hat_2_rightdown, gamepad_3_hat_2_leftup, gamepad_3_hat_2_leftdown,
	
	gamepad_3_hat_3_centered, gamepad_3_hat_3_up, gamepad_3_hat_3_right,
	gamepad_3_hat_3_down, gamepad_3_hat_3_left,	gamepad_3_hat_3_rightup,
	gamepad_3_hat_3_rightdown, gamepad_3_hat_3_leftup, gamepad_3_hat_3_leftdown,
	
	gamepad_3_hat_4_centered, gamepad_3_hat_4_up, gamepad_3_hat_4_right,
	gamepad_3_hat_4_down, gamepad_3_hat_4_left,	gamepad_3_hat_4_rightup,
	gamepad_3_hat_4_rightdown, gamepad_3_hat_4_leftup, gamepad_3_hat_4_leftdown,
};


inline InputCode inputCodeBegin()
{
    return key_backspace;
}

inline InputCode inputCodeEnd()
{
    return gamepad_3_hat_4_y;
}

InputCode getNextInputCode(InputCode code);

enum
{
    gamepad_distance = gamepad_1_button_0 - gamepad_0_button_0
};

//could expand axes and button support by adding gaps between enums for input codes
enum
{
    mice_supported = 1,
    mouse_buttons_supported = 32,
    gamepad_axes_supported = 8,
    gamepad_balls_supported = 4,
};
enum
{
    gamepad_buttons_supported = 32,
    gamepad_hats_supported = 4,
};
enum
{
    gamepads_supported = 4
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


std::string getInputCodeDisplayName (InputCode);
std::string getInputCodeSymbolName (InputCode); // returns the symbol as it is in the enhum above
std::string getInputCodeShortName (InputCode);
InputCode getInputCodeFromSymbolName (std::string, bool strict = false); // e.g. "key_tab" returns key_tab // if strict is true, will check the full string, otherwise it will make a quick as possible guess based on the first few letters.

int getInputCodeMin(InputCode);
int getInputCodeMax(InputCode);

inline bool isKey (InputCode code)
{
    return code < key_euro && code != invalid_input_code;
}

inline InputCode keyNumber (int number)
{
	if (number <= 0 || number > 9)
		return key_0;

	return static_cast<InputCode>(key_1 + number - 1);
}


inline InputCode keyPadNumber (int number)
{
	if (number < 0 || number > 9)
		return key_0;

	return static_cast<InputCode>(key_pad0 + number);
}


inline InputCode mouseButtonCode(int button)
{
    return static_cast<InputCode>(mouse_button_1 + button - 1);
}

// work out maximums

inline InputCode gamepadButtonCode(int pad, int button)
{
    return static_cast<InputCode>(gamepad_distance*pad + gamepad_0_button_0 + button);
}

inline InputCode gamepadAxisCode(int pad, int axis)
{
    return static_cast<InputCode>(gamepad_distance*pad + gamepad_0_axis_0 + axis);
}

inline InputCode gamepadAxisIsNegative(int pad, int axis)
{
    return static_cast<InputCode>(gamepad_distance*pad + gamepad_0_axis_0_left + axis);
}

inline InputCode gamepadAxisIsPositive(int pad, int axis)
{
    return static_cast<InputCode>(gamepad_distance*pad + gamepad_0_axis_0_right + axis);
}

inline InputCode gamepadBallXCode(int pad, int ball)
{
    return static_cast<InputCode>(gamepad_distance*pad + gamepad_0_ball_0_x + ball);
}

inline InputCode gamepadBallYCode(int pad, int ball)
{
    return static_cast<InputCode>(gamepad_distance*pad + gamepad_0_ball_0_y + ball);
}

inline InputCode gamepadHatCode(int pad, int hat)
{
    return static_cast<InputCode>(gamepad_distance*pad + gamepad_0_hat_0 + hat);
}

inline InputCode gamepadHatXCode(int pad, int hat)
{
    return static_cast<InputCode>(gamepad_distance*pad + gamepad_0_hat_0_x + hat);
}

inline InputCode gamepadHatYCode(int pad, int hat)
{
    return static_cast<InputCode>(gamepad_distance*pad + gamepad_0_hat_0_y + hat);
}


inline InputCode gamepadHatValueCode(int pad, int hat, HatValue value)
{
    return static_cast<InputCode>(gamepad_distance*pad + gamepad_0_hat_0_centered + value + hat*(gamepad_0_hat_1_centered-gamepad_0_hat_0_centered));
}


#ifdef _DEBUG
void testPrintingInputCodes();
void testPrintingInputCodes(std::string filename);
#endif



}		//	universal
}		//	input
}		//	aab
#endif	//	AAB_INPUT_KEY_CODES




