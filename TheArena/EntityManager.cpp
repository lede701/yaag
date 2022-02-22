#include "EntityManager.h"
#include "FileIO.h"

#include <vector>

namespace Game
{

	EntityManager::EntityManager()
	{
		ClearField();
		for (int i = 0; i < 4; i++)
		{
			players[i] = NULL;
		}

		randEngine = new Zaxis::Math::Random();
		_log = new Zaxis::Logging::NullLogger();
		eManager = NULL;
		fldDraw = NULL;
		_gameField = NULL;
		_running = true;
	}

	EntityManager::~EntityManager()
	{
	}

	void EntityManager::Update()
	{

	}

	bool EntityManager::Shutdown()
	{
		return !_running;
	}

	LPPLAYERENTITY EntityManager::CreatePlayer(LPVECTOR2D pos, int id, Game::PlayerData* pData, LPCONTROLLER ctrl)
	{
		using Zaxis::Controllers::KeyboardController;
		using Game::Controllers::PlayerMover;
		using Game::Player::PlayerEntity;
		using namespace Game::Data;

		WeaponData wpData;
		wpData = _data->GetWeapon(pData->weaponId - 1);
		
		// TODO: Setup the game to support more than 1 player
		int plGameId = 0;
		
		LPPLAYERENTITY player = new PlayerEntity(pData, plGameId, _data);
		player->SetSleeping(false)->SetPosition2D(pos);
		player->SetMover(new PlayerMover(GetField()))->GetMover()->SetController(ctrl);
		player->SetManager(this)->SetRandom(randEngine);
		player->SetLogger(Log());

		Log("Adding player to game");

#ifdef _DEBUG
		if (player->GetStats()->Health < (player->GetStats()->MaxHealth / 2))
		{
			player->GetStats()->Health = player->GetStats()->MaxHealth / 2;
		}
#endif
		if (player->GetStats()->Health > player->GetStats()->MaxHealth)
		{
			player->GetStats()->Health = player->GetStats()->MaxHealth;
		}

		// Add player to game world
		gameWorld[pos->x][pos->y] = player;

		return player;
	}

	LPPLAYERENTITY EntityManager::SetPlayer(LPPLAYERENTITY player)
	{
		// Add player to list
		players[player->GetObjectId()] = player;
		// Add player to game engine
		if (eManager != NULL)
		{
			eManager->AddEntity(player);
		}

		return player;
	}

	LPMONSTERENTITY EntityManager::CreateRndMonster()
	{
		int type = 1;
		// Search database for a list of monsters
		int minLvl = players[0]->GetLevel()->Level - 1;
		int maxLvl = players[0]->GetLevel()->Level + 1;
		int mCount = 0;
		
		std::vector<int> mList;

		while (mList.size() < 3)
		{
			for (int i = 0; i < 256; i++)
			{
				int currLevel = static_cast<int>(_data->GetMonster(i).level);
				if (currLevel >= minLvl && currLevel <= maxLvl && currLevel > 0)
				{
					// Add pos to random list
					mList.push_back(_data->GetMonster(i).id);
				}
				// Check if we hit a blank monster record
				if (_data->GetMonster(i).id == 0)
				{
					break;
				}
			}
			if (mList.size() < 3)
			{
				minLvl--;
				maxLvl++;
			}
		}

		type = mList[randEngine->Next(0, mList.size())];
		//type = 4;

		LPMONSTERENTITY mEntity = CreateMonster(type, CreatePos());
		_currentMonster = mEntity;
		return mEntity;

	}

	LPMONSTERENTITY EntityManager::CreateMonster(unsigned int type)
	{
		_currentMonster = CreateMonster(type, CreatePos());
		return _currentMonster;
	}
		
