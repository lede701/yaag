#include "MConfig.h"
#include "languagepack.h"
#include "gamedefs.h"
#include "fLogin.h"

#define CFG_COLOR Zaxis::Graphics::ConColor::BkgBlue | Zaxis::Graphics::ConColor::White
#define CFG_HIGHLIGHT Zaxis::Graphics::ConColor::BkgPurple | Zaxis::Graphics::ConColor::LtYellow
#define CFG_COMMANDCOLOR Zaxis::Graphics::ConColor::BkgBlue | Zaxis::Graphics::ConColor::LtGreen


namespace Game{ namespace Graphics{ namespace Menus
{
	MConfig::MConfig(int x, int y) : BaseSelector(CFG_COLOR, CFG_HIGHLIGHT, 25)
	{
		_box = { x, y, 30, 12 };
		txtColor = CFG_COLOR;
		highColor = CFG_HIGHLIGHT;
		cmdColor = CFG_COMMANDCOLOR;
		boxColor = Zaxis::Graphics::ConColor::BkgBlue | Zaxis::Graphics::ConColor::LtBlue;
		_isDirty = true;
		_loginCtrl = NULL;
		_dataCtrl = NULL;
		_loginDb = DataLocation::DL_LOCAL;
		_gameDb = DataLocation::DL_GAMEJOLT;
	}

	MConfig::~MConfig()
	{

	}

	void MConfig::InitControllers()
	{
		bool createLogin = false;
		bool createData = false;

		if (_loginCtrl == NULL)
		{
			// Create a default controller
			createLogin = true;
		}
		else if (_loginCtrl->GetLocation() != _loginDb)
		{
			// Clean up my memory mess
			delete _loginCtrl;
			_loginCtrl = NULL;
			createLogin = true;
		}// Endif _loginCtrl is null

		if (_dataCtrl == NULL)
		{
			createData = true;
		}
		else if (_dataCtrl->GetLocation() != _gameDb)
		{
			// Clean up my memory mess
			delete _dataCtrl;
			_dataCtrl = NULL;
			createData = true;
		}// Endif _dataCtrl is null

		if (_dataCtrl == NULL)
		{
			Game::File::FLogin *dCtrl = new Game::File::FLogin();
			dCtrl->Init();
			_dataCtrl = dCtrl;
			_stateManager->SetDataController(_dataCtrl);
		}

		// Check if we need to create the login controller
		if (createLogin)
		{
			// Which login controller do we need to create
			switch (_loginDb)
			{
			case Data::DataLocation::DL_ZAXIS:
				// Stub for my network API
				break;
			default:
				{
					// Create a file controller
					Game::File::FLogin *lCtrl = new Game::File::FLogin();
					lCtrl->Init();
					_loginCtrl = lCtrl;
				}
				break;
			}
			// Send login controller to state controller
			_stateManager->SetLoginController(_loginCtrl);
		}// Endif createLogin flag is true

		// Check if we need to create the data controller
		if (createData)
		{
			// Which login controller do we need to create
			switch (_gameDb)
			{
			case Data::DataLocation::DL_ZAXIS:
				// Stub for my network API
				break;
			default:
			{
				// Create a file controller
				Game::File::FLogin *dCtrl = new Game::File::FLogin();
				dCtrl->Init();
				_dataCtrl = dCtrl;
			}
			break;
			}
			// Send data controller to state controller
			_stateManager->SetDataController(_dataCtrl);
		}// Endif createData flag is true
	}

	void MConfig::Draw(LPGRAPHICS gfx)
	{
		Zaxis::Graphics::ConGraphics *cGfx = CONCAST(gfx);
		using Zaxis::Graphics::ConGraphicsData::BoxType;

		cGfx->DrawFillRect(&_box, BoxType::Antique, boxColor);
		DrawTitle(cGfx, CFG_TITLE, &_box, boxColor, txtColor);

		int x = _box.X + 3;
		int y = _box.Y + 2;
		// Draw set for local database
		DrawLine(cGfx, '1', "Local Login", x, y++, cmdColor, _loginDb == DataLocation::DL_LOCAL);
		DrawLine(cGfx, '2', "GameJolt Login", x, y++, cmdColor, _loginDb == DataLocation::DL_GAMEJOLT);
		DrawLine(cGfx, '3', "Local Data Files", x, y++, cmdColor, _gameDb == DataLocation::DL_LOCAL);
		DrawLine(cGfx, '4', "GameJolt Game Files", x, y++, cmdColor, _gameDb == DataLocation::DL_GAMEJOLT);

		y++;
		DrawCmd(cGfx, PS_SAVEKEY, PS_SAVETEXT, x, y, txtColor, cmdColor);
		DrawCmd(cGfx, EXITKEY, EXITTEXT, x + 10, y, txtColor, cmdColor);
		_isDirty = false;
	}

	void MConfig::Clear(LPGRAPHICS gfx)
	{
		Zaxis::Graphics::ConGraphics* cGfx = CONCAST(gfx);
		UCHAR c = 32;
		cGfx->DrawRect(&_box, &c, &c);
	}

	void MConfig::Update()
	{
		if (_controller->ChkInput(PS_SAVEKEY))
		{
			// Initialize the login and data
			InitControllers();
			// Need to close down state but inform the state manager to retrieve my controllers
			_stateManager->PushState(Game::Graphics::Menus::MenuState::MS_CONFIG_SAVE);
			return;
		}
		if (_controller->ChkInput(EXITKEY))
		{
			// Exit config screen and don't save
			_stateManager->PopState();
			return;
		}
		if (_controller->ChkInput('1'))
		{
			_loginDb = DataLocation::DL_LOCAL;
			DirtyMe();
		}
		else if (_controller->ChkInput('2'))
		{
			_loginDb = DataLocation::DL_GAMEJOLT;
			DirtyMe();
		}
		if (_controller->ChkInput('3'))
		{
			_gameDb = DataLocation::DL_LOCAL;
			DirtyMe();
		}
		else if (_controller->ChkInput('4'))
		{
			_gameDb = DataLocation::DL_GAMEJOLT;
			DirtyMe();
		}
	}

	bool MConfig::IsDirty()
	{
		return _isDirty;
	}

	void MConfig::DirtyMe()
	{
		_isDirty = true;
	}

	void MConfig::SetStateManager(LPMENUSTATE manager)
	{
		_stateManager = manager;
	}

	LPDATA MConfig::GetDataController()
	{
		return _dataCtrl;
	}

	LPLOGIN MConfig::GetLoginController()
	{
		return _loginCtrl;
	}

	void MConfig::SetController(LPCONTROLLER ctrl)
	{
		_controller = ctrl;
	}

	bool MConfig::Shutdown()
	{
		// This screen can't shut the game down so return false
		return false;
	}

} } }// End namespace Game::Graphics::Menus