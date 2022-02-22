#ifndef H_MENUSYSTEM
#define H_MENUSYSTEM

#include <sstream>
#include <list>

#include "IUpdater.h"
#include "IMenuScreen.h"
#include "ICreateMonster.h"
#include "IDrawField.h"
#include "IMenuState.h"
#include "IEntityManager.h"
#include "ISetFieldGfx.h"
#include "IData.h"
#include "ILogin.h"
#include "ConGraphics.h"
#include "ConColor.h"
#include "BoxType.h"
#include "zmath.h"
#include "PlayerEntity.h"
#include "LevelData.h"
#include "PlayerMenu.h"
#include "MonsterMenu.h"
#include "FileData.h"
#include "Loot.h"

#define LPMENU Game::Graphics::MenuSystem*
#define MAX_LAYERS 16

#include "PlayerCommand.h"

namespace Game{ namespace Graphics
{

	using Zaxis::Graphics::ConGraphics;
	using namespace Zaxis::Math;
	using namespace Zaxis::Graphics::ConGraphicsData;
	using Game::Player::PlayerEntity;
	using Game::Graphics::Menus::MenuState;

	class MenuSystem :
		public Zaxis::Engine::IUpdater, public Game::Graphics::Menus::IMenuState
	{
	private:
		ConGraphics* graphics;
		LPPLAYERENTITY _player;
		LPMONSTERENTITY _monster;

		LPCONTROLLER _controller;
		LPMCREATOR mCreator;// Monster creator object

		LPFIELDGFX _manager;
		LPLOGIN _login;
		LPDATA _data;

		LPMENUSCREEN layers[MAX_LAYERS];

		unsigned int front;
		unsigned int back;
		unsigned int current;

		Rect GameField;
		Rect WorldField;
		LPVECTOR2D _exit;
		LPVECTOR2D _plStart;

		std::list<LPLOOT> lootChest;

		bool isRunning;

	public:
		MenuSystem(ConGraphics* gfx);
		virtual ~MenuSystem();

		virtual LPMENU DrawMenu();

		virtual void LoadPlayer(int playerId);
		virtual void LoadPlayer(Game::Data::PlayerData* data);
		virtual void SavePlayer();
		virtual void SavePlayer(bool saveScore);
		virtual LPMENU SetPlayer(LPPLAYERENTITY player);
		virtual LPMENU SetController(LPCONTROLLER ctrl);
		virtual LPCONTROLLER GetController();
		virtual LPMENU SetCreator(LPMCREATOR creator);
		virtual LPMENU SetManager(LPFIELDGFX manager);
		virtual void SetLoginController(LPLOGIN login);
		virtual void SetDataController(LPDATA data);

		virtual void Update();
		virtual bool Shutdown();

		virtual Rect* GetWorld();
		virtual Rect* GetArena();
		virtual LPVECTOR2D GetExit();

		virtual LPMENU AddMenu(LPMENUSCREEN menu);
		virtual LPMENUSCREEN PopMenuFront();
		virtual LPMENUSCREEN PopMenuBack();

		virtual void AddLoot(LPLOOT loot);

		// Menu state management
		virtual void PushState(MenuState state);
		virtual void PopState();
		virtual unsigned int NextLayer(unsigned int id);
		virtual unsigned int PrevLayer(unsigned int id);

		virtual void Pause(bool pause);
	};

} }// End namespace Game::Graphics


#endif