	LPMONSTERENTITY EntityManager::CreateMonster(unsigned int type, LPVECTOR2D pos)
	{
		using Game::Monsters::Entities::MonsterEntity;
		using Game::Entity::Monsters::AI::AISight;
		using Game::Entity::Monsters::AI::AIMonster;
		using Game::Entity::Monsters::AI::AIRanged;
		using Game::Controllers::PlayerMover;
		using Game::Entity::Monsters::AI::AI_Type;

		// Try and load monster data from file
		MonsterData data;
		data = _data->GetMonster(type - 1);

		LPMONSTERENTITY monster = new MonsterEntity(data, GetPlayer(0), _data);
		unsigned int sight = 12;
		monster->SetPosition2D(pos)->SetSleeping(false);
		monster->SetMover(new PlayerMover(GetField()));
		monster->SetManager(this)->SetRandom(randEngine);
		monster->SetStateManager(_menuStates);
		// Add monster to game world
		gameWorld[pos->x][pos->y] = monster;

		// TODO: Move the AI setup to the monster.dat file
		switch (data.AI)
		{
		case AI_Type::AI_BASIC:
			{
				monster->GetMover()->SetController(new AISight(players[0]->GetPosition2D(), monster->GetPosition2D(), _exit, sight, AI_Type::AI_ASLEEP));
			}
			break;
		case AI_Type::AI_ASLEEP:
		case AI_Type::AI_BLIND:
			{
				monster->GetMover()->SetController(new AISight(players[0]->GetPosition2D(), monster->GetPosition2D(), _exit, sight, data.AI));
			}
			break;
		case AI_Type::AI_RANGED:
			{
				monster->GetMover()->SetController(new AIRanged(players[0]->GetPosition2D(), monster->GetPosition2D(), _exit, monster->GetWeapon()->GetRange()));
			}
			break;
		default:
			monster->GetMover()->SetController(new AISight(players[0]->GetPosition2D(), monster->GetPosition2D(), _exit, sight, AI_Type::AI_ASLEEP));
			break;
		}

		monster->SetLogger(Log());
		monster->CalculateMove(players[0]->GetSpeed());
		players[0]->CalculateMove(monster->GetSpeed());

		Log("Adding monster to game");

		if (eManager != NULL)
		{
			eManager->AddEntity(monster);
		}
		if (fldDraw != NULL)
		{
			fldDraw->SetMonster(monster);
		}

		return monster;
	}

	LPPLAYERENTITY EntityManager::GetPlayer(unsigned int id)
	{
		return players[id];
	}

	LPRECT2D EntityManager::GetField()
	{
		return _gameField;
	}

	void EntityManager::SetField(LPRECT2D field, LPRECT2D arena)
	{
		_gameField = field;
		_arena = arena;
		//*// Create Arena boundaries
		//x: 41, y: 1, Width: 37, Height: 17
		LPENTITY null = new Game::Field::FieldBrick();
		unsigned int minY = arena->Y - 1;
		unsigned int maxY = arena->Y + arena->Height + 1;
		unsigned int minX = arena->X - 1;
		unsigned int maxX = arena->X + arena->Width;
		for (unsigned int i = minX; i < maxX; i++)
		{
			gameWorld[i][minY] = null;
			gameWorld[i][maxY] = null;
		}
		for (unsigned int i = minY; i < maxY; i++)
		{
			gameWorld[minX][i] = null;
			gameWorld[maxX][i] = null;
		}
		// Put in the exit
		if (_exit != NULL)
		{
			gameWorld[_exit->x][_exit->y] = NULL;
			unsigned int y = _exit->y - 1;
			unsigned int sx = _exit->x - 1;
			unsigned int ex = _exit->x + 1;

			for (unsigned int x = sx; x < ex; x++)
			{
				gameWorld[x][y] = null;
			}
		}
		//*/
	}

	void EntityManager::SetExit(LPVECTOR2D exit)
	{
		_exit = exit;
	}

	void EntityManager::SetDataController(LPDATA data)
	{
		_data = data;
	}

	void EntityManager::SetDrawField(LPDRAWFIELD gfx)
	{
		fldDraw = gfx;
	}

	bool EntityManager::MoveEntity(LPENTITY entity, LPVECTOR2D oldPos)
	{
		LPVECTOR2D pos = entity->GetPosition2D();
		unsigned int x = pos->x;
		unsigned int y = pos->y;
		if (gameWorld[x][y] == NULL)
		{
			unsigned int ox = oldPos->x;
			unsigned int oy = oldPos->y;
			gameWorld[ox][oy] = NULL;
			gameWorld[x][y] = entity;
			return true;
		}
		return false;
	}

	LPENTITY EntityManager::GetEntity(LPVECTOR2D pos)
	{
		unsigned int x = pos->x;
		unsigned int y = pos->y;

		return gameWorld[x][y];
	}

