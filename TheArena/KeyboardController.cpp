#include "KeyboardController.h"
#include <conio.h>

// MAX_KEYVALUE is define in KeyboardState.h

namespace Zaxis{ namespace Controllers
{

	KeyboardController::KeyboardController()
	{
		_log = new Zaxis::Logging::NullLogger();
		keyIn = 0;
		currState = NULL;
	}


	KeyboardController::~KeyboardController()
	{
	}

	void KeyboardController::Update()
	{
		// Need to check the key state and save it in the list
		KeyboardState* state = new KeyboardState();
		for (int i = 0; i < MAX_KEYVALUE; i++)
		{
			state->keys[i] = KEY_DOWN(i);
		}// End for loop key state update

		// Add state to the list
		keyState.push_back(state);
		if (currState == NULL)
		{
			currState = keyState.front();
		}// Endif currState is not assigned
	}

	bool KeyboardController::Shutdown()
	{
		// Controller shouldn't shutdown game engine during the update process
		return false;
	}

	bool KeyboardController::ChkInput(int vk)
	{
		bool bRetVal = false;
		if (vk < MAX_KEYVALUE)
		{
			if (currState != NULL)
			{
				bRetVal = currState->keys[vk];
			}
			else
			{
				bRetVal = KEY_DOWN(vk);
			}// Endif currState is defined check
		}// Endif vk is less than max key value

		return bRetVal;
	}

	char KeyboardController::GetInput()
	{
		return 0;
	}

	int KeyboardController::Count()
	{
		return keyState.size();
	}

	void KeyboardController::PopState()
	{
		KeyboardState* state = keyState.front();
		keyState.pop_front();
		if (keyState.size() > 0)
		{
			currState = keyState.front();
		}
		else
		{
			currState = NULL;
		}

		delete state;
	}

	void KeyboardController::FlushStates()
	{
		while (keyState.size() > 0)
		{
			KeyboardState* state = keyState.front();
			keyState.pop_front();
			delete state;
		}
	}

	void KeyboardController::SetLog(LPLOGGER log)
	{
		_log = log;
	}

	LPLOGGER KeyboardController::Log()
	{
		return _log;
	}

	LPLOGGER KeyboardController::Log(const std::string &line)
	{
		Log()->WriteLine(line);
		return Log();
	}

} }// End namespace Zaxis::Controllers

