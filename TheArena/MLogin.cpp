#include "MLogin.h"
#include "GetInput.h"
#include "gamedefs.h"
#include "NullController.h"
#include "FileData.h"
#include "PlayerData.h"
#include "FileIO.h"
#include "StrToHash.h"
#include "PlayerCreator.h"
#include "fLogin.h"

#include "languagepack.h"

#include <iomanip>

#define MLOGIN_COLOR Zaxis::Graphics::ConColor::BkgRed | Zaxis::Graphics::ConColor::LtYellow
#define MLOGIN_SELECTED Zaxis::Graphics::ConColor::BkgBlue | Zaxis::Graphics::ConColor::LtYellow

namespace Game{ namespace Graphics{ namespace Menus
{
	using Zaxis::Graphics::ConGraphicsData::ConColor;

	MLogin::MLogin(int x, int y)
		: BaseSelector(MLOGIN_COLOR, MLOGIN_SELECTED, 30)
	{
		// Setup login menu
		_isRunning = true;
		_isDirty = true;
		box = { x, y, 60, 15 };
		// Set menu initial state
		state = LS_WELCOME;
		// Create a null controller until a real one is passed in
		_controller = new Zaxis::Controllers::NullController();

		// Set menu colors
		boxColor = ConColor::BkgRed | ConColor::LtYellow;
		textColor = ConColor::BkgRed | ConColor::White;
		cmdColor = ConColor::BkgRed | ConColor::LtGreen;
		inputColor = ConColor::BkgRed | ConColor::LtYellow;
		errorColor = ConColor::BkgLtYellow | ConColor::LtRed;

		// Reset failed login attempts
		failedAttempts = 0;
		_playerData = new Game::Data::PlayerData();
	}

	MLogin::~MLogin()
	{
		if (_loginCtrl != NULL)
		{
			delete _loginCtrl;
			_loginCtrl = NULL;
		}
	}

	void MLogin::Draw(LPGRAPHICS gfx)
	{
		// Get quick access to BoxType
		using Zaxis::Graphics::ConGraphicsData::BoxType;
		// Cast graphic controller to ConGraphics
		Zaxis::Graphics::ConGraphics* cGfx = CONCAST(gfx);
		// Draw box for login process
		cGfx->DrawFillRect(&box, BoxType::Antique, boxColor);

		// Check if there ils a login message
		if (loginMessage.length() > 0)
		{
			// Draw login error message
			cGfx->DrawText(loginMessage, box.X + 3, box.Y + 1, errorColor);
			loginMessage = "";
		}

		switch (state)
		{
		case LS_WELCOME:
			DrawWelcome(cGfx);
			break;
		case LS_LOGIN:
			DrawLogin(cGfx);
			break;
		case LS_SELECT_PLAYER:
			DrawSelectPlayer(cGfx);
			break;
		case LS_CREATE:
			DrawCreate(cGfx);
			break;
		case LS_COMMAND:
			DrawCommand(cGfx);
			break;
		}

		_isDirty = false;
	}

	void MLogin::DrawCreate(Zaxis::Graphics::ConGraphics* cGfx)
	{
		int x = box.X + 3;
		int y = box.Y + 6;

		WORD conColor = cGfx->GetTextColor();

		std::ostringstream out;
		out << CREATEPLAYERNAMEPROMPT;
		cGfx->DrawText(out.str(), x, y, textColor);
		cGfx->SetPos(x + out.str().length() + 1, y++);
		cGfx->SetTextColor(inputColor);
		out.str(""); out.clear();
		// Flush keyboard input
		cGfx->Flush();
		// Get player name
		std::string playerName = GetInput(false);
		// Check if name is already in use
		if (!_loginCtrl->UniqueName(playerName))
		{
			loginMessage = ERROR_ACCOUNTEXISTS;
			state = LS_NAMEEXISTS;
			return;
		}

		// Get the user password
		std::string passwd;
		std::string confirm;
		// Check if we need to create password with this login controller
		if (_loginCtrl->CreatePassword())
		{
			int srcY = y;
			do
			{
				y = srcY;
				out << PASSWORDPROMPT;
				cGfx->DrawText(out.str(), x, y, textColor);
				cGfx->SetTextColor(inputColor);
				cGfx->SetPos(x + out.str().length() + 1, y++);
				out.str(""); out.clear();
				passwd = GetInput(true);

				out << PASSWORDPROMPT;
				cGfx->DrawText(out.str(), x, y, textColor);
				cGfx->SetTextColor(inputColor);
				cGfx->SetPos(x + out.str().length() + 1, y++);
				out.str(""); out.clear();
				confirm = GetInput(true);
				if (passwd != confirm)
				{
					cGfx->DrawText(ERROR_CONFIRM, x, box.Y + 1, errorColor);
				}
			} while (passwd != confirm);
		}// Endif CreatePassword
		
		_loginCtrl->CreatePlayer(playerName, passwd);
		_loginCtrl->GetData(_playerData, sizeof(Game::Data::PlayerData));
		state = LS_SUCCESSLOGIN;
		//*/
		// Reset console text color
		cGfx->SetTextColor(conColor);
	}

	void MLogin::DrawCommand(Zaxis::Graphics::ConGraphics* cGfx)
	{

	}

