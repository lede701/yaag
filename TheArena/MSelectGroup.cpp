#include "MSelectGroup.h"
#include "BaseMenu.h"
#include "MHomeCommands.h"
#include "PlayerMenu.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	MSelectGroup::MSelectGroup(int x, int y)
	{
		_selector = new MSelect(x + 40, y+2);
		_bkg = new BaseMenu();
		_cmds = new MHomeCommands(1, 23);
		_player = new PlayerMenu(6, y+2, 39, 18);
	}

	MSelectGroup::~MSelectGroup()
	{
		// Check if we need to do some clean up
		if (_selector != NULL)
		{
			// Sweeping stuff under the rug so mom doesn't see my mess!
			delete _selector;
			_selector = NULL;
		}

		if (_cmds != NULL)
		{
			delete _cmds;
			_cmds = NULL;
		}

		if (_bkg != NULL)
		{
			delete _bkg;
			_bkg = NULL;
		}

		if (_player != NULL)
		{
			delete _player;
			_player = NULL;
		}
	}

	void MSelectGroup::Draw(LPGRAPHICS gfx)
	{
		// Draw screen background
		if (_bkg != NULL)
		{
			if (_bkg->IsDirty())
			{
				_bkg->Draw(gfx);
			}
		}

		// Draw commands background
		if (_cmds != NULL)
		{
			if (_cmds->IsDirty())
			{
				_cmds->Draw(gfx);
			}
		}

		if (_player != NULL)
		{
			if (_player->IsDirty())
			{
				_player->Draw(gfx);
				static_cast<PlayerMenu*>(_player)->DrawPlayer(gfx, _plEntity);
			}
		}

		// Draw selector
		if (_selector != NULL)
		{
			if (_selector->IsDirty())
			{
				_selector->Draw(gfx);
				LPVECTOR2D pos = new Vector2D(4, 25);
				static_cast<MSelect*>(_selector)->DrawMenu(gfx, pos);
			}// Endif selector screen is dirty
		}// Endif selector screen is defined and not null
		_isDirty = false;
	}

	void MSelectGroup::Clear(LPGRAPHICS gfx)
	{
		if (_selector != NULL)
		{
			_selector->Clear(gfx);
		}
	}

	void MSelectGroup::Update()
	{
		if (_selector != NULL)
		{
			_selector->Update();
		}
	}

	bool MSelectGroup::Shutdown()
	{
		return false;
	}

	bool MSelectGroup::IsDirty()
	{
		return _isDirty || _selector->IsDirty() || _bkg->IsDirty() || _cmds->IsDirty() || _player->IsDirty();
	}

	void MSelectGroup::DirtyMe()
	{
		_isDirty = true;
		_selector->DirtyMe();
		_bkg->DirtyMe();
		_cmds->DirtyMe();
		_player->DirtyMe();
	}

	void MSelectGroup::SetController(LPCONTROLLER ctrl)
	{
		_controller = ctrl;
		if (_selector != NULL)
		{
			static_cast<MSelect*>(_selector)->SetController(ctrl);
		}
	}

	void MSelectGroup::SetStateManager(LPMENUSTATE manager)
	{
		_manager = manager;
		if (_selector != NULL)
		{
			static_cast<MSelect*>(_selector)->SetStateManager(manager);
		}
	}

	void MSelectGroup::SetDataController(LPDATA data)
	{
		static_cast<MSelect*>(_selector)->SetDataController(data);
	}

	void MSelectGroup::SetPlayer(LPPLAYERENTITY player)
	{
		_plEntity = player;
	}

	LPMENUSCREEN MSelectGroup::GetSelector()
	{
		return _selector;
	}

} } }// End namespace Game::Graphics::Menus