#ifndef JOYSTICKBUTTON_H
#define JOYSTICKBUTTON_H

#include "JoystickWrapper.h"
#include "Robot.h"

#define CALL_OBJECT_FUNC(member) (object->*(member))

template <class T>
class JoystickCallback
{
public:
	typedef void (T::*ObjectFuncPtr)(void);

	JoystickCallback(JoystickWrapper* joystick, T *object) :
		jwrapper(joystick),object(object)
		{
			this->buttonCount = 12;
			this->downCallback = new ObjectFuncPtr[buttonCount];
			this->heldCallback = new ObjectFuncPtr[buttonCount];
			this->upCallback = new ObjectFuncPtr[buttonCount];
			this->buttonStates = new bool[buttonCount];
			for( int i = 0; i < buttonCount; i++ )
			{
				this->downCallback[i] = 0;
				this->heldCallback[i] = 0;
				this->upCallback[i] = 0;
				this->buttonStates[i] = joystick->GetJoystick()->GetRawButton(i);
			}
		}

	~JoystickCallback()
	{
		printf("Woe is the Joystick Callback!\n");

		delete [] this->downCallback;
		delete [] this->heldCallback;
		delete [] this->upCallback;
		delete [] this->buttonStates;
	}

	void SetDownCallback(int button, ObjectFuncPtr fptr)
	{
		this->downCallback[button] = fptr;
	}

	void SetHeldCallback(int button, ObjectFuncPtr fptr)
	{
		this->heldCallback[button] = fptr;
	}

	void SetTriggerDownCallback( ObjectFuncPtr fptr )
	{
		this->downCallback[1] = fptr;
	}
	
	void SetUpCallback(int button, ObjectFuncPtr fptr)
	{
		this->upCallback[button] = fptr;
	}

	void UnbindAll() {
		for( int i = 0; i < buttonCount; i++ )
		{
			this->downCallback[i] = 0;
			this->heldCallback[i] = 0;
			this->upCallback[i] = 0;
		}
	}

	void Update()
	{
		// deal with the buttons
		for( int i = 0; i < buttonCount; i++ )
		{
			bool previousState = this->buttonStates[i];
			this->buttonStates[i] = jwrapper->GetJoystick()->GetRawButton(i);
			if( previousState != this->buttonStates[i] )
			{
				if( previousState ) // was down and is now up
                {
					if(upCallback[i] == NULL) continue;
					CALL_OBJECT_FUNC(upCallback[i])();
				} 
                else // was up now is down
                {
					if(downCallback[i] == NULL) continue;
					CALL_OBJECT_FUNC(downCallback[i])();
				}
			}
			else if( previousState == 1 && this->buttonStates[i] == 1 )
			{
				if(heldCallback[i] == NULL) continue;
				CALL_OBJECT_FUNC(heldCallback[i])();
			}
		}
	}


private:
	JoystickWrapper* jwrapper;
	T *object;
	ObjectFuncPtr* downCallback;
	ObjectFuncPtr* heldCallback;
	ObjectFuncPtr* upCallback;
	bool* buttonStates;
	int buttonCount;
};

#endif // JOYSTICKBUTTON_H