	void MLogin::DrawWelcome(Zaxis::Graphics::ConGraphics* cGfx)
	{
		int x = box.X + 3;
		int y = box.Y + box.Height - 8;

		// Login command
		DrawCmd(cGfx, LM_LOGINKEY, LM_LOGINTEXT, x, y++, textColor, cmdColor);

		// Create new player
		DrawCmd(cGfx, LM_CREATEKEY, LM_CREATETEXT, x, y++, textColor, cmdColor);

		// List player in database
		DrawCmd(cGfx, LM_LISTKEY, LM_LISTTEXT, x, y++, textColor, cmdColor);

		// Configuratiom command
		DrawCmd(cGfx, LM_CONFIGKEY, LM_CONFIGTEXT, x, y++, textColor, cmdColor);

		// Help command
		DrawCmd(cGfx, LM_HELPKEY, LM_HELPTEXT, x, y++, textColor, cmdColor);

		// Quit/Exit game
		DrawCmd(cGfx, LM_QUITKEY, LM_QUITTEXT, x, y++, textColor, cmdColor);
	}

	void MLogin::DrawLogin(Zaxis::Graphics::ConGraphics* cGfx)
	{
		int x = box.X + 3;
		int y = box.Y + 5;

		cGfx->SetConCursor(true);

		std::ostringstream out;
		out << PLAYERNAMEPROMPT;
		cGfx->DrawText(out.str(), x, y, textColor);
		x += out.str().length() + 1;
		out.str(""); out.clear();
		cGfx->SetPos(x, y++);

		// Flush the keyboard input
		cGfx->Flush();
		cGfx->SetTextColor(inputColor);
		std::string name = GetInput(false);

		out << PASSWORDPROMPT;
		x = box.X + 3;
		cGfx->DrawText(out.str(), x, y, textColor);
		x += out.str().length() + 1;
		out.str(""); out.clear();
		cGfx->SetPos(x, y++);

		cGfx->SetTextColor(inputColor);
		std::string passwd = GetInput(true);
		cGfx->SetConCursor(false);
		Zaxis::Network::ILogin::LoginMessage msg = _loginCtrl->Login(name, passwd);
		if (msg == Zaxis::Network::ILogin::LM_OK)
		{
			state = LS_SUCCESSLOGIN;
			// Load player data from the login process
			_loginCtrl->GetData(_playerData, sizeof(Game::Data::PlayerData));
			return;
		}
		else if (msg == Zaxis::Network::ILogin::LM_NEW)
		{
			state = LS_CREATE_NEW;
			return;
		}

		state = LS_FAILEDLOGIN;
	}

	void MLogin::DrawSelectPlayer(Zaxis::Graphics::ConGraphics* cGfx)
	{

	}

	void MLogin::DrawHelp(Zaxis::Graphics::ConGraphics* cGfx)
	{

	}

	void MLogin::Clear(LPGRAPHICS gfx)
	{
		Zaxis::Graphics::ConGraphics* cGfx = CONCAST(gfx);
		UCHAR c = 32;
		cGfx->DrawRect(&box, &c, &c);
	}

	void MLogin::Update()
	{
		LoginState prevState = state;
		switch (state)
		{
		case LS_WELCOME:
			{
				if (_controller->ChkInput(LM_LOGINKEY))
				{
					state = LS_LOGIN;
				}
				if (_controller->ChkInput(LM_CREATEKEY))
				{
					state = LS_CREATE;
				}
				if (_controller->ChkInput(LM_LISTKEY))
				{
					_stateManager->PushState(Game::Graphics::Menus::MenuState::MS_PLAYERLIST);
				}
				if (_controller->ChkInput(LM_CONFIGKEY))
				{
					// Add config layer to graphic stack
					_stateManager->PushState(Game::Graphics::Menus::MenuState::MS_CONFIG);
				}

				// Administrative feature
				/*
				if (_controller->ChkInput('C'))
				{
					state = LS_COMMAND;
				}
				//*/
			}
			break;
		case LS_SUCCESSLOGIN:
			{
				_stateManager->LoadPlayer(_playerData);
				// TODO: Change this back to MS_HOME once the home screen is developed
				_stateManager->PushState(Game::Graphics::Menus::MenuState::MS_HOME);
				// Reset the state back to the welcome
				state = LS_WELCOME;
			}
			break;
		case LS_FAILEDLOGIN:
			{
				failedAttempts++;
				if (failedAttempts > 4)
				{
					// Change this state to Goodbye for failure to login
					_stateManager->PushState(Game::Graphics::Menus::MenuState::MS_EXIT);
				}
				state = LS_WELCOME;
				loginMessage = "Invalid user or password";
			}
			break;
		case LS_CREATE_NEW:
			{
				state = LS_CREATE;
			}
			break;
		case LS_CREATE:
			{
			}
			break;
		case LS_NAMEEXISTS:
			{
				state = LS_CREATE;
			}
			break;
		default:
			{
				loginMessage = "";
			}
			break;
		}

		if (_controller->ChkInput(VK_ESCAPE) || _controller->ChkInput(LM_QUITKEY) || _controller->ChkInput(EXITKEY))
		{
			// Set game to exit
			_stateManager->PushState(Game::Graphics::Menus::MenuState::MS_EXIT);
			// Remove me off the stack
			_stateManager->PopState();
			return;
		}

		_isDirty = prevState != state || _isDirty;
	}
	
	bool MLogin::Shutdown()
	{
		return !_isRunning;
	}

	bool MLogin::IsDirty()
	{
		return _isDirty;
	}

	void MLogin::DirtyMe()
	{
		_isDirty = true;
	}

	void MLogin::SetStateManager(LPMENUSTATE manager)
	{
		_stateManager = manager;
	}

	void MLogin::SetController(LPCONTROLLER ctrl)
	{
		_controller = ctrl;
	}

	void MLogin::SetLoginController(LPLOGIN login)
	{
		_loginCtrl = login;
	}


} } }// End namespace Game::Graphics::Menus