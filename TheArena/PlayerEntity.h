#ifndef H_PLAYERENTITY
#define H_PLAYERENTITY

#include <algorithm>
#include <Windows.h>
#include <list>

#include "IEntityManager.h"
#include "IEntity.h"
#include "IAttacker.h"
#include "IWeapons.h"
#include "IArmor.h"
#include "IGraphics.h"
#include "IMenuScreen.h"
#include "IData.h"
#include "IAttacker.h"
#include "ItemList.h"
#include "IMenuState.h"
#include "NullSound.h"
#include "ArmorData.h"
#include "WeaponData.h"
#include "ConObject.h"
#include "Random.h"
#include "playerHelper.h"

#define LPPLAYERENTITY Game::Player::PlayerEntity*
#define HAND_WEAPON_ID 4
#define MAXHOTITEMS 10

namespace Game{ namespace Player
{
	using namespace Zaxis::Graphics::ConGraphicsData;
	using Game::Data::PlayerData;
	using Game::Data::WeaponData;
	using Game::Data::ArmorData;
	using Game::Data::CharacterData;

	class PlayerEntity :
		public Zaxis::Entity::IEntity, public Game::IAttacker
	{
	private:
		ConObject _myMesh;
		WORD _myColor;
		WORD _myHitColor;
		unsigned short _hitDuration;

		// Player data
		PlayerData data;
		LPDATA _dataCtrl;

		unsigned int _originalRight;
		LPWEAPONS _rightWeapon;
		LPWEAPONS _bow;
		LPARMOR _armor;

		Game::IEntityManager* _manager;
		LPMENUSCREEN _plMenu;
		LPMENUSTATE _menuState;

		LPRANDOM rand;
		int _id;

		bool PlayerWon;
		LPATTACKER _monster;

		std::list<LPCHARACTER> items;

	private:
		// Entity required pointers
		LPENGSOUND _sound;

	public:
		PlayerEntity(int id, LPDATA dataCtrl);
		PlayerEntity(PlayerData* plData, int id, LPDATA dataCtrl);
		virtual ~PlayerEntity();

		virtual void Init(void);
		virtual void Dispose(void);

		virtual LPOBJECT Update();
		virtual bool UpdateAttack();

		virtual void Draw(LPGRAPHICS gfx);

		virtual LPOBJECT SetUpdate(unsigned int interval);
		virtual unsigned int GetSpeed();

		virtual LPOBJECT SetSound(LPENGSOUND sound);
		virtual LPENGSOUND Sound();

		virtual void LoadDefaultWeapon();
		virtual LPPLAYERENTITY SetWeapon(WeaponData wpData);
		virtual LPPLAYERENTITY SetWeapon(unsigned int id);
		virtual LPWEAPONS GetWeapon();
		virtual int LoadWeapon(unsigned int id);

		virtual LPARMOR GetDefaultArmor();
		virtual LPPLAYERENTITY SetArmor(LPARMOR armor);
		virtual LPPLAYERENTITY SetArmor(unsigned int id);
		virtual LPARMOR GetArmor();
		virtual int LoadArmor(unsigned int id);

		virtual void Attack(LPATTACKER who);
		virtual void Defend(int attackRoll, unsigned int damage);
		virtual bool IsDead();
		virtual LPLOOT GetLoot();

		virtual void AddItem(LPCHARACTER data);
		virtual void RemoveItem(LPCHARACTER data);
		virtual LPCHARACTER GetCharacter();

		virtual bool IsAlive();

		virtual void CalculateMove(unsigned int mSpeed);

		virtual LPPLAYERENTITY SetManager(Game::IEntityManager* manager);
		virtual LPPLAYERENTITY SetRandom(LPRANDOM random);
		virtual LPPLAYERENTITY SetMenu(LPMENUSCREEN menu);
		virtual LPPLAYERENTITY SetStateManager(LPMENUSTATE state);

		virtual Game::Data::LevelData* GetLevel();
		virtual Game::Data::CharacterData* GetStats();
		virtual std::string GetName();
		virtual WORD GetColor();
		virtual int GetObjectId();

		virtual int iGetLevel();

		virtual LPPLAYERENTITY LevelUp();
		virtual void SetReady();

		virtual unsigned int GetMinDamage();
		virtual unsigned int GetDamage();
		virtual int GetDefense();
		virtual PlayerData* GetData();
		virtual void SetData(PlayerData data);

		virtual bool IsAttackReady();

		// Monster that lost to player
		virtual LPATTACKER GetMonster();

	public:
		unsigned int itemList[MAXHOTITEMS];

	};

} }// End namespace Game::Player
#endif