	bool EntityManager::AddEntity(LPENTITY entity)
	{
		bool bRetVal = false;
		// Check if game engine entity manager is defined
		if (eManager != NULL)
		{
			// Add entity to game engine
			eManager->AddEntity(entity);
		}

		return bRetVal;
	}

	bool EntityManager::RmEntity(LPENTITY entity, bool AutoSpawn)
	{
		using Game::Field::FieldBrick;
		bool bRetVal = false;
		// Check if entity manager is defined
		if (eManager != NULL)
		{
			// Get entity world position
			LPVECTOR2D pos = entity->GetPosition2D()->Clone();
			FieldBrick* brick = dynamic_cast<FieldBrick*>(gameWorld[pos->x][pos->y]);
			// Try and remove entity from game engine
			if (eManager->RmEntity(entity) && brick == NULL)
			{
				// Remove link to entity in our manager
				gameWorld[pos->x][pos->y] = NULL;
				// Clear mesh from game world
				bRetVal = true;
				// Check if we spawn a monster
				if (AutoSpawn)
				{
					CreateRndMonster();
				}// Endif AutoSpawn is true
				//delete entity;
			}
			// Check if we have a way to refresh the game field
			if (fldDraw != NULL)
			{
				fldDraw->DrawField();
			}

		}

		// Tell caller if we were able to remove entity
		return bRetVal;
	}

	void EntityManager::ClearField()
	{
		for (int x = 0; x < WORLDX; x++)
		{
			for (int y = 0; y < WORLDY; y++)
			{
				gameWorld[x][y] = NULL;
			}
		}

	}

	LPVECTOR2D EntityManager::CreatePos()
	{
		LPVECTOR2D pos = new Zaxis::Math::Vector2D(0, 0);
		unsigned int minY = _arena->Y;
		unsigned int maxY = _arena->Y + _arena->Height + 1;
		unsigned int minX = _arena->X + 15;
		unsigned int maxX = _arena->X + _arena->Width;
		do
		{
			pos->x = randEngine->Next(minX, maxX);
			pos->y = randEngine->Next(minY, maxY);
		} while (gameWorld[pos->x][pos->y] != NULL);

		return pos;
	}

	void EntityManager::SetLog(LPLOGGER log)
	{
		// Cleanup my log mess!
		if (_log != NULL)
		{
			_log->Save();
			delete _log;
			_log = NULL;
		}

		_log = log;
	}

	LPLOGGER EntityManager::Log()
	{
		return _log;
	}

	LPLOGGER EntityManager::Log(std::string line)
	{
		Log()->WriteLine(line);
		return Log();
	}

	void EntityManager::SetEntityManager(LPENTITYENGINE manager)
	{
		eManager = manager;
	}

	void EntityManager::SetStateManager(LPMENUSTATE states)
	{
		_menuStates = states;
	}

	LPMONSTERENTITY EntityManager::GetMonster()
	{
		return _currentMonster;
	}

	LPMENUSCREEN EntityManager::CreateMenu(UINT id)
	{
		LPMENUSCREEN menu = NULL;

		return menu;
	}

	void EntityManager::RmMenu()
	{

	}

	void EntityManager::RmMenu(UINT id)
	{

	}

	void EntityManager::PlayerDead(int id)
	{
		using Game::Field::FieldBrick;
		using std::ostringstream;
		LPPLAYERENTITY player = players[id];
		if (player != NULL)
		{
			ostringstream out;
			// Remove player from game world
			RmEntity(player, false);
			// Remove all the monsters from the game world
			ClearField();
			eManager->RmAll();
			
			out << "you have lost " << player->GetData()->Losses << " times!";
			player->Dispose();
		}

		fldDraw->PlayerDied();
	}

	bool EntityManager::IsExit(LPVECTOR2D pos)
	{
		bool bRetVal = pos->x == _exit->x && pos->y == _exit->y;
		return bRetVal;
	}

	void EntityManager::Exit()
	{
		eManager->RmAll();
		ClearField();
	}

	void EntityManager::Pause(bool pause)
	{
		// Call game engine pause
		eManager->Pause(pause);
	}

}// End namespace Game
