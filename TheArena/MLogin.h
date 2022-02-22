#ifndef H_MLOGIN
#define H_MLOGIN

#include "ILogin.h"
#include "IData.h"
#include "BaseSelector.h"
#include "IMenuState.h"
#include "PlayerEntity.h"
#include "ConGraphics.h"
#include "zmath.h"
#include "PlayerData.h"
#include "DataLocation.h"

#include <time.h>

namespace Game{ namespace Graphics{ namespace Menus
{
	using Zaxis::Data::DataLocation;

	class MLogin
		: public BaseSelector
	{
	private:
		Zaxis::Math::Rect box;

		bool _isRunning;
		bool _isDirty;

		// Login color scheme
		WORD textColor;
		WORD cmdColor;
		WORD boxColor;
		WORD inputColor;
		WORD errorColor;

		enum LoginState
		{
			LS_WELCOME,
			LS_LOGIN,
			LS_SELECT_PLAYER,
			LS_SUCCESSLOGIN,
			LS_FAILEDLOGIN,
			LS_COMMAND,
			LS_HELP,
			LS_CREATE,
			LS_CREATE_NEW,
			LS_NAMEEXISTS,
			LS_LIST,
			LS_QUIT
		};

		LoginState state;

		LPCONTROLLER _controller;
		LPMENUSTATE _stateManager;
		LPLOGIN _loginCtrl;

		Game::Data::PlayerData* _playerData;

		int playerId;
		int failedAttempts;

		std::string loginMessage;

	public:
		MLogin(int x, int y);
		virtual ~MLogin();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();

		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual void SetStateManager(LPMENUSTATE manager);
		virtual void SetController(LPCONTROLLER ctrl);
		virtual void SetLoginController(LPLOGIN login);

		// State draw methods
		virtual void DrawCreate(Zaxis::Graphics::ConGraphics* cGfx);
		virtual void DrawCommand(Zaxis::Graphics::ConGraphics* cGfx);
		virtual void DrawWelcome(Zaxis::Graphics::ConGraphics* cGfx);
		virtual void DrawLogin(Zaxis::Graphics::ConGraphics* cGfx);
		virtual void DrawSelectPlayer(Zaxis::Graphics::ConGraphics* cGfx);
		virtual void DrawHelp(Zaxis::Graphics::ConGraphics* cGfx);

	};

} } }// End namespace Game::Graphics::Menus
#endif