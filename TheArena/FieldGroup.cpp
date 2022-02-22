#include "FieldGroup.h"
#include "ConGraphics.h"
#include "gamedefs.h"
#include "AttackCommand.h"
#include "languagepack.h"

namespace Game{ namespace Graphics{ namespace Menus
{

	FieldGroup::FieldGroup(LPRECT2D GameField, LPVECTOR2D exit)
	{
		_gameField = GameField;
		_exit = exit;
		// Map player keys to commands
		int i = 0;
		cmds[i++] = new Game::Commands::PlayerCommand('W', new Vector2D(12, 28));
		cmds[i++] = new Game::Commands::PlayerCommand('A', new Vector2D(9, 29));
		cmds[i++] = new Game::Commands::PlayerCommand('D', new Vector2D(15, 29));
		cmds[i++] = new Game::Commands::PlayerCommand('S', new Vector2D(12, 30));
		cmds[i++] = new Game::Commands::AttackCommand(VK_SHIFT, "SHIFT", new Vector2D(9, 32));
		cmds[i++] = new Game::Commands::PlayerCommand(CMD_LEVELUPKEY, new Vector2D(52, 25));
		cmds[i++] = new Game::Commands::PlayerCommand(CMD_HEALKEY, new Vector2D(52, 26));
		// Make sure to clear all unused commands
		for (int idx = i; idx < PLCMDCOUNT; idx++)
		{
			cmds[idx] = NULL;
		}
		//		cmds[5] = new Game::Commands::PlayerCommand(VK_ESCAPE, "ESC", new Vector2D(24, 32));

		_back = new Game::Graphics::Menus::BaseMenu();
		_player = new Game::Graphics::Menus::PlayerMenu(6, 3);
		_monster = new Game::Graphics::Menus::MonsterMenu(1, 11);
		_field = new Game::Graphics::Menus::GameField(*GameField, exit);
		_cmds = new Game::Graphics::Menus::CtrlMenu(1, 23);
		_isDirty = true;
	}


	FieldGroup::~FieldGroup()
	{
		if (_back != NULL)
		{
			delete _back;
			_back = NULL;
		}
		if (_player != NULL)
		{
			delete _player;
			_player = NULL;

		}
		if (_monster != NULL)
		{
			delete _monster;
			_monster = NULL;
		}
		if (_field != NULL)
		{
			delete _field;
			_field = NULL;
		}
		if (_cmds == NULL)
		{
			delete _cmds;
			_cmds = NULL;
		}
	}

	void FieldGroup::Update()
	{
		for (int i = 0; i < PLCMDCOUNT; i++)
		{
			// Check if item is defined
			if (cmds[i] != NULL)
			{
				// Draw menu commands to screen
				cmds[i]->Update(CONCAST(graphics));
			}
		}
		if (plEntity != NULL)
		{
			_player->DrawPlayer(graphics, plEntity);
		}
		if (monEntity != NULL)
		{
			_monster->DrawMonster(graphics, monEntity);
		}
	}

	bool FieldGroup::Shutdown()
	{
		return false;
	}

	void FieldGroup::Draw(LPGRAPHICS gfx)
	{
		if (_back->IsDirty())
		{
			_back->Draw(gfx);
		}
		if (_field->IsDirty())
		{
			_field->Draw(gfx);
		}
		if (_player->IsDirty())
		{
			_player->Draw(gfx);
		}
		if (_monster->IsDirty())
		{
			_monster->Draw(gfx);
		}
		if (_cmds->IsDirty())
		{
			_cmds->Draw(gfx);
		}
		Zaxis::Graphics::ConGraphics* cGfx = CONCAST(gfx);
		cGfx->Init();
		_isDirty = false;
	}

	void FieldGroup::Clear(LPGRAPHICS gfx)
	{
		_back->Clear(gfx);
		_isDirty = false;
	}

	void FieldGroup::DrawField()
	{
		_field->Draw(graphics);
	}

	void FieldGroup::PlayerDied()
	{
		Clear(graphics);
		plEntity = NULL;
		monEntity = NULL;
		for (int i = 0; i < 8; i++)
		{
			cmds[i] = NULL;
		}

		_stateManager->PushState(MenuState::MS_DIED);
	}

	bool FieldGroup::IsDirty()
	{
		return _isDirty || _back->IsDirty() || _field->IsDirty() || _player->IsDirty() || _monster->IsDirty() || _cmds->IsDirty();
	}

	void FieldGroup::DirtyMe()
	{
		_isDirty = true;
		_back->DirtyMe();
		_field->DirtyMe();
		_player->DirtyMe();
		_monster->DirtyMe();
		_cmds->DirtyMe();
	}

	LPMENUSCREEN FieldGroup::SetController(LPCONTROLLER ctrl)
	{
		_controller = ctrl;
		for (int i = 0; i < PLCMDCOUNT; i++)
		{
			// Check if command is defined
			if (cmds[i] != NULL)
			{
				cmds[i]->SetController(_controller);

			}
		}
		return this;
	}

	LPMENUSCREEN FieldGroup::SetGraphics(LPGRAPHICS gfx)
	{
		graphics = gfx;
		return this;
	}

	LPMENUSCREEN FieldGroup::SetPlayer(LPPLAYERENTITY player)
	{
		plEntity = player;
		plEntity->SetMenu(_player);
		dynamic_cast<Game::Commands::AttackCommand*>(cmds[4])->SetPlayer(player);
		SetController(player->GetMover()->GetController());
		return this;
	}

	void FieldGroup::SetMonster(LPMONSTERENTITY monster)
	{
		monEntity = monster;
		_isDirty = true;
	}

	void FieldGroup::SetStateManager(LPMENUSTATE manager)
	{
		_stateManager = manager;
	}

	LPVECTOR2D FieldGroup::GetExit()
	{
		return _exit;
	}

	LPRECT2D FieldGroup::GetArean()
	{
		return _gameField;
	}

	void FieldGroup::DrawMonster(LPGRAPHICS gfx, LPMONSTERENTITY monster)
	{
		_monster->DrawMonster(gfx, monster);
	}
} } }// End namespace Game::Graphics::Menus


