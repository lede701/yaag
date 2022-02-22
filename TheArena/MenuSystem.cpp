#include "MenuSystem.h"
#include "BaseMenu.h"
#include "CtrlMenu.h"
#include "PlayerMenu.h"
#include "GameField.h"
#include "IMenuMonster.h"
#include "FileIO.h"
// Menu systems
#include "FieldGroup.h"
#include "GameOver.h"
#include "NoRevival.h"
#include "MLogin.h"
#include "MLevelUp.h"
#include "MHomeGroup.h"
#include "StoreMenu.h"
#include "MWin.h"
#include "MFleeWin.h"
#include "MSelectGroup.h"
#include "MPlayerList.h"
#include "MPlayerInfo.h"
#include "MConfig.h"
#include "fLogin.h"

#define CMDCOUNT 6

namespace Game{ namespace Graphics
{

	MenuSystem::MenuSystem(ConGraphics* gfx)
	{
		using Zaxis::Math::Vector2D;
		graphics = gfx;
		GameField = { 42, 4, 35, 13 };
		WorldField = { 0, 0, 79, 23 };
		_exit = new Zaxis::Math::Vector2D(68, 3);
		
		// Store field layer number
		mCreator = NULL;
		_controller = NULL;
		_manager = NULL;
		isRunning = true;
		for (int i = 0; i < MAX_LAYERS; i++)
		{
			layers[i] = NULL;
		}

		_plStart = new Vector2D(52, 8);
	}


	MenuSystem::~MenuSystem()
	{
		// Clean up menu layers
		LPMENUSCREEN menu;
		while (menu = PopMenuBack())
		{
			delete menu;
		}
	}

	LPMENU MenuSystem::DrawMenu()
	{
		// Very boring code to draw the menu!  Read at your own risk...
		layers[current]->Draw(graphics);

		return this;
	}

	Rect* MenuSystem::GetWorld()
	{
		return &WorldField;
	}

	Rect* MenuSystem::GetArena()
	{
		return &GameField;
	}

	LPVECTOR2D MenuSystem::GetExit()
	{
		return _exit;
	}

	LPMENU MenuSystem::SetPlayer(LPPLAYERENTITY player)
	{
		_player = player;
		_player->SetStateManager(this);
		return this;
	}

	void MenuSystem::LoadPlayer(int playerId)
	{
		Game::Data::PlayerData data;
		ZeroMemory(&data, sizeof(Game::Data::PlayerData));
		LPPLAYERENTITY player = _manager->CreatePlayer(_plStart->Clone(), 1, &data, _controller);
		SetPlayer(player);
	}

	void MenuSystem::LoadPlayer(Game::Data::PlayerData* data)
	{
		LPPLAYERENTITY player = _manager->CreatePlayer(_plStart->Clone(), 1, data, _controller);
		SetPlayer(player);
	}

	void MenuSystem::SavePlayer()
	{
		if (_player != NULL)
		{
			Game::Data::PlayerData data = (*_player->GetData());
			_login->SetData(&data, sizeof(Game::Data::PlayerData));
			//_login->Save();
			//plData.Add(data, data.id - 1);
			//plData.Save(plFile);
		}
	}

	void MenuSystem::SavePlayer(bool saveScore)
	{
		SavePlayer();
		if (saveScore)
		{
			float denominator = static_cast<float>(_player->GetData()->Wins + _player->GetData()->Losses);
			float score = (_player->GetData()->level.Experience / denominator);
			_login->SaveScore(static_cast<int>(score), _player->GetData()->name);
		}
	}

	LPMENU MenuSystem::SetController(LPCONTROLLER ctrl)
	{
		_controller = ctrl;
		return this;
	}

	LPCONTROLLER MenuSystem::GetController()
	{
		return _controller;
	}

	void MenuSystem::Update()
	{
		layers[current]->Update();
		if (layers[current] != NULL && layers[current]->IsDirty())
		{
			layers[current]->Draw(graphics);
		}
	}

	bool MenuSystem::Shutdown()
	{
		return !isRunning;
	}

	LPMENU MenuSystem::AddMenu(LPMENUSCREEN menu)
	{
		if (NextLayer(back) != front)
		{
			layers[back] = menu;
			current = back;
			back = NextLayer(back);
		}

		return this;
	}

	unsigned int MenuSystem::NextLayer(unsigned int id)
	{
		return (id + 1) % MAX_LAYERS;
	}

	unsigned int MenuSystem::PrevLayer(unsigned int id)
	{
		unsigned int pId = 0;
		if (id == 0)
		{
			pId = MAX_LAYERS - 1;
		}
		else
		{
			pId = id - 1;
		}

		return pId;
	}

