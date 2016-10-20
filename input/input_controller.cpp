
/**
*
*	input_controller.cpp
*
**/

#include"input_controller.hpp"
#include"../time/time.hpp"
#include"gamepad_values.hpp"
#include"hat_position.hpp"
#include"../events/event_handlers.hpp"
#include"../events/gamepad_port_handler.hpp"
#include"../events/mouse_handler.hpp"
#include"../geometry/vector.hpp"
#include"../test/debug_assertions.hpp"
#include<sdl.H>
#include<cstdio>
#include<algorithm>
#include<iostream>
namespace aab	{
namespace input	{
using std::cout;

/*
   Thoughts on revising inputController:
   
   Better approach would be that some mapped values will be between 0 and 1, others will be either 0 or 1, others ranging -1 to 1 etc
   An improvement should have modifiable properties for each virtually mapped input, such as:
       is_analogue()
       is_analogue_capable()
       make_digital()
       make_abs()
       is_signed()
       is_signed_capable()
   and so on.
   This allows ones used for a gun button say to force digital abs output. Now, this is not really currently required because values are clipped such that low analogue results are 0.f and large are true. This therefore means that the isDown()  method returns true, appropriately.
   GetValue happens to return the sum of the first and second codes. Does this mean it is a value between 0 and 2.f?
   
   
   A more pressing update is allowing change of the clip value for each input or mapped value, so that analogue inputs can be used digitally in a comfortable manner.
   A suitable method for this could be
        make_button(threshold = 0.6) for example.
    However it is advisable that the threshold be assessed by the player playing the game, or matched to the model of controller being used if available.
    
    Currently, the InputControllerClass has one axisdirectionalcutoff which applies for all axis. This is not suitable.
    Also, the value is fully fleshed, and therefore set between say -32768 and 32768.
    
    Values are stored as ints. Where something wants to use things as analogue, it would be better if they were clipped to the the range [-1.f,1.f]
    Note that for axisMove, the inputcontroller has an approach where the negative and positive directions are both seperate inputs and also so is the total version.
    Based on the current setup, where axis clipping is done to axis alone during an axis move event, an axis directional cutoff would need to be specified based on the axis itself rather than the input.
    A future method could have a "cutoff" option for each input, but this may be overkill.
    
    Work out an overall axisdirectionalcutoff for SPB.
    Then implement a new version of axisdirectionalcutoff which supplies the gamepad and axis as fields. 
    
    
    Provide option for hat move flags ion each direction?
    Making it optionally enabled would be a good way for allowing people to disable the overhead.
    
    Also, a diagnostic version should be made, where if printing is enabled in _DEBUG, then every input is output to standard input.
    
    default is gamepad_axis_max/5.
    
    Lets try gamepad_axis_max/2
    
    Other issue is the doubling of analgue values due to the secondary inputs and primary inputs being equal in the the event of only one being set.
*/

class InputControllerClass::PressedEventHandler : public aab::events::KeyDownHandler
{
	InputControllerClass &owner;

	public:

	PressedEventHandler (InputControllerClass &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData key)
	{
		owner.setKeyPress (static_cast<InputCode>(key.getKeyCode ()));
	}
};


class InputControllerClass::ReleasedEventHandler : public aab::events::KeyUpHandler
{
	InputControllerClass &owner;

	public:

	ReleasedEventHandler (InputControllerClass &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData key)
	{
		owner.setKeyRelease (static_cast<InputCode>(key.getKeyCode ()));
	}
};

class InputControllerClass::FocusGainedHandler : public aab::events::KeyboardFocusGainedHandler
{
	InputControllerClass &owner;

	public:

	FocusGainedHandler (InputControllerClass &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData)
	{
		owner.keyboardFocusGained ();
	}
};


class InputControllerClass::FocusLostHandler : public aab::events::KeyboardFocusLostHandler
{
	InputControllerClass &owner;

	public:

	FocusLostHandler (InputControllerClass &owner) : owner (owner)
	{
		// nothing //
	}

	void handleEvent (const EventData)
	{
		owner.keyboardFocusLost ();
	}
};


class InputControllerClass::ICGamepadHandler: public aab::events::GamepadPortHandler
{
	InputControllerClass &owner;

	public:
	
