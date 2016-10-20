
/*
*
*	input_controller.hpp
*
**/

#if !defined(AAB_INPUT_CONTROLLER_CLASS)
#define AAB_INPUT_CONTROLLER_CLASS
#include"input_codes.hpp"
#include"../types/smart_ptr.hpp"
#include"../types/manager.hpp"
//#include"../events/keyboard_handler.hpp"
//#include"../events/gamepad_port_handler.hpp"
#include"../events/multi_event_handler.hpp"
//#include"../events/key_event.hpp"
//#include"keyboard.hpp" // move event receiver out to somewhere else.
#include"hat_position.hpp"
#include"key_codes.hpp"
#include"gamepad_values.hpp"
#include"gamepad.hpp"
#include<map>
#include<vector>
#include<unordered_map>
namespace aab	{
namespace input	{


class DefaultingInputCode
{
    typedef aab::input::universal::InputCode InputCode;
    InputCode value;
    
    public:
    
    DefaultingInputCode():value(aab::input::universal::invalid_input_code)
    {
        //nothing //
    }
    
    operator InputCode&()
    {
        return value;
    }
    
    operator InputCode()const
    {
        return value;
    }
    
    DefaultingInputCode& operator=(InputCode other)
    {
        value = other;
        return *this;
    }
};




class InputControllerClass //: public aab::types::Manager <InputControllerClass>
//: public KeyEventReceiverClass,
//  public virtual aab::events::GamepadPortHandler
: public aab::events::MultiEventHandler
{
	public:

	typedef aab::types::Smart <InputControllerClass>::Ptr Ptr;
	typedef universal::InputCode InputCode;
	//typedef GamepadAxisValue;

	private:

		class PressedEventHandler;
		class ReleasedEventHandler;
		class FocusGainedHandler;
		class FocusLostHandler;
		class ICGamepadHandler;
		class ICMouseHandler;
		//aab::events::GamepadsAutoHandler::Ptr gamepadsHandler;
		std::vector<Gamepad> gamepads; // these are created for the purposes of opening the gamepads, but they are not kepy up to date event wise. Instead, the codeValues are given the gamepads values.
		input::GamepadPorts gamepadPorts;		
        //typedef aab::events::EventData EventData;        
        
		typedef unsigned int (* TimeFunction)(void);		

		class CodeValue
		{
			public:

			int value;
			int previous;
			unsigned int lastModified;

			explicit CodeValue ();
			explicit CodeValue (bool value, bool prev, unsigned int lastModified);

		};
		     
        struct DBool
        {
            bool value;

            DBool():value(false)
            {
                // nothing //
            }
            
            operator bool()const
            {
                return value;
            }
            
            DBool & operator=(const bool b)
            {
                value = b;
                return *this;
            }
        };

		TimeFunction timeFunction;
		mutable
		std::map <InputCode, CodeValue> codeValues; // change to an unordered_map for constant results
		std::list <InputCode> recentlyModified; // change to forward_list? Or would it be better to use a reserved vector=> less allocations.
        float defaultAxisClip; //for axis left, right, up, down, a cut off is needed.
        std::map<InputCode, int> axisClips; // custom cutoff for individual InputCodes relating to gamepads
		InputControllerClass(InputControllerClass&);
        std::map<int, DBool> isolatedHats;
		void prepareForInputCode (InputCode);
		



	protected:

		//friend class aab::types::Manager <InputControllerClass>::Deleter;
		friend Ptr makeInputController (InputConnector::Ptr);
		explicit InputControllerClass (InputConnector::Ptr); //aab::test::already_instantiated_error, GamepadUnavailableException, NoGamepadsException, FailedToOpenGamepadException
		
        
        //typedef std::multimap<int, InputCode> CodeMapping; // investigate making this an unordered_multimap for constant rather than logarithmic resolution
        
        // Need to use a code that defaults to zero so that map requests for something that hasn't been assigned evaluate to no input given so far.
        // Commands using "time since X" etc will look at the most recent update to an input control code.
        typedef std::unordered_map<int, DefaultingInputCode> CodeMapping;
        
        //mutable
        CodeMapping map1; // used to map userCodes to InputCodes
        CodeMapping map2; // used to map secondary codes
        
	public:
	
	virtual ~InputControllerClass () throw ();


	void update (); // call every frame - updates state for things such as isKeyHit and isKeyToggled

    // call one of these each frame after polling for events in order to calibrate gamepad axes
    // assumes axis 0 is X and axis 1 is Y
    ////because the input doesn't happen every frame, this does not work properly.
    ///TODO - fix these to work or be allowed run only after a set of paired gamepad
    ///updates
    /*
    void axialDeadZoneXYAxes(int pad, int deadzone, int maximum = gamepad_axis_max)
    {
        axialDeadZoneAxes(pad, deadzone, 0, 1, maximum);
    }
    void radialDeadZoneXYAxes(int pad, float deadzone, int maximum = gamepad_axis_max)
    {
        radialDeadZoneAxes(pad, deadzone, 0, 1, maximum);
    }
    void axialDeadZoneAxes(int pad, int deadzone, int xAxis, int yAxis, int maximum = gamepad_axis_max); // number between 0 and gamepad_axis_max
    void radialDeadZoneAxes(int pad, float deadzone, int xAxis, int yAxis, int maximum = gamepad_axis_max);
    */
    
    int getAxisClip(const InputCode)const;
    void setDefaultAxisClip(const int axisDirectionCutoffIn){ defaultAxisClip = axisDirectionCutoffIn; }
    // use custom axis clip on individual axis, e.g. universal::gamepadAxisCode(id,axis)
    void setCustomAxisClip(const InputCode, const int axisDirectionCutoffIn); // make axis clips positive even for negative axis InputCodes: the absolute value is checked.
    
    // utility which determines inpuitcode for you:
    void setCustomAxisClip(const int id, const int axis, const int cutoff);
    void removeCustomAxisClip(const InputCode);
    void removeCustomAxisClip(const int id, const int axis);
    bool hasCustomAxisClip(const InputCode);
    bool hasCustomAxisClip(const int id, const int axis);
    void clearCustomAxisClipping()
    {
        axisClips.clear();
    }
    
    void setControl(int userCode, InputCode inputCode);
    void setSecondControl(int userCode, InputCode inputCode);
    void removeControl(int userCode);
    void removeSecondControl(int userCode);
    
    
    bool isolatesHatValues(const int id, const int hat); // returns true if hat codes have been set to be isolated. Defaults to false.
    void setIsolateHatValues(const int id, const int hat, const bool isolated);
    void clearAllIsolatedHatSettings();
        
    /*
    #ifdef _DEBUG
        int getValue(int userCode) { return getCodeValue(map.at(userCode)); }
        int getMin(int userCode)  { return getCodeMin(map.at(userCode)); }
        int getMax(int userCode)  { return getCodeMax(map.at(userCode)); }
        bool isDown(int userCode)  { return isCodeDown(map.at(userCode)); }
        bool isToggled(int userCode)  { return isCodeToggled(map.at(userCode)); }
        bool isHit(int userCode)  { return isCodeHit(map.at(userCode)); }
        bool isReleased (int userCode)  { return isCodeReleased(map.at(userCode)); }
        bool isHeldLongerThan (int userCode, unsigned int milliseconds)  { return isCodeHeldLongerThan(map.at(userCode), milliseconds); }
        bool isHeldLongerThan (int A, int B)  { return isCodeHeldLongerThan(map.at(A),map.at(B)); }
        unsigned int getRest (int userCode) { return getCodeRest(map.at(userCode)); }
        unsigned int getLastModified (int userCode)  { return getCodeLastModified(map.at(userCode)); }
        bool hasRead (int userCode)  { return  hasReadCode(map.at(userCode)); }
        bool hasJustModified (int userCode)  { return hasJustModifiedCode(map.at(userCode)); }
    #else
        int getValue(int userCode)  { return getCodeValue(map[userCode]); }
        int getMin(int userCode)  { return getCodeMin(map[userCode]); }
        int getMax(int userCode)  { return getCodeMax(map[userCode]); }
        bool isDown(int userCode)  { return isCodeDown(map[userCode]); }
        bool isToggled(int userCode)  { return isCodeToggled(map[userCode]); }
        bool isHit(int userCode)  { return isCodeHit(map[userCode]); }
        bool isReleased (int userCode)  { return isCodeReleased(map[userCode]); }
        bool isHeldLongerThan (int userCode, unsigned int milliseconds)  { return isCodeHeldLongerThan(map[userCode], milliseconds); }
        bool isHeldLongerThan (int A, int B)  { return isCodeHeldLongerThan(map[A],map[B]); }
        unsigned int getRest (int userCode)  { return getCodeRest(map[userCode]); }
        unsigned int getLastModified (int userCode)  { return getCodeLastModified(map[userCode]); }
        bool hasRead (int userCode)  { return  hasReadCode(map[userCode]); }
        bool hasJustModified (int userCode)  { return hasJustModifiedCode(map[userCode]); }
	#endif
	*/
	
	// If multiple input controls (InputCode) are mapped to the one userCode using addControl(), then the 
	// largest value from both will be returned. For keys, this will mean "true" will trump "false"
	// for joysticks, this behaviour is not useful (an average would be better
 
    int getValue(int userCode);
    int getFirstMin(int userCode);
    int getFirstMax(int userCode);
    bool isDown(int userCode);
    bool isToggled(int userCode);
    bool isHit(int userCode);
    bool isReleased (int userCode);
    bool isHeldLongerThanTime (int userCode, unsigned int milliseconds);
    bool isHeldLongerThanInput (int A, int B);
    unsigned int getRest (int userCode);
    unsigned int getLastModified (int userCode);
    bool hasRead (int userCode);
    bool hasJustModified (int userCode);
    
    InputCode getInputCode(int userCode);
    InputCode getSecondInputCode(int userCode);
        
        
	int getCodeValue(InputCode) const;
	int getCodeMin(InputCode) const;
	int getCodeMax(InputCode) const;
	bool isCodeDown(InputCode) const;  // does not make sense for all codes - may be true all the time for analogue stick for example, which has small values even when at rest
	bool isCodeToggled(InputCode) const; // does not make sense for all codes
	bool isCodeHit(InputCode) const; // does not make sense for all codes
	bool isCodeReleased (InputCode) const; // does not make sense for all codes
	bool isCodeHeldLongerThanTime (InputCode, unsigned int milliseconds) const; // does not make sense for all codes
	bool isCodeHeldLongerThanCode (InputCode, InputCode) const;// does not make sense for all codes
	unsigned int getCodeRest (InputCode) const;
	unsigned int getCodeLastModified (InputCode) const;
	bool hasReadCode (InputCode) const;
	bool hasJustModifiedCode (InputCode) const;
	
	bool isKeyDown (InputCode code) const { return isCodeDown(code); }; // is key being held down
	bool isKeyToggled (InputCode code) const { return isCodeToggled(code); }; // has key been changed since previous frame
	bool isKeyHit (InputCode code) const { return isCodeHit(code); }; // is key now down but wasn't last frame
	bool isKeyReleased (InputCode code) const{ return isCodeReleased(code); }; // is key up now but was down last frame
	bool isKeyHeldLongerThanTime (InputCode code, unsigned int milliseconds) const { return isCodeHeldLongerThanTime(code, milliseconds); }; // time depends on the TimeFunction
	bool isKeyHeldLongerThanCode (InputCode a, InputCode b) const { return isCodeHeldLongerThanCode(a,b); };
	
	inline bool isMouseButtonDown(int button) { return getCodeValue(universal::mouseButtonCode(button)); }
    inline int getMouseX() { return getCodeValue(universal::mouse_x); }
    inline int getMouseY() { return getCodeValue(universal::mouse_y); }
    
    inline bool isGamepadButtonDown(int pad, int button) { return getCodeValue(universal::gamepadButtonCode(pad, button)); }
    inline int getXaxis(int pad) { return getCodeValue(universal::gamepadAxisCode(pad,0)); }
    inline int getYaxis(int pad) { return getCodeValue(universal::gamepadAxisCode(pad,1)); }
    inline int getBallX(int pad, int ball = 0) { return getCodeValue(universal::gamepadBallXCode(pad, ball)); }
    inline int getBallY(int pad, int ball = 0) { return getCodeValue(universal::gamepadBallYCode(pad, ball)); }
    inline int getHat(int pad, int hat = 0) { return getCodeValue(universal::gamepadHatCode(pad, hat)); } 
    inline int getHatX(int pad, int hat = 0) { return getCodeValue(universal::gamepadHatXCode(pad, hat)); }
    inline int getHatY(int pad, int hat = 0) { return getCodeValue(universal::gamepadHatYCode(pad, hat)); }
    

    int countGamepads(){ return gamepadPorts->countGamepads(); }
    std::string getGamepadName(int id)const; //_DEBUG std::invalid_argument
    int getGamepadAxesCount(int id)const; //_DEBUG std::invalid_argument
    int getGamepadBallCount(int id)const; //_DEBUG std::invalid_argument 
    int getGamepadHatCount(int id)const; //_DEBUG std::invalid_argument
    int getGamepadButtonCount(int id)const; //_DEBUG std::invalid_argument



	/*
	virtual void buttonPressed (int id, int button);
	virtual void buttonReleased (int id, int button);
	virtual void axisMove (int id, int axis, GamepadAxisValue);
	virtual void ballMove (int id, int ball, GamepadAxisValue x, GamepadAxisValue y);
	virtual void hatMove (int id, int hat, HatPosition);
	*/
	
	virtual void keyboardFocusGained() { }
	virtual void keyboardFocusLost() { }
	
	
    // used by event handlers to set the values for the input controller.
    // must register into several different event handlers.
	virtual void setKeyPress (InputCode);
	virtual void setKeyRelease (InputCode);	
	
	void setInputValue (InputCode, int value);
	void setValue (int userCode, int value);
	
	
	
};

typedef InputControllerClass::Ptr InputController;

InputController makeInputController (InputConnector::Ptr);




}		//	input
}		//	aab
#endif	//	AAB_INPUT_CONTROLLER_CLASS




