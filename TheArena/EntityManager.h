#ifndef H_ENTITYMANAGER
#define H_ENTITYMANAGER

#include <fstream>

#include "IEntityManager.h"
#include "IEntity.h"
#include "ILogger.h"
#include "IUpdater.h"
#include "ICreateMonster.h"
#include "IEntityToEngine.h"
#include "IMenuScreen.h"
#include "IDrawField.h"
#include "IFieldExit.h"
#include "ISetFieldGfx.h"
#include "IData.h"
#include "IMenuState.h"
#include "MonsterEnum.h"
#include "PlayerEntity.h"
#include "MonsterEntity.h"
#include "MonsterData.h"
#include "FieldBrick.h"
#include "PlayerMover.h"
#include "KeyboardController.h"
#include "AIMonster.h"
#include "AISight.h"
#include "AIRanged.h"
#include "FieldBrick.h"
#include "NullLogger.h"
#include "ConColor.h"
#include "Random.h"
#include "WeaponData.h"
#include "FileData.h"

#include "AList.cpp"

#define WORLDX 80
#define WORLDY 24

namespace Game
{
	using Game::Monsters::Entities::MonsterType;
	using Game::Data::MonsterData;
	using Game::Player::PlayerData;
	using Game::Data::WeaponData;
	using Zaxis::Graphics::ConGraphicsData::ConColor;
	using std::ifstream;
	using Zaxis::Engine::Data::AList;
	using Zaxis::FileData;

	class EntityManager :
		public Zaxis::Engine::IUpdater, public IEntityManager, public Entity::ICreateMonster, public Entity::ISetFieldGfx
	{
		LPENTITY gameWorld[WORLDX][WORLDY];
		LPRECT2D _gameField;
		LPRECT2D _arena;
		LPPLAYERENTITY players[4];

		LPRANDOM randEngine;
		LPLOGGER _log;

		LPENTITYENGINE eManager;
		LPMENUSTATE _menuStates;
		LPDRAWFIELD fldDraw;
		LPVECTOR2D _exit;
		LPMONSTERENTITY _currentMonster;

		//LPMENUSCREEN menus[16];
		AList<LPMENUSCREEN> aMenus;

		LPDATA _data;

		bool _running;

	public:
		EntityManager();
		virtual ~EntityManager();

		void Update();
		bool Shutdown();

		void SetDrawField(LPDRAWFIELD gfx);

		void SetEntityManager(LPENTITYENGINE manager);
		void SetStateManager(LPMENUSTATE state);
		void SetDataController(LPDATA data);
		virtual LPPLAYERENTITY CreatePlayer(LPVECTOR2D pos, int id, Game::PlayerData* plData, LPCONTROLLER ctrl);
		virtual LPPLAYERENTITY SetPlayer(LPPLAYERENTITY player);
		LPMONSTERENTITY CreateMonster(unsigned int type);
		LPMONSTERENTITY CreateMonster(unsigned int type, LPVECTOR2D pos);
		LPMONSTERENTITY CreateRndMonster();
		LPMONSTERENTITY GetMonster();
		LPVECTOR2D CreatePos();

		LPRECT2D GetField();
		virtual void SetField(LPRECT2D field, LPRECT2D arena);
		virtual void SetExit(LPVECTOR2D exit);
		LPPLAYERENTITY GetPlayer(unsigned int id);

		virtual bool MoveEntity(LPENTITY entity, LPVECTOR2D oldPos);
		virtual LPENTITY GetEntity(LPVECTOR2D pos);
		virtual bool AddEntity(LPENTITY entity);
		virtual bool RmEntity(LPENTITY entity, bool AutoSpawn=true);
		virtual void PlayerDead(int id);
		virtual bool IsExit(LPVECTOR2D pos);
		virtual void Exit();

		// Create Menu Layer
		virtual  LPMENUSCREEN CreateMenu(UINT id);
		// Remove current menu
		virtual void RmMenu();
		// Remove menu layer
		virtual void RmMenu(UINT id);

		void ClearField();

		void SetLog(LPLOGGER log);
		LPLOGGER Log();
		LPLOGGER Log(std::string line);

		virtual void Pause(bool pause);
	};
}// End namespace Game

#endif