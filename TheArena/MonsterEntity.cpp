#include "MonsterEntity.h"
#include "Weapon.h"
#include "WeaponData.h"
#include "Armor.h"
#include "ArmorData.h"
#include "Projectile.h"
#include "FileData.h"
#include "FileIO.h"

namespace Game{	namespace Monsters{	namespace Entities
{

	MonsterEntity::MonsterEntity(unsigned char mesh, LPENTITY player, LPDATA dataCtrl, MonsterType type, WORD color/* = LtGreen*/) :
		IEntity()
	{
		_mType = type;
		Init();
		_myMesh.c = mesh;
		_myMesh.color = color;
		_myColor = _myMesh.color;
		_myHitColor = ConColor::LtRed;

		SetMesh(&_myMesh);

		_player = player;
		_dataCtrl = dataCtrl;
	}

	MonsterEntity::MonsterEntity(Game::Data::MonsterData monster, LPENTITY player, LPDATA dataCtrl)
	{
		_dataCtrl = dataCtrl;
		data = monster;
		_myMesh.c = monster.mesh;
		_myMesh.color = monster.color;
		_myHitColor = monster.hitColor;
		_myColor = monster.color;
		_mType = data.type;
		Init();
		LoadArmor(data.armorId);
		LoadWeapon(data.weaponId);

		SetMesh(&_myMesh);
		_player = player;
	}

	MonsterEntity::~MonsterEntity()
	{
	}

	void MonsterEntity::Init()
	{
		static float levelAdjustemnt = 0.3f;
		// Initialize monster base information
		_sound = new Zaxis::Sound::NullSound();
		if (_mType != data.type)
		{
			FindMonster(_mType);
		}

		loot = new Game::Data::Loot();
		loot->Exp = (data.character.AttackSpeed + data.character.AttackDamage + data.character.DefenseRating
			+ data.character.MaxHealth) * data.level;
		loot->Gold = static_cast<int>((data.character.MaxHealth + data.character.Speed) * (data.level * levelAdjustemnt));
		loot->Items = Game::Data::ItemList::IL_NONE;
		loot->data = data;
		_manager = NULL;
		_hitDuration = 0;

		LoadArmor(1);
		LoadWeapon(4);
	}

	LPOBJECT MonsterEntity::Update()
	{
		LPATTACKER pl = NULL;
		Game::Entity::Monsters::AI::AIMonster* ai = dynamic_cast<Game::Entity::Monsters::AI::AIMonster*>(GetMover()->GetController());
		// Calculate the movement speed of monster
		data.character.NextMove = (data.character.NextMove + 1) % data.character.Move;
		data.character.NextAttack = min(data.character.NextAttack + 1, 100);
		// Check if we are able to move on this frame
		if (data.character.NextMove == 0 && IsAlive())
		{
			// Convert player to attack interface for testing if player is alive
			if (GetMover()->GetController()->ChkInput(VK_SHIFT) && data.character.NextAttack > data.character.AttackSpeed)
			{
				LPENTITY entity = _manager->GetEntity(ai->GetAttackPos());
				pl = dynamic_cast<LPATTACKER>(entity);
				// Check if what we want to attack is the player
				if (pl != NULL && !pl->IsDead())
				{
					// This is a bad spot for this because it will only be check if monster is attacking
					ai->DoIFlee(pl, this);
					if (ai->GetRange() > 1)
					{
						using Game::Items::Projectile::Projectile;
						// Shoot a projectile
						LPPROJECTILE projectile = new Projectile(ai->GetRangedVelocity(), ai->GetRange(), this);
						LPVECTOR2D projPos = GetPosition2D()->Clone();
						// Move projectile so it doesn't start on top of the monster
						projPos->x += ai->GetRangedVelocity()->x;
						projPos->y += ai->GetRangedVelocity()->y;
						// Configure projectile
						projectile->SetPosition2D(projPos)->SetSleeping(false);
						projectile->SetManager(_manager);
						// Add projectile to entity manager for tracking and drawing
						_manager->AddEntity(projectile);
						data.character.NextAttack = 0;
					}
					else
					{
						// Attacking!!!!
						Attack(pl);
						data.character.NextAttack = 0;
					}
				}
			}
			else
			{
				Zaxis::Entity::IEntity::Update();
				_manager->MoveEntity(this, GetOldPosition2D());
			}

		}
		else
		{
			SetOldPosition2D(GetPosition2D());
		}
		if (_hitDuration > 0)
		{
			_hitDuration--;
			if (_hitDuration == 0)
			{
				_myMesh.color = _myColor;
			}
		}

		// Have AI check to see if AI wants to flee
		pl = dynamic_cast<LPATTACKER>(_player);
		if (pl != NULL && ai != NULL)
		{
			ai->DoIFlee(pl, this);
		}

		if (_manager->IsExit(GetPosition2D()))
		{
			_manager->Exit();
			// TODO: Find a way to set me into the player object
			_menuStates->AddLoot(loot);
			_menuStates->PushState(Game::Graphics::Menus::MenuState::MS_FLEEWIN);
			return this;
		}

		// Return me
		return this;
	}