	typedef aab::types::Smart <ICGamepadHandler>::Ptr Ptr;
	typedef aab::input::HatPosition HatPosition;
	//typedef aab::input::Gamepad Gamepad;
	

	ICGamepadHandler (InputControllerClass &owner) : owner (owner)
	{
		// nothing //
	}

	virtual void buttonPressed (int id, int button)
	{
	    owner.setInputValue(universal::gamepadButtonCode(id,button),1);
	}
	
	virtual void buttonReleased (int id, int button)
	{
	    owner.setInputValue(universal::gamepadButtonCode(id,button),0);
	}
	
	//http://www.third-helix.com/2013/04/doing-thumbstick-dead-zones-right/
	
	// Could implement a radial deadzone, and then allow a functor which the player
	// implements: this would allow a multiplication of the value, and would give them
	// the deadzone, and max.
	// alternatively, implement this as a standard feature
	// magnitude mapped linearly from [cutoff,gamepad_max]->[0,user_max]
	//what if someone wanted a non linear mapping?
	//Perhaps it is up to the user then to tae the linear output, e.g. 0-32768 (or user_max)
	//and scale it as they see fit.
	
	virtual void axisMove (int  id, int axis, aab::input::GamepadAxisValue value)
	{ 
	    /*
	    InputCode code = universal::gamepadAxisCode(id,axis);
	    owner.setInputValue(code,value);
	    
        if (std::abs(value) < owner.getAxisClip(code))
        {            
            owner.setInputValue(universal::gamepadAxisIsNegative(id,axis),0);
            owner.setInputValue(universal::gamepadAxisIsPositive(id,axis),0);
        }
        else if (value < 0)
        {
            owner.setInputValue(universal::gamepadAxisIsNegative(id,axis),1);
            owner.setInputValue(universal::gamepadAxisIsPositive(id,axis),0);
        }
        else
        {
            owner.setInputValue(universal::gamepadAxisIsNegative(id,axis),0);
            owner.setInputValue(universal::gamepadAxisIsPositive(id,axis),1);
        }
        */
        
	    InputCode code = universal::gamepadAxisCode(id,axis);
	    owner.setInputValue(code,value);
	    
	    if(value > 0)
	    {	        
	        owner.setInputValue(universal::gamepadAxisIsPositive(id,axis), value >= owner.getAxisClip(code));
	        owner.setInputValue(universal::gamepadAxisIsNegative(id,axis),0);
	    }
	    else
	    {
	        owner.setInputValue(universal::gamepadAxisIsNegative(id,axis), -value >= owner.getAxisClip(code));
	        owner.setInputValue(universal::gamepadAxisIsPositive(id,axis),0);
	    }
	    
        /*
        // This alternative version allows separate codes for each direction on the axis.
	    owner.setInputValue(universal::gamepadAxisCode(id,axis),value);
	    
	    if(value > 0)
	    {	        
	        const InputCode pos_code = universal::gamepadAxisIsPositive(id,axis);
	        owner.setInputValue(pos_code, value >= owner.getAxisClip(pos_code));
	        owner.setInputValue(universal::gamepadAxisIsNegative(id,axis),0);
	    }
	    else
	    {
	        const InputCode neg_code = universal::gamepadAxisIsNegative(id,axis);
	        owner.setInputValue(neg_code, -value >= owner.getAxisClip(neg_code));
	        owner.setInputValue(universal::gamepadAxisIsPositive(id,axis),0);
	    }
	    */
	}
	
	virtual void ballMove (int  id, int ball, aab::input::GamepadAxisValue xchange, aab::input::GamepadAxisValue ychange)
	{
	    owner.setInputValue(universal::gamepadBallXCode(id,ball),xchange);
	    owner.setInputValue(universal::gamepadBallYCode(id,ball),ychange);
	}
	
