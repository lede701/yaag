#ifndef H_KEYBOARDCONTROLLER
#define H_KEYBOARDCONTROLLER

#include <list>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include "IController.h"
#include "IStateManager.h"
#include "IUpdater.h"
#include "NullLogger.h"
#include "KeyboardState.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

namespace Zaxis{ namespace Controllers
{

	class KeyboardController :
		public IController, public IStateManager, public Zaxis::Engine::IUpdater
	{
	private:
		char keyIn;
		std::list<KeyboardState*> keyState;
		KeyboardState* currState;
		LPLOGGER _log;

	public:
		KeyboardController();
		virtual ~KeyboardController();

		virtual bool ChkInput(int key);
		virtual char GetInput();

		virtual void Update();
		virtual bool Shutdown();

		virtual int Count(); // Number of keyboard states in buffer
		virtual void PopState(); // remove current state from list
		virtual void FlushStates(); // Clear input buffer

		// Logging support for this controller
		virtual void SetLog(LPLOGGER log);
		virtual LPLOGGER Log();
		virtual LPLOGGER Log(const std::string &line);
	};


} }// End namespace Zaxis::Controllers

#endif