	LPMENUSCREEN MenuSystem::PopMenuBack()
	{
		LPMENUSCREEN menu = NULL;
		if (back != front)
		{
			back = PrevLayer(back);
			menu = layers[back];
			layers[back] = NULL;
			current = PrevLayer(back);
			if (layers[current] != NULL)
			{
				layers[current]->DirtyMe();
			}
		}
		return menu;
	}

	LPMENUSCREEN MenuSystem::PopMenuFront()
	{
		LPMENUSCREEN menu = NULL;
		if (front != back)
		{
			menu = layers[front];
			layers[front] = NULL;
			front = NextLayer(front);
		}

		return menu;
	}

	LPMENU MenuSystem::SetCreator(LPMCREATOR creator)
	{
		mCreator = creator;
		return this;
	}

	void MenuSystem::PushState(MenuState state)
	{
		using namespace Game::Graphics::Menus;
		switch (state)
		{
		case MenuState::MS_DIED:
			{
				_player->GetData()->Losses++;
				SavePlayer();
				if (_player->GetLevel()->Gold > _player->GetLevel()->Level * 100)
				{
					GameOver* over = new GameOver(10, 2);
					over->SetPlayer(_player);
					over->SetStateManager(this);
					AddMenu(over);
				}
				else
				{
					NoRevival* over = new NoRevival(10, 2);
					over->SetPlayer(_player);
					over->SetStateManager(this);
					PopState();// Remove the game field
					PopState();// Remove the select monster field
					AddMenu(over);
				}
			}
			break;
		case MenuState::MS_CONFIG:
			{
				MConfig *cfg = new MConfig(15, 5);
				cfg->SetController(GetController());
				cfg->SetStateManager(this);
				AddMenu(cfg);
			}
			break;
		case MenuState::MS_CONFIG_SAVE:
			{
				// What do we need to save here

				// Clean up the menu state
				PopState();
				// Update the login menu
				MLogin *login = static_cast<MLogin*>(layers[front]);
				if (login != NULL)
				{
					login->SetLoginController(_login);
				}
			}
			break;
		case MenuState::MS_REVIVEENOUGH:
			{
				PopState();
				NoRevival* over = new NoRevival(10, 2);
				over->SetPlayer(_player);
				over->SetStateManager(this);
				AddMenu(over);
			}
			break;
		case MenuState::MS_REVIVE:
			{
				PopState();
				SavePlayer();
				PushState(MenuState::MS_GAMEFIELD);
			}
			break;
		case MenuState::MS_RESURECTDEAD:
			{
				PopState();//  Pop off the no revive menu and return to the home screen 
				SavePlayer();
			}
			break;
		case MenuState::MS_HOME:
			{
				//FieldHome* home = new FieldHome()
				MHomeGroup* home = new MHomeGroup(0,0);
				home->SetController(GetController());
				home->SetStateManager(this);
				home->SetPlayer(_player);
				AddMenu(home);
			}
			break;
		case MenuState::MS_GAMEFIELD:
			{
				//SavePlayer();
				// Set player start location
				_player->SetPosition2D(_plStart->Clone());
				FieldGroup* fld = new FieldGroup(GetArena(), _exit);
				fld->SetGraphics(graphics);
				fld->SetPlayer(_player);
				fld->SetStateManager(this);
				_manager->SetExit(GetExit());
				_manager->SetField(GetWorld(), GetArena());
				_manager->SetDrawField(fld);
				_manager->SetPlayer(_player);
				mCreator->CreateRndMonster();

				AddMenu(fld);
			}
			break;
		case MenuState::MS_SELECTION:
			{
				MSelectGroup* menu = new MSelectGroup(1, 1);
				menu->SetDataController(_data);
				menu->SetController(GetController());
				menu->SetStateManager(this);
				menu->SetPlayer(_player);

				AddMenu(menu);
			}
			break;
		case MenuState::MS_FIGHTMONSTER:
			{
				// Get monster id from MSelect form
				MSelect* selector = static_cast<MSelect*>(static_cast<MSelectGroup*>(layers[current])->GetSelector());
				unsigned int id = selector->GetMonsterId();
				// Remove the select form from layers

				SavePlayer();
				// Set player start location
				_player->SetPosition2D(_plStart->Clone());
				_player->SetReady();
				FieldGroup* fld = new FieldGroup(GetArena(), _exit);
				fld->SetGraphics(graphics);
				fld->SetPlayer(_player);
				fld->SetStateManager(this);
				_manager->SetExit(GetExit());
				_manager->SetField(GetWorld(), GetArena());
				_manager->SetDrawField(fld);
				_manager->SetPlayer(_player);
				mCreator->CreateMonster(id);

				AddMenu(fld);
			}
			break;
		case MenuState::MS_LEVELUP:
			{
				MLevelUp* up = new MLevelUp(_player, 25, 2);
				up->SetStateManager(this);
				AddMenu(up);
			}
			break;
		case MenuState::MS_LOGIN:
			{
				// Starting state for the game
				MLogin* login = new MLogin(10, 4);
				login->SetStateManager(this);
				login->SetController(GetController());
				// Make sure there is a default login controller
				if (_login == NULL)
				{
					Game::File::FLogin *ctrl = new Game::File::FLogin();
					ctrl->Init();
					SetLoginController(ctrl);
					SetDataController(ctrl);
					login->SetLoginController(ctrl);
				}
				AddMenu(login);
			}
			break;
		case MenuState::MS_STORE:
			{
				StoreMenu* menu = new StoreMenu(_player, 10, 2, _data);
				menu->SetStateManager(this);
				AddMenu(menu);
			}
			break;
		case MenuState::MS_WIN:
			{
				MWin* win = new MWin(15, 5, _player);
				_player->GetData()->Wins++;
				win->SetController(GetController());
				win->SetStateManager(this);
				if (lootChest.size() > 0)
				{
					// Move each item to the menu loot
					for (std::list<LPLOOT>::iterator it = lootChest.begin(); it != lootChest.end(); it++)
					{
						win->AddLoot(*it);
					}
					lootChest.clear();
				}
				// Calculate loot
				win->CalculateLoot();
				// Remove game map
				PopState();
				_player->LevelUp();
				//_player->GetData().
				SavePlayer();
				AddMenu(win);
			}
			break;
		case MenuState::MS_FLEEWIN:
			{
				MFleeWin* win = new MFleeWin(5, 3, _player);
				win->SetController(GetController());
				win->SetStateManager(this);
				// Update player win/loss
				_player->GetData()->Wins++;
				if (lootChest.size() > 0)
				{
					// Move each item to the menu loot
					for (std::list<LPLOOT>::iterator it = lootChest.begin(); it != lootChest.end(); it++)
					{
						win->AddLoot(*it);
					}
					lootChest.clear();
				}
				// Remove game map
				PopState();
				_player->LevelUp();
				SavePlayer();
				AddMenu(win);
			}
			break;
		case MenuState::MS_PLAYERLIST:
			{
				MPlayerList* menu = new MPlayerList(5, 1);
				menu->SetController(GetController());
				menu->SetStateManager(this);
				AddMenu(menu);
			}
			break;
		case MenuState::MS_PLAYERDETAILS:
			{
				// Create menu for player information panel
				MPlayerInfo* menu = new MPlayerInfo(20, 3);
				menu->SetController(GetController());
				menu->SetStateManager(this);

				// Need to get the player information from the previous menu layer
				MPlayerList* plLister = static_cast<MPlayerList*>(layers[current]);
				Game::Data::PlayerData pl = plLister->GetSelectedPlayer();
				menu->SetPlayer(pl);

				AddMenu(menu);
			}
			break;
		case MenuState::MS_EXIT:
			{
				SavePlayer();
				isRunning = false;
			}
			break;
		}
	}

	void MenuSystem::PopState()
	{
		LPMENUSCREEN menu = PopMenuBack();
		menu->Clear(graphics);

		delete menu;
	}

	LPMENU MenuSystem::SetManager(LPFIELDGFX manager)
	{
		_manager = manager;
		SetCreator(dynamic_cast<Game::Entity::ICreateMonster*>(manager));

		return this;
	}

	void MenuSystem::SetLoginController(LPLOGIN login)
	{
		using namespace Game::Graphics::Menus;
		_login = login;
		// Try and update the login menu
		MLogin *menu = static_cast<MLogin*>(layers[front]);
		if (menu != NULL)
		{
			menu->SetLoginController(login);
		}
	}

	void MenuSystem::SetDataController(LPDATA data)
	{
		_data = data;
		_manager->SetDataController(_data);
	}

	void MenuSystem::Pause(bool pause)
	{
		_manager->Pause(pause);
	}

	// Add an item to the loot chest
	void MenuSystem::AddLoot(LPLOOT loot)
	{
		lootChest.push_back(loot);
	}

} }// End namespace Game::Graphics