	virtual void hatMove (int id, int hat, HatPosition position)
	{
	    owner.setInputValue(universal::gamepadHatCode(id,hat),position);
	    owner.setInputValue(universal::gamepadHatXCode(id,hat),position.getX());
	    owner.setInputValue(universal::gamepadHatYCode(id,hat),position.getY());
	    
	    //todo: add support for centred etc flags for hats as individual booleans
	    //would need to set all to zero apart form activated one, set to true.
	    //is it worth it? Most clients may prefer to not have this overhead
	    
	    if(owner.isolatesHatValues(id, hat)) // each code is its own out of 9 values, only one is active at a time
	    {
	        //optimize - store off last hat direction so that it can be nullifued rather than removing all of them
	        const int begin = universal::gamepadHatValueCode(id, hat, getFirstHatValue());
	        const int end = universal::gamepadHatValueCode(id, hat, getLastHatValue()) + 1;
	        for(int t = begin; t < end; ++t)
	        {
	            owner.setInputValue(static_cast<InputCode>(t), false);
	        }
	        owner.setInputValue(static_cast<InputCode>(begin + position.as_hat_value()), true);
	    }
	    else // works as a d-pad, such that top right represents both top and right being active at the same time.
	    {
	        //optimize - store off last hat direction so that it can be nullifued rather than removing all of them
	        //todo - make a utility method to zero a hat
	        const int begin = universal::gamepadHatValueCode(id, hat, getFirstHatValue());
	        const int end = universal::gamepadHatValueCode(id, hat, getLastHatValue()) + 1;
	        for(int t = begin; t < end; ++t)
	        {
	            owner.setInputValue(static_cast<InputCode>(t), false);
	        }
	        
	        const HatValue value = position.as_hat_value();
	        const InputCode base_code = universal::gamepadHatValueCode(id,hat,getFirstHatValue());
	        owner.setInputValue(static_cast<InputCode>(base_code+value), true);
	        
	        switch(value)
	        {
                case hat_rightup:
                    owner.setInputValue(static_cast<InputCode>(base_code+hat_right), true);
                    owner.setInputValue(static_cast<InputCode>(base_code+hat_up), true);
                    break;
                case hat_rightdown:
                    owner.setInputValue(static_cast<InputCode>(base_code+hat_right), true);
                    owner.setInputValue(static_cast<InputCode>(base_code+hat_down), true);
                    break;
                case hat_leftup:
                    owner.setInputValue(static_cast<InputCode>(base_code+hat_left), true);
                    owner.setInputValue(static_cast<InputCode>(base_code+hat_up), true);
                    break;
                case hat_leftdown:
                    owner.setInputValue(static_cast<InputCode>(base_code+hat_left), true);
                    owner.setInputValue(static_cast<InputCode>(base_code+hat_down), true);
                    break;
                default:
                    break;
	        }
	    }
	}
};


class InputControllerClass::ICMouseHandler: public aab::events::MouseHandler
{
	InputControllerClass &owner;

	public:
	
	typedef aab::types::Smart <ICMouseHandler>::Ptr Ptr;

	ICMouseHandler (InputControllerClass &owner) : owner (owner)
	{
		// nothing //
	}
	
	virtual void moved (int x, int y, int dx, int dy)
	{
	    owner.setInputValue(universal::mouse_x, x);
	    owner.setInputValue(universal::mouse_y, y);
        owner.setInputValue(universal::mouse_x_change, dx);
	    owner.setInputValue(universal::mouse_y_change, dy);
	}
	
	virtual void buttonPressed (int button, int x, int y)
	{
	    owner.setInputValue(universal::mouseButtonCode(button), true);
	}
	
	virtual void buttonReleased (int button, int x, int y)
	{
	    owner.setInputValue(universal::mouseButtonCode(button), false);
	}
	
	virtual void focusGained ()
	{
	    //todo - add in focus gained for mouse
	    //owner.setInputValue(universal::mouse_);
	}
	