	WORD MonsterEntity::GetColor()
	{
		return _myMesh.color;
	}

	LPOBJECT MonsterEntity::SetUpdate(unsigned int interval)
	{
		data.character.Move = interval;
		return this;
	}

	LPOBJECT MonsterEntity::SetSound(LPENGSOUND snd)
	{
		if (_sound != NULL)
		{
			delete _sound;
			_sound = NULL;
		}
		_sound = snd;

		return this;
	}

	LPENGSOUND MonsterEntity::Sound()
	{
		return _sound;
	}

	void MonsterEntity::CalculateMove(unsigned int pSpeed)
	{
		if (pSpeed > data.character.Speed)
		{
			SetUpdate((pSpeed - data.character.Speed) + 1);
		}
		else
		{
			// Update every frame.  Fast monster...
			SetUpdate(1);
		}
	}
	unsigned int MonsterEntity::GetSpeed()
	{
		return data.character.Speed;
	}

	void MonsterEntity::Attack(LPATTACKER who)
	{
		if (who != NULL && !who->IsDead())
		{
			LPCHARACTER mchar = GetCharacter();
			unsigned int minRoll = 0 + (data.level - 1) + mchar->AttackBonus;
			unsigned int maxRoll = 30;
			int attackRoll = rand->Next(minRoll, maxRoll);
			unsigned int damage = rand->Next(mchar->AttackMinDamage, mchar->AttackDamage);
			if (attackRoll > 20)
			{
				damage = damage * 2;
			}
			attackRoll -= who->GetCharacter()->DefenseRating;
			who->Defend(attackRoll, damage);
		}
	}

	void MonsterEntity::Defend(int attackRoll, unsigned int attack)
	{
		unsigned int defense = GetDefense();
		if (attack > defense || attackRoll > 19)
		{
			std::ostringstream out;
			// Set my color to the hit color
			_myMesh.color = _myHitColor;
			_hitDuration = 10;
			// Send attack to AI system
			Game::Entity::Monsters::AI::AIMonster* ai = dynamic_cast<Game::Entity::Monsters::AI::AIMonster*>(GetMover()->GetController());
			out << "PLAYER: hit for " << attack;
			Log(out.str());
			unsigned int myDamage = attack;
			if (attackRoll < 18)
			{
				double percDamage = abs(static_cast<double>(attackRoll)+10.0) / 30.0;
				myDamage = static_cast<unsigned int>(percDamage * static_cast<double>(attack));
			}

			if (ai != NULL)
			{
				// Let the AI know I've been hit and it hurt!
				ai->ProcessAttack();
			}
			if (myDamage >= data.character.Health)
			{
				data.character.Health = 0;
			}
			else
			{
				// Reset monster attack like the player (Only fair right?)
				//data.nextAttack = 0;
				data.character.Health -= myDamage;
			}
		}
		else
		{
			Log("PLAYER: Missed me nah nah");
		}
	}

	int MonsterEntity::GetDefense()
	{
		LPCHARACTER mchar = GetCharacter();
		int defense = mchar->DefenseRating;
		return defense;
	}

	LPMONSTERENTITY MonsterEntity::SetWeapon(LPWEAPONS weapon)
	{
		_weapon = weapon;
		return this;
	}

	LPWEAPONS MonsterEntity::GetWeapon()
	{
		return _weapon;
	}

