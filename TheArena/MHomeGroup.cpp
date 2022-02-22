#include "MHomeGroup.h"
#include "gamedefs.h"
#include "BaseMenu.h"
#include "languagepack.h"
#include "MHomeCommands.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	using Zaxis::Graphics::ConGraphicsData::ConColor;

	MHomeGroup::MHomeGroup(int x, int y)
	{
		_isRunning = true;
		_isDirty = true;
		box = { x, y, 80, 25 };
		boxColor = ConColor::Black | ConColor::Red;
		_bkg = new BaseMenu();
		_plMenu = new PlayerMenu(6, 3, 39, 18);
		_cmds = new MHomeCommands(1, 23);
	}

	MHomeGroup::~MHomeGroup()
	{
		delete _bkg;
		delete _plMenu;
	}

	void MHomeGroup::Draw(LPGRAPHICS gfx)
	{
		if (_bkg->IsDirty())
		{
			_bkg->Draw(gfx);
		}
		if (_cmds->IsDirty())
		{
			_cmds->Draw(gfx);
			LPVECTOR2D pos = new Zaxis::Math::Vector2D(4, 25);
			static_cast<MHomeCommands*>(_cmds)->DrawMenu(gfx, pos);
		}

		// Make sure player menu is drawn last
		if (_plMenu->IsDirty())
		{
			_plMenu->Draw(gfx);
			_plMenu->DrawPlayer(gfx, _player);
		}

		_isDirty = false;
	}

	void MHomeGroup::Clear(LPGRAPHICS gfx)
	{
		_bkg->Clear(gfx);
	}

	void MHomeGroup::Update()
	{
		if (_controller->ChkInput(VK_ESCAPE) || _controller->ChkInput(EXITKEY))
		{
			_manager->SavePlayer(true);
			_manager->PopState();
			// Prevent calling myself and causing a game crash
			return;
		}
		else
		{
			if (_controller->ChkInput(CMD_RANDOMKEY))
			{
				_manager->PushState(Game::Graphics::Menus::MenuState::MS_GAMEFIELD);
			}
			if (_controller->ChkInput(CMD_ENTERARENAKEY))
			{
				_manager->PushState(Game::Graphics::Menus::MenuState::MS_SELECTION);
			}
			if (_controller->ChkInput(CMD_LEVELUPKEY))
			{
				_manager->PushState(Game::Graphics::Menus::MenuState::MS_LEVELUP);
			}
			if (_controller->ChkInput(CMD_STOREKEY))
			{
				_manager->PushState(Game::Graphics::Menus::MenuState::MS_STORE);
			}
			if (_controller->ChkInput(CMD_PLAYERLISTKEY))
			{
				// Last time we made this state now we are just connecting it to the home screen
				_manager->PushState(Game::Graphics::Menus::MenuState::MS_PLAYERLIST);
			}

		}
	}

	bool MHomeGroup::Shutdown()
	{
		return !_isRunning;
	}

	bool MHomeGroup::IsDirty()
	{
		return _isDirty;
	}

	void MHomeGroup::DirtyMe()
	{
		_isDirty = true;
		_bkg->DirtyMe();
		_plMenu->DirtyMe();
		_cmds->DirtyMe();
	}

	void MHomeGroup::SetStateManager(LPMENUSTATE manager)
	{
		_manager = manager;
	}

	void MHomeGroup::SetController(LPCONTROLLER ctrl)
	{
		_controller = ctrl;
	}

	void MHomeGroup::SetPlayer(LPPLAYERENTITY player)
	{
		_player = player;
	}

} } }// End namespace Game::Graphics::Menus