	virtual void focusLost ()
	{
	    //todo - add in focus lost for mouse
	    //other todo - should engine also check for game being minimised etc and provide alternate actions?
	    //owner.setInputValue(universal::mouse_);
	}
	
};

InputController makeInputController (InputConnector::Ptr connector)
{
	InputController ptr (new InputControllerClass (connector));//, InputControllerClass::Deleter ());
	return ptr;
}


InputControllerClass::InputControllerClass (InputConnector::Ptr connector) : //aab::test::already_instantiated_error, GamepadUnavailableException, NoGamepadsException, FailedToOpenGamepadException
	timeFunction (aab::time::getMilliseconds),
	defaultAxisClip(gamepad_axis_max/5)
{
    using aab::events::EventHandler;
    
    CodeValue blankCodeValue;        
    codeValues[universal::invalid_input_code] = blankCodeValue; 
    
	EventHandler::Ptr pressedHandler (new PressedEventHandler (*this));
	EventHandler::Ptr releasedHandler (new ReleasedEventHandler (*this));
	EventHandler::Ptr focusGainedHandler (new FocusGainedHandler (*this));
	EventHandler::Ptr focusLostHandler (new FocusLostHandler (*this));
	EventHandler::Ptr icGamepadHandler (new ICGamepadHandler (*this));
	EventHandler::Ptr icMouseHandler (new ICMouseHandler (*this));
	/*gamepadsHandler = aab::events::GamepadsAutoHandler::Ptr
                            (new aab::events::GamepadsAutoHandler ());*/

	setHandler (pressedHandler);
	setHandler (releasedHandler);
	setHandler (focusGainedHandler);
	setHandler (focusLostHandler);
	setHandler (icGamepadHandler);
	setHandler (icMouseHandler);
	
	
	//setHandler (gamepadsHandler-> getEventType(), gamepadsHandler);
	
	gamepadPorts = startGamepadPorts (connector);
	//gamepadPorts->setUnpluggedCallback(this); //todo - allow setting unplugged callback
	
	// ust open each gamepad so that events will be triggered.
	for(int t = 0; t < gamepadPorts->countGamepads(); ++t)
	{
        Gamepad gamepad = makeGamepad(gamepadPorts);
        //gamepadsHandler->addGamepad(gamepad);
        gamepads.push_back(gamepad);
	}
}

InputControllerClass::~InputControllerClass () throw ()
{
	// nothing //
}

void InputControllerClass::update ()
{
	recentlyModified.clear ();
	
	gamepadPorts->updateGamepadPorts();
	
	setInputValue(universal::mouse_x_change,0);
	setInputValue(universal::mouse_y_change,0);
	
	// todo - check for new gamepads not already opened and then open again?
	

}

int InputControllerClass::getAxisClip(const InputCode inputCode)const
{
    auto itr = axisClips.find(inputCode);
    
    if(axisClips.end() == itr)
    {
        return defaultAxisClip;
    }
    
    return itr->second;
}
 

void InputControllerClass::setCustomAxisClip(const InputCode inputCode, const int newClip)
{
    axisClips[inputCode] = newClip;
    /*
    auto itr = axisClips.find(inputCode);

    if(axisClips.end() == itr)
    {
        axisClips.insert(std::make_pair(inputCode, newClip);
    }
    else
    {
        itr->second == newClip;
    }*/
}

void InputControllerClass::setCustomAxisClip(const int id, const int axis, const int cutoff)
{
    return setCustomAxisClip(universal::gamepadAxisCode(id,axis), cutoff);
}
   
void InputControllerClass::removeCustomAxisClip(const InputCode inputCode)
{
    axisClips.erase(inputCode);
    /*
    auto itr = axisClips.find(inputCode);
    axisClips.erase(itr);
    
    if(axisClips.end() == itr)
    {
        axisClips.insert(std::make_pair(inputCode, newClip);
    }*/
}

void InputControllerClass::removeCustomAxisClip(const int id, const int axis)
{
    return removeCustomAxisClip(universal::gamepadAxisCode(id,axis));
}
   
   
bool InputControllerClass::hasCustomAxisClip(const InputCode inputCode)
{
    auto itr = axisClips.find(inputCode);
    
    return axisClips.end() != itr;
}

bool InputControllerClass::hasCustomAxisClip(const int id, const int axis)
{
    return hasCustomAxisClip(universal::gamepadAxisCode(id,axis));
}
    
    
/*
void InputControllerClass::axialDeadZoneAxes(int pad, int deadzone, int xAxis, int yAxis, int maximum )
{
    int xvalue = getCodeValue(universal::gamepadAxisCode(pad,xAxis));
    int yvalue = getCodeValue(universal::gamepadAxisCode(pad,yAxis));
    
    
    const int xsign = (xvalue<0)*(-2) + 1; // -1 or 1
    if ( xsign*xvalue < deadzone)
    {
        xvalue = 0;
    }
    else if ( xsign*xvalue > maximum )
    {
        xvalue = xsign * maximum;
    }
    
    
    const int ysign = (yvalue<0)*(-2) + 1; // -1 or 1
    if ( ysign*yvalue < deadzone)
    {
        yvalue = 0;
    }
    else if ( ysign*yvalue > maximum )
    {
        yvalue = ysign * maximum;
    }

    setInputValue(universal::gamepadAxisCode(pad,xAxis), xvalue);
    setInputValue(universal::gamepadAxisCode(pad,yAxis), yvalue);
}


void InputControllerClass::radialDeadZoneAxes(int pad, float deadzone, int xAxis, int yAxis, int maximum)
{
    //because the input doesn't happen every frame, this does not work properly.
    //the quick fix below does not seem to fix this well enough.
    
    static bool xmod = false;
    static bool ymod = false;

    if (hasJustModifiedCode(universal::gamepadAxisCode(pad,xAxis)))
    {
        xmod = true;
    }
    if (hasJustModifiedCode(universal::gamepadAxisCode(pad,yAxis)))
    {
        ymod = true;
    }
    
    if (!xmod || !ymod) // need to both be modified before any dead zoning. Alternatively, could have a modified version of each value.
    {
        return;
    }
    
    const float x = getCodeValue(universal::gamepadAxisCode(pad,xAxis));
    const float y = getCodeValue(universal::gamepadAxisCode(pad,yAxis));
    
    aab::geometry::Vector v = {x,y};
    
    float length = v.getLength();
    
    if (length < deadzone)
    {
        setInputValue(universal::gamepadAxisCode(pad,xAxis), 0);
        setInputValue(universal::gamepadAxisCode(pad,yAxis), 0);
    }
    else
    {
        //float newLength = (v.getLength() - deadzone) * (gamepad_axis_max) / (gamepad_axis_max-deadzone);
        float newLength = (v.getLength() - deadzone);
        //float newLength = (v.getLength() - deadzone)* (maximum+deadzone) /(gamepad_axis_max+deadzone);
        v.setLength(newLength);
        
        setInputValue(universal::gamepadAxisCode(pad,xAxis), v.x);
        setInputValue(universal::gamepadAxisCode(pad,yAxis), v.y);
    }
    
    xmod = false;
    ymod = false;
}
*/

////////////
//  user codes & their get values

void InputControllerClass::setControl(int userCode, InputCode inputCode)
{
    //map.insert(std::make_pair<int,InputCode>(userCode,inputCode));
    map1[userCode] = inputCode;
    
    
    if (map2.find(userCode) == map2.end())
    {
        map2[userCode] = inputCode;
    }
    
}

void InputControllerClass::setSecondControl(int userCode, InputCode inputCode)
{
    //map.insert(std::make_pair<int,InputCode>(userCode,inputCode));
    map2[userCode] = inputCode;
    
    
    if (map1.find(userCode) == map1.end())
    {
        map1[userCode] = inputCode;
    }
    
}

void InputControllerClass::removeControl(int userCode)
{
    //todo - should this be allowed?
    map1.erase(userCode);
}

void InputControllerClass::removeSecondControl(int userCode)
{
    map2.erase(userCode);
}

//TODO - need to test below methods:
int InputControllerClass::getValue(int userCode)  
{ 
    /*
    _DEBUG_ASSERTION(map.find(userCode)==map.end(),throw std::logic_error("InputControllerClass::get?(userCode)\tInvalid user code given."));
    
    auto range = map.equal_range (userCode);
    int value = 0;
    for (auto itr = range.first; itr != range.second; ++ itr)
    {
        value = std::max(getCodeValue(itr->second), value);
    }
    return value; 
    */
    
    // should add in debug assertion for codes not valid
    
    return getCodeValue(map1[userCode]) + getCodeValue(map2[userCode]);
}

int InputControllerClass::getFirstMin(int userCode)  
{ 
    return getCodeMin(map1[userCode]); 
}
int InputControllerClass::getFirstMax(int userCode)  
{ 
    return getCodeMax(map1[userCode]); 
}

bool InputControllerClass::isDown(int userCode)  
{ 
	return isCodeDown(map1[userCode]) || isCodeDown(map2[userCode]); 
}
bool InputControllerClass::isToggled(int userCode)  
{ 
    return isCodeToggled(map1[userCode]) || isCodeToggled(map2[userCode]);
}
bool InputControllerClass::isHit(int userCode)  
{ 
    return isCodeHit(map1[userCode]) || isCodeHit(map2[userCode]); 
}
bool InputControllerClass::isReleased (int userCode)  
{ 
    return isCodeReleased(map1[userCode]) || isCodeReleased(map2[userCode]); 
}
bool InputControllerClass::isHeldLongerThanTime (int userCode, unsigned int milliseconds)  
{
    return isCodeHeldLongerThanTime(map1[userCode], milliseconds) || isCodeHeldLongerThanTime(map2[userCode], milliseconds); 
}
bool InputControllerClass::isHeldLongerThanInput (int A, int B)  
{ 
    return isDown (A) && isDown (B) && getLastModified (A) < getLastModified (B);    
}
unsigned int InputControllerClass::getRest (int userCode)  
{ 
    unsigned int rest1 = getCodeRest(map1[userCode]);
    unsigned int rest2 = getCodeRest(map2[userCode]);
    // return the smaller rest value
    return rest1 < rest2? rest1 : rest2;
}
unsigned int InputControllerClass::getLastModified (int userCode) 
{ 
    unsigned int modified1 = getCodeLastModified(map1[userCode]); 
    unsigned int modified2 = getCodeLastModified(map2[userCode]); 
    // return newest i.e. larger last modified time.
    return modified1 > modified2? modified1 : modified2;
}
bool InputControllerClass::hasRead (int userCode)  
{ 
    return hasReadCode(map1[userCode]) || hasReadCode(map2[userCode]); 
}
bool InputControllerClass::hasJustModified (int userCode) 
{ 
    return hasJustModifiedCode(map1[userCode]) || hasJustModifiedCode(map2[userCode]); 
}

universal::InputCode InputControllerClass::getInputCode(int userCode)
{
    return map1[userCode];
}

universal::InputCode InputControllerClass::getSecondInputCode(int userCode)
{
    return map2[userCode];
}
    
///////////////////
// Normal get values

int InputControllerClass::getCodeValue(InputCode code) const
{
    return codeValues[code].value;
}

int InputControllerClass::getCodeMin(InputCode code) const
{
    return getInputCodeMin(code);
}

int InputControllerClass::getCodeMax(InputCode code) const
{
    return getInputCodeMax(code);
}


bool InputControllerClass::isCodeDown (InputCode code) const
{
	if (hasReadCode (code))
	{
		return codeValues[code].value;
	}

	return false;
}

bool InputControllerClass::isCodeToggled (InputCode code) const
{
	if (hasJustModifiedCode (code))
	{
		return codeValues[code].value != codeValues[code].previous;
	}

	return false;
}

bool InputControllerClass::isCodeHit (InputCode code) const
{
	return isCodeDown (code) && isCodeToggled (code);
}

bool InputControllerClass::isCodeReleased (InputCode code) const
{
	return (! isCodeDown (code)) && isCodeToggled (code);
}

bool InputControllerClass::isCodeHeldLongerThanTime (InputCode code, unsigned int milliseconds) const
{
	return isCodeDown (code) && getCodeRest (code) >= milliseconds;
}

bool InputControllerClass::isCodeHeldLongerThanCode (InputCode a, InputCode b) const
{
	return isCodeDown (a) && isCodeDown (b) && getCodeLastModified (a) < getCodeLastModified (b);
}

	
unsigned int InputControllerClass::getCodeRest (InputCode code) const
{
	return timeFunction() - getCodeLastModified (code);
}


unsigned int InputControllerClass::getCodeLastModified (InputCode code) const
{
	if (hasReadCode (code))
	{
		return codeValues[code].lastModified;
	}
	else
	{
		return 0;
	}
}


bool InputControllerClass::hasReadCode (InputCode code) const
{
	return codeValues.find (code) != codeValues.end ();
}

bool InputControllerClass::hasJustModifiedCode (InputCode code) const
{
	return find (recentlyModified.begin (), recentlyModified.end (), code) != recentlyModified.end ();
}




void InputControllerClass::prepareForInputCode (InputCode code)
{
	codeValues[code].previous = codeValues[code].value;
	codeValues[code].lastModified = timeFunction ();
	recentlyModified.push_front (code);
}



///////////

std::string InputControllerClass::getGamepadName(int id)const //_DEBUG std::invalid_argument
{
    if (id < 0 || static_cast<unsigned int>(id) > gamepads.size()) 
    {
        _DEBUG_RESPONSE(throw std::invalid_argument("InputControllerClass::getGamepadName::\tInvalid controller ID"));
        _RELEASE_RESPONSE(return "");
    }
        
    return gamepads[id]->getName();
}
int InputControllerClass::getGamepadAxesCount(int id)const //_DEBUG std::invalid_argument
{
    if (id < 0 || static_cast<unsigned int>(id) > gamepads.size())
    {
        _DEBUG_RESPONSE(throw std::invalid_argument("InputControllerClass::getGamepadAxesCount::\tInvalid controller ID"));
        _RELEASE_RESPONSE(return 0);
    }
      
        
    return gamepads[id]->getAxesCount();
}
int InputControllerClass::getGamepadBallCount(int id)const //_DEBUG std::invalid_argument
{
    if (id < 0 || static_cast<unsigned int>(id) > gamepads.size())
    {
        _DEBUG_RESPONSE(throw std::invalid_argument("InputControllerClass::getGamepadBallCount::\tInvalid controller ID"));
        _RELEASE_RESPONSE(return 0);
    }
        
    return gamepads[id]->getBallCount();
}
int InputControllerClass::getGamepadHatCount(int id)const //_DEBUG std::invalid_argument
{
    if (id < 0 || static_cast<unsigned int>(id) > gamepads.size())
    {
        _DEBUG_RESPONSE(throw std::invalid_argument("InputControllerClass::getGamepadHatCount::\tInvalid controller ID"));
        _RELEASE_RESPONSE(return 0);
    }
        
    return gamepads[id]->getHatCount();
}
int InputControllerClass::getGamepadButtonCount(int id)const //_DEBUG std::invalid_argument
{
    if (id < 0 || static_cast<unsigned int>(id) > gamepads.size())
     {
        _DEBUG_RESPONSE(throw std::invalid_argument("InputControllerClass::getGamepadButtonCount::\tInvalid controller ID"));
        _RELEASE_RESPONSE(return 0);
    }
        
    return gamepads[id]->getButtonCount();
}


void InputControllerClass::setKeyPress (InputCode code)
{
	prepareForInputCode (static_cast<InputCode>(code));
	codeValues[static_cast<InputCode>(code)].value = true;
}

void InputControllerClass::setKeyRelease (InputCode code)
{
	prepareForInputCode (static_cast<InputCode>(code));
	codeValues[static_cast<InputCode>(code)].value = false;
}


void InputControllerClass::setInputValue (InputCode code, int value)
{
    prepareForInputCode(code);
    codeValues[code].value = value;
}

// be careful setting values based on existing presses!
// one may be released and another not
void InputControllerClass::setValue (int userCode, int value)
{
    /*prepareForInputCode(map1[userCode]);
    prepareForInputCode(map2[userCode]);
    codeValues[map1[userCode]].value = value;
    codeValues[map2[userCode]].value = value;*/
    
    setInputValue(map1[userCode],value);
    setInputValue(map2[userCode],value);
}



#define MAX_HATS_FOREVER    10000

bool InputControllerClass::isolatesHatValues(const int id, const int hat)
{
    return isolatedHats[id*MAX_HATS_FOREVER+hat];
    /*
    auto itr = isolatedHats.find(id * MAX_HATS_FOREVER + hat);
    
    if(isolatedHats.end() == itr)
    {
        return false;
    }*/
}

void InputControllerClass::setIsolateHatValues(const int id, const int hat, const bool isolated)
{
    isolatedHats[id*MAX_HATS_FOREVER+hat] = isolated;
}

void InputControllerClass::clearAllIsolatedHatSettings()
{
    isolatedHats.clear();
}

////////////



InputControllerClass::CodeValue::CodeValue () :
	value (0),
	previous (0),
	lastModified (0)
{
	// nothing //
}

InputControllerClass::CodeValue::CodeValue (bool valueIn, bool previousIn, unsigned int lastModifiedIn) :
	value (valueIn),
	previous (previousIn),
	lastModified (lastModifiedIn)
{
	// nothing //
}





}		//	input
}		//	aab





