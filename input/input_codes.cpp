
/**
*
*
*
**/

#include"input_codes.hpp"
#include"gamepad_values.hpp"
#include"hat_position.hpp"
#include<test/debug_assertions.hpp>
#include<sstream>
#include<sdl.H>
//#ifdef _DEBUG
#include<stdexcept>
#include<fstream>
#include<iostream>
//#endif
namespace aab	{
namespace input	{
namespace universal	{
  
  
#define IS_KEY(C)  isKey(C) 
#define IS_MOUSE_BUTTON(C)  C < universal::mouse_x
#define IS_MOUSE_POSITION(C)  C < universal::mouse_x_change
#define IS_MOUSE_MOVE(C)  C < universal::gamepad_0_button_0
#define IS_GAMEPAD_BUTTON(C)  C < universal::gamepad_0_axis_0  
#define IS_GAMEPAD_AXIS(C)  C < universal::gamepad_0_axis_0_left
#define IS_GAMEPAD_AXIS_NEGATIVE(C)  C < universal::gamepad_0_axis_0_right
#define IS_GAMEPAD_AXIS_POSITIVE(C)  C < universal::gamepad_0_ball_0_x
#define IS_GAMEPAD_BALL_X(C)    C < universal::gamepad_0_ball_0_y
#define IS_GAMEPAD_BALL_Y(C)    C < universal::gamepad_0_hat_0
#define IS_GAMEPAD_HAT(C)   C < universal::gamepad_0_hat_0_x
#define IS_GAMEPAD_HAT_X(C) C < universal::gamepad_0_hat_0_y
#define IS_GAMEPAD_HAT_Y(C) true


/*
{
    if(IS_KEY(code))
    {
        return ;
    }
    else if(IS_MOUSE_BUTTON(code))
    {
        return ;
    }
    else if (IS_MOUSE_POSITION(code))
    {
        return ;
    }
    else if (IS_MOUSE_MOVE(code))
    {
        return ;
    }
    else if( IS_GAMEPAD_BUTTON(code))
    {
        return ;
    }
    else if( IS_GAMEPAD_AXIS(code))
    {
        return ;
    }
    else if( IS_GAMEPAD_AXIS_NEGATIVE(code))
    {
        return ;
    }
    else if( IS_GAMEPAD_AXIS_POSITIVE(code))
    {
        return ;
    }
    else if( IS_GAMEPAD_BALL_X(code))
    {
        return ;
    }
    else if( IS_GAMEPAD_BALL_Y(code))
    {
        return ;
    }
    else if( IS_GAMEPAD_HAT(code))
    {
        return ;
    }
    else if( IS_GAMEPAD_HAT_X(code))
    {
        return ;
    }
    else if( IS_GAMEPAD_HAT_Y(code))
    {
        return ;
    }
}
*/

std::string getInputCodeSymbolName (InputCode code)
{
    std::stringstream message;
    
    if (code == invalid_input_code)
    {
        message << "invalid_input_code";
    }
	else if (IS_KEY(code))
    {
        switch(code)
        {
            case key_backspace:return "key_backspace";
            case key_tab:return "key_tab";
            case key_clear:return "key_clear";
            case key_return:return "key_return";
            case key_pause:return "key_pause";
            case key_escape:return "key_escape";
            case key_space:return "key_space";
            case key_exclaim:return "key_exclaim";
            case key_doublequote:return "key_doublequote";
            case key_hash:return "key_hash";
            case key_dollar:return "key_dollar";
            case key_ampersand:return "key_ampersand";
            case key_quote:return "key_quote";
            case key_leftparenthesis:return "key_leftparenthesis";
            case key_rightparenthesis:return "key_rightparenthesis";
            case key_asterisk:return "key_asterisk";
            case key_plus:return "key_plus";
            case key_comma:return "key_comma";
            case key_minus:return "key_minus";
            case key_period:return "key_period";
            case key_slash:return "key_slash";
            case key_0:return "key_0";
            case key_1:return "key_1";
            case key_2:return "key_2";
            case key_3:return "key_3";
            case key_4:return "key_4";
            case key_5:return "key_5";
            case key_6:return "key_6";
            case key_7:return "key_7";
            case key_8:return "key_8";
            case key_9:return "key_9";
            case key_colon:return "key_colon";
            case key_semicolon:return "key_semicolon";
            case key_less:return "key_less";
            case key_equals:return "key_equals";
            case key_greater:return "key_greater";
            case key_question:return "key_question";
            case key_at:return "key_at";
            case key_leftbracket:return "key_leftbracket";
            case key_backslash:return "key_backslash";
            case key_rightbracket:return "key_rightbracket";
            case key_caret:return "key_caret";
            case key_underscore:return "key_underscore";
            case key_backquote:return "key_backquote";
            case key_a:return "key_a";
            case key_b:return "key_b";
            case key_c:return "key_c";
            case key_d:return "key_d";
            case key_e:return "key_e";
            case key_f:return "key_f";
            case key_g:return "key_g";
            case key_h:return "key_h";
            case key_i:return "key_i";
            case key_j:return "key_j";
            case key_k:return "key_k";
            case key_l:return "key_l";
            case key_m:return "key_m";
            case key_n:return "key_n";
            case key_o:return "key_o";
            case key_p:return "key_p";
            case key_q:return "key_q";
            case key_r:return "key_r";
            case key_s:return "key_s";
            case key_t:return "key_t";
            case key_u:return "key_u";
            case key_v:return "key_v";
            case key_w:return "key_w";
            case key_x:return "key_x";
            case key_y:return "key_y";
            case key_z:return "key_z";
            case key_delete:return "key_delete";
            case key_pad0:return "key_pad0";
            case key_pad1:return "key_pad1";
            case key_pad2:return "key_pad2";
            case key_pad3:return "key_pad3";
            case key_pad4:return "key_pad4";
            case key_pad5:return "key_pad5";
            case key_pad6:return "key_pad6";
            case key_pad7:return "key_pad7";
            case key_pad8:return "key_pad8";
            case key_pad9:return "key_pad9";
            case key_padperiod:return "key_padperiod";
            case key_paddivide:return "key_paddivide";
            case key_padmultiply:return "key_padmultiply";
            case key_padminus:return "key_padminus";
            case key_padplus:return "key_padplus";
            case key_padenter:return "key_padenter";
            case key_padequals:return "key_padequals";
            case key_up:return "key_up";
            case key_down:return "key_down";
            case key_right:return "key_right";
            case key_left:return "key_left";
            case key_insert:return "key_insert";
            case key_home:return "key_home";
            case key_end:return "key_end";
            case key_pageup:return "key_pageup";
            case key_pagedown:return "key_pagedown";
            case key_f1:return "key_f1";
            case key_f2:return "key_f2";
            case key_f3:return "key_f3";
            case key_f4:return "key_f4";
            case key_f5:return "key_f5";
            case key_f6:return "key_f6";
            case key_f7:return "key_f7";
            case key_f8:return "key_f8";
            case key_f9:return "key_f9";
            case key_f10:return "key_f10";
            case key_f11:return "key_f11";
            case key_f12:return "key_f12";
            case key_f13:return "key_f13";
            case key_f14:return "key_f14";
            case key_f15:return "key_f15";
            case key_numlock:return "key_numlock";
            case key_capslock:return "key_capslock";
            case key_scrolllock:return "key_scrolllock";
            case key_rightshift:return "key_rightshift";
            case key_leftshift:return "key_leftshift";
            case key_rightcontrol:return "key_rightcontrol";
            case key_leftcontrol:return "key_leftcontrol";
            case key_rightalt:return "key_rightalt";
            case key_leftalt:return "key_leftalt";
            case key_rightmeta:return "key_rightmeta";
            case key_leftmeta:return "key_leftmeta";
            case key_leftsuper:return "key_leftsuper";
            case key_rightsuper:return "key_rightsuper";
            case key_mode:return "key_mode";
            case key_help:return "key_help";
            case key_print:return "key_print";
            case key_sysrq:return "key_sysrq";
            case key_break:return "key_break";
            case key_menu:return "key_menu";
            case key_power:return "key_power";
            case key_euro:return "key_euro";
            default:
                return "invalid_input_code";
        }
    }
    else if (IS_MOUSE_BUTTON(code))
    {   // mouse button
        message << "mouse_button_" << code - mouse_button_1 + 1;
    }
    else if (IS_MOUSE_POSITION(code))
    {   // mouse button
        message << "mouse_" << (code == mouse_x?"x":"y");
    }
    else if (IS_MOUSE_MOVE(code))
    {   // mouse button
        message << "mouse_" << (code == mouse_x_change?"x":"y") << "_change";
    }
    else
    {
        //Gamepad 
        const int gamepad = (code - gamepad_0_button_0)/gamepad_distance;
        
        message << "gamepad_" << gamepad << "_";
        
        const int resolved_code = code - gamepad*gamepad_distance;
        
        if (IS_GAMEPAD_BUTTON(resolved_code))
        {   //gamepad button
            message << "button_" << resolved_code - gamepad_0_button_0;
        }
        else if (IS_GAMEPAD_AXIS(resolved_code)) 
        {   //gamepad axis
            message << "axis_" << resolved_code - gamepad_0_axis_0;
        }
        else if (IS_GAMEPAD_AXIS_NEGATIVE(resolved_code)) 
        {   //gamepad axis
            message << "axis_" << resolved_code - gamepad_0_axis_0_left <<  ((resolved_code-gamepad_0_axis_0_left)%2?"_up":"_left");
        }
        else if (IS_GAMEPAD_AXIS_POSITIVE(resolved_code)) 
        {   //gamepad axis
            message << "axis_" << resolved_code - gamepad_0_axis_0_right <<  ((resolved_code-gamepad_0_axis_0_right)%2?"_down":"_right");
        }
        else if (IS_GAMEPAD_BALL_X(resolved_code))
        {   // ball x
            message << "ball_" << resolved_code - gamepad_0_ball_0_x << "_x";
        }
        else if (IS_GAMEPAD_BALL_Y(resolved_code))
        {   // ball y
            message << "ball_" << resolved_code - gamepad_0_ball_0_y << "_y";        
        }
        else if (IS_GAMEPAD_HAT(resolved_code))
        {   //gamepad hats                
            message << "hat_" << resolved_code - gamepad_0_hat_0;
        }
        else if (IS_GAMEPAD_HAT_X(resolved_code))
        {
            message << "hat_" << resolved_code - gamepad_0_hat_0_x << "_x";
        }
        else if (IS_GAMEPAD_HAT_Y(resolved_code)) //if (resolved_code < universal::gamepad_0_hat_0_centered )
        {
            message << "hat_" << resolved_code - gamepad_0_hat_0_y << "_y";
        }
        else //individual gamepad hat values
        {
            int hat_distance = gamepad_0_hat_1_centered - gamepad_0_hat_0_centered;
            int hat = (resolved_code - gamepad_0_hat_0)/hat_distance;
            
            message << "hat_" << hat << "_";
            
            switch(resolved_code - hat*hat_distance)
            {
                case gamepad_0_hat_0_centered: message << "centered";break;
                case gamepad_0_hat_0_up: message << "up";break;
                case gamepad_0_hat_0_right: message << "right";break;
                case gamepad_0_hat_0_down: message << "down";break;
                case gamepad_0_hat_0_left: message << "left";break;
                case gamepad_0_hat_0_rightup: message << "rightup";break;
                case gamepad_0_hat_0_rightdown: message << "rightdown";break;
                case gamepad_0_hat_0_leftup: message << "leftup";break;
                case gamepad_0_hat_0_leftdown: message << "leftdown";break;
            }
        }
    }
    
      
    return message.str();
}

std::string getInputCodeDisplayName (InputCode code)
{
    std::stringstream message;
    
    if (code == invalid_input_code)
    {
        message << "unknown key";
    }
	else if (IS_KEY(code))
    {
        return std::string(SDL_GetKeyName ((SDLKey) code));
    }
    else if (IS_MOUSE_BUTTON(code))
    {   // mouse button
        message << "Mouse button " << code - mouse_button_1 + 1;
    }
    else if (IS_MOUSE_POSITION(code))
    {   // mouse button
        message << "Mouse position " << (code == mouse_x?"x":"y");
    }
    else if (IS_MOUSE_MOVE(code))
    {   // mouse button
        message << "Mouse move " << (code == mouse_x_change?"x":"y");
    }
    else
    {
        //Gamepad 
        const int gamepad = (code - gamepad_0_button_0)/gamepad_distance;
        
        message << "Gamepad " << gamepad << " ";
        
        const int resolved_code = code - gamepad*gamepad_distance;
        
        if (IS_GAMEPAD_BUTTON(resolved_code))
        {   //gamepad button
            message << "button " << resolved_code - gamepad_0_button_0;
        }
        else if (IS_GAMEPAD_AXIS(resolved_code)) 
        {   //gamepad axis
            message << "Axis " << resolved_code - gamepad_0_axis_0;
        }
        else if (IS_GAMEPAD_AXIS_NEGATIVE(resolved_code)) 
        {   //gamepad axis
            message << "Axis " << resolved_code - gamepad_0_axis_0_left << " negative";
        }
        else if (IS_GAMEPAD_AXIS_POSITIVE(resolved_code)) 
        {   //gamepad axis
            message << "Axis " << resolved_code - gamepad_0_axis_0_right << " positive";
        }
        else if (IS_GAMEPAD_BALL_X(resolved_code))
        {   // ball x
            message << "Ball X " << resolved_code - gamepad_0_ball_0_x;
        }
        else if (IS_GAMEPAD_BALL_Y(resolved_code))
        {   // ball y
            message << "Ball Y " << resolved_code - gamepad_0_ball_0_y;        
        }
        else if (IS_GAMEPAD_HAT(resolved_code))
        {   //gamepad hats                
            message << "Hat " << resolved_code - gamepad_0_hat_0;
        }
        else if (IS_GAMEPAD_HAT_X(resolved_code))
        {
            message << "Hat X " << resolved_code - gamepad_0_hat_0_x;
        }
        else if (IS_GAMEPAD_HAT_Y(resolved_code)) //if (resolved_code < universal::gamepad_0_hat_0_centered )
        {
            message << "Hat Y " << resolved_code - gamepad_0_hat_0_y;
        }
        else //individual gamepad hat values
        {
            int hat_distance = gamepad_0_hat_1_centered - gamepad_0_hat_0_centered;
            int hat = (resolved_code - gamepad_0_hat_0)/hat_distance;
            
            message << "Hat code " << hat;
            
            switch(resolved_code - hat*hat_distance)
            {
                case gamepad_0_hat_0_centered: message << " centered";break;
                case gamepad_0_hat_0_up: message << " up";break;
                case gamepad_0_hat_0_right: message << " right";break;
                case gamepad_0_hat_0_down: message << " down";break;
                case gamepad_0_hat_0_left: message << " left";break;
                case gamepad_0_hat_0_rightup: message << " rightup";break;
                case gamepad_0_hat_0_rightdown: message << " rightdown";break;
                case gamepad_0_hat_0_leftup: message << " leftup";break;
                case gamepad_0_hat_0_leftdown: message << " leftdown";break;
            }
        }
    }

    
    return message.str();
}

std::string getInputCodeShortName (InputCode code)
{
    std::stringstream message;
    
    if (code == invalid_input_code)
    {
        message << "??";
    }
	else if (IS_KEY(code))
    {
        return std::string(SDL_GetKeyName ((SDLKey) code));
    }
    else if (IS_MOUSE_BUTTON(code))
    {   // mouse button
        message << "M" << code - mouse_button_1 + 1;
    }
    else if (IS_MOUSE_POSITION(code))
    {   // mouse button
        message << "M" << (code == mouse_x?"x":"y");
    }
    else if (IS_MOUSE_MOVE(code))
    {   // mouse button
        message << "Md" << (code == mouse_x_change?"x":"y");
    }
    else
    {
        //Gamepad 
        const int gamepad = (code - gamepad_0_button_0)/gamepad_distance;
        
        message << "G" << gamepad;
        
        const int resolved_code = code - gamepad*gamepad_distance;
        
        if (IS_GAMEPAD_BUTTON(resolved_code))
        {   //gamepad button
            message << "B" << resolved_code - gamepad_0_button_0;
        }
        else if (IS_GAMEPAD_AXIS(resolved_code)) 
        {   //gamepad axis
            message << "A" << resolved_code - gamepad_0_axis_0;
        }
        else if (IS_GAMEPAD_AXIS_NEGATIVE(resolved_code)) 
        {   //gamepad axis
            message << "A" << resolved_code - gamepad_0_axis_0_left << "-";
        }
        else if (IS_GAMEPAD_AXIS_POSITIVE(resolved_code)) 
        {   //gamepad axis
            message << "A" << resolved_code - gamepad_0_axis_0_right << "+";
        }
        else if (IS_GAMEPAD_BALL_X(resolved_code))
        {   // ball x
            message << "BX" << resolved_code - gamepad_0_ball_0_x;
        }
        else if (IS_GAMEPAD_BALL_Y(resolved_code))
        {   // ball y
            message << "BY" << resolved_code - gamepad_0_ball_0_y;        
        }
        else if (IS_GAMEPAD_HAT(resolved_code))
        {   //gamepad hats                
            message << "H" << resolved_code - gamepad_0_hat_0;
        }
        else if (IS_GAMEPAD_HAT_X(resolved_code))
        {
            message << "HX" << resolved_code - gamepad_0_hat_0_x;
        }
        else if (IS_GAMEPAD_HAT_Y(resolved_code)) //if (resolved_code < universal::gamepad_0_hat_0_centered )
        {
            message << "HY" << resolved_code - gamepad_0_hat_0_y;
        }
        else //individual gamepad hat values
        {
            int hat_distance = gamepad_0_hat_1_centered - gamepad_0_hat_0_centered;
            int hat = (resolved_code - gamepad_0_hat_0)/hat_distance;
            
            message << "H" << hat;
            
            switch(resolved_code - hat*hat_distance)
            {
                case gamepad_0_hat_0_centered: message << "C";break;
                case gamepad_0_hat_0_up: message << "U";break;
                case gamepad_0_hat_0_right: message << "R";break;
                case gamepad_0_hat_0_down: message << "D";break;
                case gamepad_0_hat_0_left: message << "L";break;
                case gamepad_0_hat_0_rightup: message << "RU";break;
                case gamepad_0_hat_0_rightdown: message << "RD";break;
                case gamepad_0_hat_0_leftup: message << "LU";break;
                case gamepad_0_hat_0_leftdown: message << "LD";break;
            }
        }
    }
    
    
    return message.str();
}



unsigned int getInputCodeFromSymbolNameAsUint (std::string name)
{
    if (name.empty())
    {
        _DEBUG_RESPONSE(throw std::invalid_argument("getInputCodeFromSymbolName::\tInvalid Symbol Name '' (empty)"));
        _RELEASE_RESPONSE(return invalid_input_code);
    }
    
    switch(name[0])
    {
        case 'i': 
        {
            return invalid_input_code;
        }
        case 'k': //key_
        {
            switch(name.size())
            {
                case 5: //key_X, X<-{[0,9]|[a,z]}
                {
                    const char decider = name[4];
                    
                    if (decider >= '0' && decider <= '9') //key_X, X<-[0,9]
                    {
                        return key_0 + decider - '0';
                    }
                    else if (decider >= 'a' && decider <= 'z') //key_X, X<-[a,z]
                    {
                        return key_a + decider - 'a';
                    }
                    else
                    {
                        return invalid_input_code;
                    }
                }
                case 6:
                {
                    switch(name[4])
                    {
                        case 'a':return key_at;
                        case 'f':
                        {
                            if (name[5] >= '1' && name[5] <= '9')
                            {
                                return key_f1 + name[5]-'1';
                            }
                            else
                            {
                                return invalid_input_code;
                            }
                        }
                        case 'u':return key_up;
                        default: return invalid_input_code;
                    }
                }
                case 7:
                {
                    switch(name[4])
                    {
                        case 'e': return key_end;
                        case 't': return key_tab;
                        case 'f':
                        {
                            if (name[6] >= '0' && name[6] <= '5')
                            {
                                return key_f10 + name[6]-'0';
                            }
                            else
                            {
                                return invalid_input_code;
                            }
                        }
                        default: return invalid_input_code;
                    }
                }
                case 8:
                {
                    switch(name[6])
                    {
                        case 'w': return key_down;
                        case 'r': return key_euro;                        
                        case 'f': return key_left;
                        case 'm': return key_home;                         
                        case 'l': return key_help;
                        case 'n': return key_menu ;
                        case 'u': return key_plus;
                        case 's':
                        {
                            switch(name[4])
                            {
                                case 'l': return key_less;
                                case 'h': return key_hash;
                                default: return invalid_input_code;
                            }
                        }
                        case 'd':
                        {
                            switch(name[4])
                            {
                                case 'm': return key_mode;
                                case 'p':
                                {
                                    int number = name[7] - '0';
                                    if (number <0 || number > 9)
                                    {
                                        return invalid_input_code;
                                    }
                                    return key_pad0 + number;
                                }
                                default: return invalid_input_code;
                            }                                                     
                        }
                        default: return invalid_input_code;
                    }
                }
                case 9:
                {
                    switch(name[6])
                    {
                        case 'r': return key_caret;                                
                        case 'l': return key_colon;
                        case 'm': return key_comma;
                        case 'u': return key_pause;
                        case 'o': return key_quote;
                        case 'n': return key_minus;
                        case 'g': return key_right;
                        case 'w': return key_power;                                
                        case 'i': return key_print;
                        case 's': return key_sysrq;
                        case 'a':
                        {
                            switch(name[5])
                            {
                                case 'p': return key_space;
                                case 'l': return key_slash;
                                default: return invalid_input_code;
                            }
                        }
                        case 'e':
                        {
                            switch(name[4])
                            {
                                case 'c': return key_clear;
                                case 'b': return key_break;
                                default: return invalid_input_code;
                            }
                        }
                        default: return invalid_input_code;
                    }                
                }
                case 10:
                {
                    switch(name[8])
                    {
                        case 't': return key_delete;
                        case 'a': return key_dollar;
                        case 'l': return key_equals;
                        case 'p': return key_escape;                        
                        case 'o': return key_period;                                            
                        case 'u': return key_pageup;
                        case 'r':
                        {
                            switch(name[4])
                            {
                                case 'r': return key_return;
                                case 'i': return key_insert;
                                default: return invalid_input_code;
                            }
                        }
                        default: return invalid_input_code;
                    }
                }
                case 11:
                {
                    switch(name[4])
                    {
                        case 'e': return key_exclaim;
                        case 'g': return key_greater;                  
                        case 'p': return key_padplus;
                        case 'n': return key_numlock;
                        case 'l': return key_leftalt;                        
                        default: return invalid_input_code;
                    }
                }
                case 12:
                {
                    switch(name[10])
                    {                    
                    case 's': return key_asterisk;
                    case 'o': return key_question;
                    case 'u': return key_padminus;
                    case 'e': return key_padenter;
                    case 'w': return key_pagedown;
                    case 'c': return key_capslock;                                        
                    case 'l': return key_rightalt;
                    case 't': return key_leftmeta; 
                    default: return invalid_input_code;
                    }
                }
                case 13:
                {
                    switch(name[9])
                    {
                        case 's': return key_ampersand;                      
                        case 'l': return key_backslash;
                        case 'p': return key_backspace;
                        case 'o': return key_semicolon;
                        case 'r': return key_padperiod;
                        case 'v': return key_paddivide;                        
                        case 'h': return key_leftshift;
                        case 'm': return key_rightmeta;    
                        case 'u':
                        {
                            switch(name[4])
                            {
                                case 'b': return key_backquote;
                                case 'l': return key_leftsuper;
                                case 'p': return key_padequals;
                                default: return invalid_input_code;
                            }
                        }  
                        default: return invalid_input_code;
                    }
                }
                case 14:
                {
                    switch(name[10])
                    {
                        case 'c': return key_underscore;
                        case 'l': return key_scrolllock;
                        case 'h': return key_rightshift;  
                        case 'u': return key_rightsuper;   
                        default: return invalid_input_code;
                    }
                }
                case 15:
                {
                    switch(name[8])
                    {
                        case 'l': return key_doublequote;
                        case 'b': return key_leftbracket;
                        case 'u': return key_padmultiply; 
                        case 'c': return key_leftcontrol;
                        default: return invalid_input_code;
                    }
                                      
                }
                case 16:
                {
                    switch(name[9])
                    {
                        case 'b': return key_rightbracket;
                        case 'c': return key_rightcontrol;
                        default: return invalid_input_code;
                    }
                }
                case 19:
                {
                    return key_leftparenthesis;
                }
                case 20:
                {
                    return key_rightparenthesis;
                }
                default:
                {
                    return invalid_input_code;
                }
            }
            
            break;
        }
        case 'm'://mouse_
        {
            if (name.size() < 7)
            {
                return invalid_input_code;
            }
            
            switch(name[6])
            {
                case 'b': //mouse_button_
                {
                    switch(name.size())
                    {
                        case 14: return mouse_button_1 + name[13] - '1';
                        case 15:
                        {
                            int button = (name[13]-'0')*10 + (name[14]-'0');
                            if(button < 0 || button > mouse_buttons_supported)
                            {
                                return invalid_input_code;
                            }
                            return mouse_button_1 + button - 1;
                        }
                        default: return invalid_input_code;
                    }
                }
                case 'x': //mouse_x, mouse_x_change 
                {
                    switch(name.size())
                    {
                        case 7: return mouse_x;
                        case 14: return mouse_x_change;
                        default: return invalid_input_code;
                    }
                }
                case 'y': // mouse_y, mouse_y_change
                {
                    switch(name.size())
                    {
                        case 7: return mouse_y;
                        case 14: return mouse_y_change;
                        default: return invalid_input_code;
                    }
                }
                default: return invalid_input_code;
            }
            break;
        }
        case 'g'://gamepad_
        {
            
            if (name.size() < 15)
            {
                return invalid_input_code;
            }
            
            int gamepad = name[8] - '0';
            
            if (gamepad < 0 || gamepad > gamepads_supported)
            {
                return invalid_input_code;
            }
            
            switch(name[10])
            {
                case 'b': //gamepad_X_button_X | gamepad_X_ball_X_x | gamepad_X_ball_X_y
                {
                    int button = 0;
                    
                    switch(name.size())
                    {
                        case 18:
                        {
                            switch(name[11])
                            {
                                case 'u': button = name[17] - '0'; break; // continue on to make gamepad_X_button_X
                                case 'a': //gamepad_X_ball_X_x | gamepad_X_ball_X_y
                                {
                                    int ball = name[15] - '0';
                                    if (ball < 0 || ball > gamepad_balls_supported)
                                    {
                                        return invalid_input_code;
                                    }
                                    switch(name[17])
                                    {
                                        case 'x': return gamepadBallXCode(gamepad, ball);
                                        case 'y': return gamepadBallYCode(gamepad, ball);
                                        default:return invalid_input_code;
                                    }
                                }
                                default:return invalid_input_code;
                            }
                            break;
                        }
                        case 19:
                        {
                            button = (name[17]-'0')*10 + (name[18]-'0');
                            break;
                        }
                        default: return invalid_input_code;
                    }
                    
                    if (button < 0 || button > gamepad_buttons_supported)
                    {
                        return invalid_input_code;
                    }
                    
                    return gamepadButtonCode(gamepad, button);
                }
                case 'a'://gamepad_X_axis_X | gamepad_X_axis_X_XXXX
                {
                    const int axis = name[15] - '0';
                    if (axis < 0 || axis > gamepad_axes_supported)
                    {
                        return invalid_input_code;
                    }
                    switch(name.size())
                    {
                        case 16:
                        {
                            return gamepadAxisCode(gamepad, axis);
                        }
                        case 19: //gamepad_X_axis_X_up
                        {
                            return gamepadAxisIsNegative(gamepad, axis);
                        }
                        case 21: //gamepad_X_axis_X_left || gamepad_X_axis_X_down
                        {
                            switch(name[17])
                            {
                                case 'l':return gamepadAxisIsNegative(gamepad, axis);
                                case 'd': return gamepadAxisIsPositive(gamepad, axis);
                                default:return invalid_input_code;
                            }
                        }                        
                        case 22: //gamepad_0_axis_2_right
                        {
                            return gamepadAxisIsPositive(gamepad, axis);
                        }
                        default: return invalid_input_code;
                    }
                }
                case 'h'://gamepad_X_hat_X | gamepad_X_hat_X_x | gamepad_X_hat_X_y | gamepad_X_hat_X_<pos>
                {
                    const int hat = name[14] - '0';
                    if (hat < 0 || hat > gamepad_hats_supported)
                    {
                        return invalid_input_code;
                    }
                    switch(name.size()) 
                    {
                        case 15:
                        {
                            return gamepadHatCode(gamepad, hat);
                        }
                        case 17:
                        {
                            switch(name[16])
                            {
                                case 'x': return gamepadHatXCode (gamepad, hat);
                                case 'y': return gamepadHatYCode (gamepad, hat);
                                default:return invalid_input_code;
                            }
                        }
                        case 18: //up
                        {
                            return gamepadHatValueCode(gamepad, hat, hat_up);
                        }
                        case 20: //down | left
                        {
                            return gamepadHatValueCode(gamepad, hat, ('d'==name[16]? hat_down : hat_left));
                        }
                        case 21: // right
                        {
                            return gamepadHatValueCode(gamepad, hat, hat_right);
                        }
                        case 22: // leftup
                        {
                            return gamepadHatValueCode(gamepad, hat, hat_leftup);
                        }
                        case 23: // rightup
                        {
                            return gamepadHatValueCode(gamepad, hat, hat_rightup);
                        }
                        case 24: // centered | leftdown
                        {
                            return gamepadHatValueCode(gamepad, hat, ('c'==name[16]? hat_centered: hat_leftdown));
                        }
                        case 25: // rightdown
                        {
                            return gamepadHatValueCode(gamepad, hat, hat_rightdown);
                        }
                        default:
                        {
                            return invalid_input_code;
                        }
                    }
                }
                default:
                {
                     return invalid_input_code;
                }
                
            }
        }      
        default:
        {
            return invalid_input_code;
        }
    }
}

InputCode getInputCodeFromSymbolName (std::string name, bool strict)
{
    InputCode code = static_cast<InputCode>(getInputCodeFromSymbolNameAsUint(name));
    
    if (strict && code != invalid_input_code)
    {
        if (name != getInputCodeSymbolName(code))
        {
            #ifdef _DEBUG
                std::stringstream error;
                error << "getInputCodeFromSymbolName::\tInvalid input code match: "
                << name << " erroneously matched to " << getInputCodeSymbolName(code) << ".";
                throw std::logic_error(error.str());
            #else
                return invalid_input_code;
            #endif
        }
    }
    
    return code;
}


int getInputCodeMin(InputCode code)
{
    if(IS_KEY(code))
    {
        return 0;
    }
    else if(IS_MOUSE_BUTTON(code))
    {
        return 0;
    }
    else if (IS_MOUSE_POSITION(code))
    {   
        return 0;
    }
    else if (IS_MOUSE_MOVE(code))
    {   
        return 0;
    }
    else if( IS_GAMEPAD_BUTTON(code))
    {
        return 0;
    }
    else if( IS_GAMEPAD_AXIS(code))
    {
        return gamepad_axis_min;
    }
    else if (IS_GAMEPAD_AXIS_NEGATIVE(code)) 
    {   
        return 0;
    }
    else if (IS_GAMEPAD_AXIS_POSITIVE(code)) 
    {   
        return 0;
    }
    else if( IS_GAMEPAD_BALL_X(code))
    {
        return gamepad_axis_min;
    }
    else if( IS_GAMEPAD_BALL_Y(code))
    {
        return gamepad_axis_min;
    }
    else if( IS_GAMEPAD_HAT(code))
    {
        return HatPosition::centered;
    }
    else if( IS_GAMEPAD_HAT_X(code))
    {
        return -1;
    }
    else if( IS_GAMEPAD_HAT_Y(code))
    {
        return -1;
    }
}

int getInputCodeMax(InputCode code)
{
    if(IS_KEY(code))
    {
        return 1;
    }
    else if(IS_MOUSE_BUTTON(code))
    {
        return 1;
    }
    else if (IS_MOUSE_POSITION(code) || IS_MOUSE_MOVE(code))
    {   
        const SDL_VideoInfo *info = SDL_GetVideoInfo();
        return (code == mouse_x?info->current_w:info->current_h);
    }
    else if( IS_GAMEPAD_BUTTON(code))
    {
        return 1;
    }
    else if( IS_GAMEPAD_AXIS(code))
    {
        return gamepad_axis_max;
    }
    else if (IS_GAMEPAD_AXIS_NEGATIVE(code)) 
    {   
        return 1;
    }
    else if (IS_GAMEPAD_AXIS_POSITIVE(code)) 
    {   
        return 1;
    }
    else if( IS_GAMEPAD_BALL_X(code))
    {
        return gamepad_axis_max;
    }
    else if( IS_GAMEPAD_BALL_Y(code))
    {
        return gamepad_axis_max;
    }
    else if( IS_GAMEPAD_HAT(code))
    {
        return HatPosition::leftdown;
    }
    else if( IS_GAMEPAD_HAT_X(code))
    {
        return 1;
    }
    else if( IS_GAMEPAD_HAT_Y(code))
    {
        return 1;
    }
}



#ifdef _DEBUG
void testPrintingInputCodes(std::ostream &out)
{
    int words = 0;
    const int max_words_per_line = 3;
    
    
    out
    << "----------------------------------\n"
    << "Testing printing of Symbol names\n"
    << "----------------------------------\n";
    
    for(InputCode code = inputCodeBegin(); code!=inputCodeEnd(); code = getNextInputCode(code))
    {
        out << getInputCodeSymbolName((code)) << "\t";
        if(++words == max_words_per_line)
        {
            out << "\n";
            words = 0;
        }
    }
    
    out
    << "\n\n----------------------------------\n"
    << "Testing printing of Display names\n"
    << "----------------------------------\n";
    
    for(InputCode code = inputCodeBegin(); code!=inputCodeEnd(); code = getNextInputCode(code))
    {
        out << getInputCodeDisplayName((code)) << "\t";
        if(++words == max_words_per_line)
        {
            out << "\n";
            words = 0;
        }
    }
    
    out
    << "\n\n----------------------------------\n"
    << "Testing printing of Short Names\n"
    << "----------------------------------\n";
    
    for(InputCode code = inputCodeBegin(); code!=inputCodeEnd(); code = getNextInputCode(code))
    {
        out << getInputCodeShortName((code)) << "\t";
        if(++words == max_words_per_line)
        {
            out << "\n";
            words = 0;
        }
    }
    
    out
    << "\n\n----------------------------------\n"
    << "Testing getting code from symbol strings"
    << "----------------------------------\n";
    
    for(InputCode code = inputCodeBegin(); code!=inputCodeEnd(); code = getNextInputCode(code))
    {
        std::string symbolName = getInputCodeSymbolName(code);
        InputCode codeGuess = getInputCodeFromSymbolName(symbolName);

        out << symbolName << ":\t" << (code==codeGuess?"success":"FAILURE") << "\t" << codeGuess << "\n";
    }
    
    
    out <<"\n\n------------------------------------\n";
    
}
#endif

#ifdef _DEBUG
void testPrintingInputCodes()
{
    testPrintingInputCodes(std::cout);
}
#endif

#ifdef _DEBUG
void testPrintingInputCodes(std::string filename)
{
    std::ofstream out(filename.c_str());
    testPrintingInputCodes(out);
    out.close();
}
#endif


InputCode getNextInputCode(InputCode code)
{
    switch(code)
    {
        case invalid_input_code:
            return key_backspace ;
        case key_backspace :
            return key_tab;
        case key_tab:
            return key_clear;
        case key_clear:
            return key_return;
        case key_return:
            return key_pause;
        case key_pause:
            return key_escape;
        case key_escape:
            return key_space;
        case key_space:
            return key_exclaim;
        case key_exclaim:
            return key_doublequote;
        case key_doublequote:
            return key_hash;
        case key_hash:
            return key_dollar;
        case key_dollar:
            return key_ampersand;
        case key_ampersand:
            return key_quote;
        case key_quote:
            return key_leftparenthesis;
        case key_leftparenthesis:
            return key_rightparenthesis;
        case key_rightparenthesis:
            return key_asterisk;
        case key_asterisk:
            return key_plus;
        case key_plus:
            return key_comma;
        case key_comma:
            return key_minus;
        case key_minus:
            return key_period;
        case key_period:
            return key_slash;
        case key_slash:
            return key_0;
        case key_0:
            return key_1;
        case key_1:
            return key_2;
        case key_2:
            return key_3;
        case key_3:
            return key_4;
        case key_4:
            return key_5;
        case key_5:
            return key_6;
        case key_6:
            return key_7;
        case key_7:
            return key_8;
        case key_8:
            return key_9;
        case key_9:
            return key_colon;
        case key_colon:
            return key_semicolon;
        case key_semicolon:
            return key_less;
        case key_less:
            return key_equals;
        case key_equals:
            return key_greater;
        case key_greater:
            return key_question;
        case key_question:
            return key_at;
        case key_at:
            return key_leftbracket;
        case key_leftbracket:
            return key_backslash;
        case key_backslash:
            return key_rightbracket;
        case key_rightbracket:
            return key_caret;
        case key_caret:
            return key_underscore;
        case key_underscore:
            return key_backquote;
        case key_backquote:
            return key_a;
        case key_a:
            return key_b;
        case key_b:
            return key_c;
        case key_c:
            return key_d;
        case key_d:
            return key_e;
        case key_e:
            return key_f;
        case key_f:
            return key_g;
        case key_g:
            return key_h;
        case key_h:
            return key_i;
        case key_i:
            return key_j;
        case key_j:
            return key_k;
        case key_k:
            return key_l;
        case key_l:
            return key_m;
        case key_m:
            return key_n;
        case key_n:
            return key_o;
        case key_o:
            return key_p;
        case key_p:
            return key_q;
        case key_q:
            return key_r;
        case key_r:
            return key_s;
        case key_s:
            return key_t;
        case key_t:
            return key_u;
        case key_u:
            return key_v;
        case key_v:
            return key_w;
        case key_w:
            return key_x;
        case key_x:
            return key_y;
        case key_y:
            return key_z;
        case key_z:
            return key_delete;
        case key_delete:
            return key_pad0;
        case key_pad0:
            return key_pad1;
        case key_pad1:
            return key_pad2;
        case key_pad2:
            return key_pad3;
        case key_pad3:
            return key_pad4;
        case key_pad4:
            return key_pad5;
        case key_pad5:
            return key_pad6;
        case key_pad6:
            return key_pad7;
        case key_pad7:
            return key_pad8;
        case key_pad8:
            return key_pad9;
        case key_pad9:
            return key_padperiod;
        case key_padperiod:
            return key_paddivide;
        case key_paddivide:
            return key_padmultiply;
        case key_padmultiply:
            return key_padminus;
        case key_padminus:
            return key_padplus;
        case key_padplus:
            return key_padenter;
        case key_padenter:
            return key_padequals;
        case key_padequals:
            return key_up;
        case key_up:
            return key_down;
        case key_down:
            return key_right;
        case key_right:
            return key_left;
        case key_left:
            return key_insert;
        case key_insert:
            return key_home;
        case key_home:
            return key_end;
        case key_end:
            return key_pageup;
        case key_pageup:
            return key_pagedown;
        case key_pagedown:
            return key_f1;
        case key_f1:
            return key_f2;
        case key_f2:
            return key_f3;
        case key_f3:
            return key_f4;
        case key_f4:
            return key_f5;
        case key_f5:
            return key_f6;
        case key_f6:
            return key_f7;
        case key_f7:
            return key_f8;
        case key_f8:
            return key_f9;
        case key_f9:
            return key_f10;
        case key_f10:
            return key_f11;
        case key_f11:
            return key_f12;
        case key_f12:
            return key_f13;
        case key_f13:
            return key_f14;
        case key_f14:
            return key_f15;
        case key_f15:
            return key_numlock;
        case key_numlock:
            return key_capslock;
        case key_capslock:
            return key_scrolllock;
        case key_scrolllock:
            return key_rightshift;
        case key_rightshift:
            return key_leftshift;
        case key_leftshift:
            return key_rightcontrol;
        case key_rightcontrol:
            return key_leftcontrol;
        case key_leftcontrol:
            return key_rightalt;
        case key_rightalt:
            return key_leftalt;
        case key_leftalt:
            return key_rightmeta;
        case key_rightmeta:
            return key_leftmeta;
        case key_leftmeta:
            return key_leftsuper;
        case key_leftsuper:
            return key_rightsuper;
        case key_rightsuper:
            return key_mode;
        case key_mode:
            return key_help;
        case key_help:
            return key_print;
        case key_print:
            return key_sysrq;
        case key_sysrq:
            return key_break;
        case key_break:
            return key_menu;
        case key_menu:
            return key_power;
        case key_power:
            return key_euro;
        case key_euro:
            return mouse_button_1;
        default:
            return static_cast<InputCode>(code+1);
    }
}


}		//	universal
}		//	input
}		//	aab