	void MonsterEntity::SetArmor(LPARMOR armor)
	{
		_armor = armor;
	}

	LPARMOR MonsterEntity::GetArmor()
	{
		return _armor;
	}


	bool MonsterEntity::IsAlive()
	{
		return data.character.Health > 0;
	}

	bool MonsterEntity::IsDead()
	{
		return !IsAlive();
	}

	LPLOOT MonsterEntity::GetLoot()
	{
		LPLOOT myLoot = NULL;
		if (loot != NULL)
		{
			myLoot = loot;
			loot = NULL;
		}
		return myLoot;
	}

	LPMONSTERENTITY MonsterEntity::SetManager(Game::IEntityManager* manager)
	{
		_manager = manager;
		return this;
	}

	LPMONSTERENTITY MonsterEntity::SetStateManager(LPMENUSTATE manager)
	{
		_menuStates = manager;
		return this;
	}

	LPMONSTERENTITY MonsterEntity::SetRandom(LPRANDOM random)
	{
		rand = random;
		return this;
	}

	bool MonsterEntity::FindMonster(MonsterType type)
	{
		bool bRetVal = false;
		using std::ifstream;
		ifstream fin;
		fin.open("monster.dat", ifstream::binary);
		if (fin.good())
		{
			while (!fin.eof())
			{
				fin.read((char*)&data, sizeof(Game::Data::MonsterData));
				if (data.type == type)
				{
					bRetVal = true;
					break;
				}
			}
		}
		fin.close();

		return bRetVal;
	}

	Game::Data::MonsterData* MonsterEntity::GetData()
	{
		return &data;
	}

	LPCHARACTER MonsterEntity::GetCharacter()
	{
		LPCHARACTER cd = new CharacterData();
		cd->Init(data.character);
		if (items.size() > 0)
		{
			for (std::list<LPCHARACTER>::iterator it = items.begin(); it != items.end(); it++)
			{
				cd->Add((*it));
			}
		}// Endif items are in inverntory
		return cd;
	}

	bool MonsterEntity::IsAttackReady()
	{
		return data.character.NextAttack >= data.character.AttackSpeed;
	}

	/// Load weapon for monster
	void MonsterEntity::LoadWeapon(unsigned int id)
	{
		using Game::Data::WeaponData;
		using Zaxis::FileData;
		
		// Check if current weapon is defined
		if (_weapon != NULL)
		{
			RemoveItem(_weapon->GetCharacter());
			// Dispose old weapon and save some memory like a tree
			delete _weapon;
			_weapon = NULL;
		}

		WeaponData wpData = _dataCtrl->GetWeapon(id - 1);
		// Create a new weapon
		_weapon = new Game::Items::Weapons::Weapon(wpData);
		AddItem(_weapon->GetCharacter());
	}

	void MonsterEntity::LoadArmor(unsigned int id)
	{
		using Game::Data::ArmorData;
		using Zaxis::FileData;

		if (_armor != NULL)
		{
			RemoveItem(_armor->GetCharacter());
			delete _armor;
			_armor = NULL;
		}

		ArmorData apData = _dataCtrl->GetArmor(id - 1);
		_armor = new Game::Items::Armor::Armor(apData);
		AddItem(_armor->GetCharacter());
	}

	bool MonsterEntity::IsFriendly(LPENTITY entity)
	{
		bool bRetVal = false;
		// Check if this is a player
		MonsterEntity* mEntity = dynamic_cast<MonsterEntity*>(entity);
		bRetVal = mEntity != NULL;

		return bRetVal;
	}

	int MonsterEntity::iGetLevel()
	{
		return data.level;
	}

	void MonsterEntity::AddItem(LPCHARACTER item)
	{
		items.push_back(item);
	}

	bool MonsterEntity::RemoveItem(LPCHARACTER item)
	{
		bool bRetVal = false;
		// Need to find item in list of items
		for (std::list<LPCHARACTER>::iterator it = items.begin(); it != items.end(); it++)
		{
			if (item->dataId == (*it)->dataId)
			{
				// Found item so time to remove it from the list
				items.remove((*it));
				bRetVal = true;
				break;
			}
		}

		return bRetVal;
	}

} } }// End namespace Game::Monsters::Entity

