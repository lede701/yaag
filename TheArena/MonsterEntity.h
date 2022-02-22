#ifndef H_MONSTERENTITY
#define H_MONSTERENTITY

#include <fstream>
#include <list>

#include "IEntity.h"
#include "NullSound.h"
#include "MovementData.h"
#include "IArmor.h"
#include "IWeapons.h"
#include "IAttacker.h"
#include "IEntityManager.h"
#include "IFriendlyEntity.h"
#include "IData.h"
#include "IMenuState.h"
#include "ConObject.h"
#include "Loot.h"
#include "ItemList.h"
#include "Random.h"
#include "AIMonster.h"
#include "MonsterEnum.h"
#include "MonsterData.h"

#define LPMONSTERENTITY Game::Monsters::Entities::MonsterEntity*

namespace Game{ namespace Monsters{ namespace Entities
{
	using namespace Zaxis::Graphics::ConGraphicsData;
	using Game::Data::CharacterData;

	class MonsterEntity :
		public Zaxis::Entity::IEntity, public Game::IAttacker
	{
	private:
		LPENTITY _player;
		ConObject _myMesh;
		WORD _myColor;
		WORD _myHitColor;
		MonsterType _mType;
		unsigned short _hitDuration;

		Game::Data::MonsterData data;
		LPWEAPONS _weapon;
		LPARMOR _armor;

		LPLOOT loot;

		LPENGSOUND _sound;

		Game::IEntityManager* _manager;
		LPMENUSTATE _menuStates;
		LPRANDOM rand;
		LPDATA _dataCtrl;

		std::list<LPCHARACTER> items;

	public:
		MonsterEntity(unsigned char mesh, LPENTITY player, LPDATA data, MonsterType type, WORD color = LtGreen);
		MonsterEntity(Game::Data::MonsterData monster, LPENTITY player, LPDATA data);
		virtual ~MonsterEntity();

		virtual void Init();

		virtual void LoadWeapon(unsigned int id);
		virtual void LoadArmor(unsigned int id);

		virtual LPOBJECT Update();

		virtual LPOBJECT SetUpdate(unsigned int interval);
		virtual unsigned int GetSpeed();

		virtual LPOBJECT SetSound(LPENGSOUND sound);
		virtual LPENGSOUND Sound();
		virtual void CalculateMove(unsigned int pSpeed);

		virtual LPMONSTERENTITY SetWeapon(LPWEAPONS weapon);
		virtual LPWEAPONS GetWeapon();
		virtual void SetArmor(LPARMOR armor);
		virtual LPARMOR GetArmor();
		virtual void Attack(LPATTACKER who);
		virtual void Defend(int attackRoll, unsigned int damage);
		virtual int GetDefense();
		virtual bool IsDead();
		virtual LPLOOT GetLoot();
		virtual WORD GetColor();
		virtual int iGetLevel();

		virtual Game::Data::MonsterData* GetData();
		virtual LPCHARACTER GetCharacter();

		virtual LPMONSTERENTITY SetManager(Game::IEntityManager* manager);
		virtual LPMONSTERENTITY SetStateManager(LPMENUSTATE manager);
		virtual LPMONSTERENTITY SetRandom(LPRANDOM random);

		virtual bool IsAlive();

		virtual bool FindMonster(MonsterType type);
		// Tell combat system if I'm ready to attack
		virtual bool IsAttackReady();
		// Tell colliding entity if I'm friednly
		virtual bool IsFriendly(LPENTITY entity);

		virtual void AddItem(LPCHARACTER item);
		virtual bool RemoveItem(LPCHARACTER item);

	};

} } }// End namespace Game::Monsters::Entity

#endif