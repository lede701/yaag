#include "PlayerEntity.h"
#include "IDirection.h"
#include "ConGraphics.h"
#include "Projectile.h"
#include "Weapon.h"
#include "WeaponData.h"
#include "Armor.h"
#include "ArmorData.h"
#include "FileData.h"
#include "FileLogger.h"
#include "NullLogger.h"
#include "IMenuState.h"
#include "languagepack.h"
#include "FileIO.h"

// Include interface for game play
#include "IFriendlyEntity.h"

namespace Game{ namespace Player
{
	using Zaxis::Math::Vector2D;
	using Game::Items::Projectile::Projectile;
	using Game::Items::Weapons::WeaponData;
	using Zaxis::FileData;

	PlayerEntity::PlayerEntity(PlayerData* plData, int id, LPDATA dataCtrl) : IEntity(Zaxis::Entity::EntityType::ET_PLAYER)
	{
		_id = id;
		_dataCtrl = dataCtrl;
		data = *plData;
		Init();
		LoadWeapon(data.weaponId);
		LoadArmor(data.armorId);
	}

	PlayerEntity::~PlayerEntity()
	{
	}

	void PlayerEntity::Init()
	{
		// Create a null sound object
		_sound = new Zaxis::Sound::NullSound();

		// Set weapon to default weapon
		LoadDefaultWeapon();
		_armor = GetDefaultArmor();

		// Set player icon
		_myColor = ConColor::LtTorquoise;
		_myMesh.c = 234;
		_myMesh.color = _myColor;
		SetMesh(&_myMesh);

		_manager = NULL;
		_myHitColor = ConColor::LtRed;
		SetReady();
		// Define item list for hot keys
		for (int i = 0; i < 9; i++)
		{
			itemList[i] = 0;
		}
		LevelUp();

		PlayerWon = false;
		_monster = NULL;
	}

	void PlayerEntity::Dispose()
	{
	}

	LPOBJECT PlayerEntity::Update()
	{
		// Get access to the controller
		LPCONTROLLER ctrl = GetMover()->GetController();
		// Calculate the next time player can move
		data.character.NextMove = (data.character.NextMove + 1) % data.character.Move;
		data.character.NextAttack = min(data.character.NextAttack + 1, 100);
		if (data.character.NextMove == 0 && IsAlive())
		{
			if (GetMover()->GetController()->ChkInput(VK_SHIFT))
			{
				// Perform attack
				UpdateAttack();
			}
			else
			{
				// Player is able to move so process parent update method
				IEntity::Update();
				// Check if we can move to the new position
				if (!_manager->MoveEntity(this, GetOldPosition2D()) && 
					(GetPosition2D()->x != GetOldPosition2D()->x || GetPosition2D()->y != GetOldPosition2D()->y))
				{
					// Get world entity player ran into
					LPENTITY entity = _manager->GetEntity(GetPosition2D());
					LPFRIENDLY fEntity = dynamic_cast<LPFRIENDLY>(entity);
					// Move player back to old position
					GetPosition2D()->x = GetOldPosition2D()->x;
					GetPosition2D()->y = GetOldPosition2D()->y;
					// Check to make sure what we walked into is not the wall
					if (fEntity == NULL || !fEntity->IsFriendly(this))
					{
						UpdateAttack();
					}
				}
				if (_manager->IsExit(GetPosition2D()))
				{
					// Shutdown and exit game simulation
					_manager->Exit();
					// Pop this game state off the stack
					_menuState->PopState();
					return this;
				}// Endif square is arena exit

			}// Endif player is moving or attacking

		}
		else if (data.character.NextAttack > data.character.AttackSpeed && IsAlive() 
			&& (_rightWeapon->GetRange() == 1 || (_rightWeapon->GetRange() > 1 && GetMover()->GetController()->ChkInput(VK_SHIFT))))
		{
			UpdateAttack();
		}// Endif player can move

		if (PlayerWon)
		{
			// Shutdown and exit game simulation
			_manager->Exit();
			// Pop this game state off the stack
			_menuState->PushState(Game::Graphics::Menus::MenuState::MS_WIN);
			// Reset player so we can continue
			PlayerWon = false;
			return this;
		}

		// Check if the player is healing
		unsigned int healSpeed = max(1, 20 - (data.character.HealingSpeed * 2));
		if (data.character.HealingAmount > 0 && data.character.NextHealing++ > healSpeed)
		{
			int healAmount = max(1, 20 - data.character.HealingSpeed);
			// Reset heal interval
			data.character.NextHealing = 0;
			// Change heal amount per step
			data.character.Health = (data.character.Health + 1);
			if (data.character.Health > data.character.MaxHealth)
			{
				// Set health to max
				data.character.Health = data.character.MaxHealth;
				// Turn off healing affect: Turned this off to see how it would work with pre attack healing (I liked this off!)
				//data.character.HealingAmount = 0;
			}
			data.character.HealingAmount--;
		}

		if (_hitDuration > 0)
		{
			_hitDuration--;
			if (_hitDuration == 0)
			{
				_myMesh.color = _myColor;
			}
		}
		// Check if player has click the heal key
		unsigned int healCost = data.level.Level * 15;
		if (ctrl->ChkInput(CMD_HEALKEY) && data.level.Gold > healCost)
		{
			// Check if character is already healing
			if (data.character.HealingAmount == 0)
			{
				// Pay for healing
				data.level.Gold -= healCost;
				// Set heal amount based on character level
				data.character.HealingAmount = 10 + (10 * (data.level.Level)) - 1;
				// Set healing interval to start healing
				data.character.NextHealing = 0;
				data.character.Health++;
			}
		}

		// Game menu commands
		if (ctrl->ChkInput(CMD_LEVELUPKEY))
		{
			_menuState->PushState(Game::Graphics::Menus::MenuState::MS_LEVELUP);
		}

		// Update is done so return me
		return this;
	}// End method Update

	bool PlayerEntity::UpdateAttack()
	{
		bool bRetVal = false;

		LPDIRECTION mvr = dynamic_cast<LPDIRECTION>(GetMover());

		if (data.character.NextAttack > data.character.AttackSpeed)
		{
			// Check if a monster is pointing in the direction of the keyboard
			int range = _rightWeapon->GetRange();
			// Clone players position
			LPVECTOR2D pos = GetPosition2D();
			LPVECTOR2D attPos = pos->Clone();
			// Set the attack to false
			bool KeyedAttack = false;

			// Try and figure out which direction player is attacking
			if (mvr->MoveRight())
			{
				attPos->x++;
				KeyedAttack = true;
			}
			if (mvr->MoveLeft())
			{
				attPos->x--;
				KeyedAttack = true;
			}

			if (mvr->MoveUp())
			{
				attPos->y--;
				KeyedAttack = true;
			}
			if (mvr->MoveDown())
			{
				attPos->y++;
				KeyedAttack = true;
			}

			if (KeyedAttack)
			{
				if (range > 1)
				{
					// Shoot a projectile
					LPPROJECTILE projectile = new Projectile(new Vector2D(attPos->x - pos->x, attPos->y - pos->y), range, this);
					LPVECTOR2D projPos = attPos->Clone();
					// Configure projectile
					projectile->SetPosition2D(projPos)->SetSleeping(false);
					projectile->SetManager(_manager);
					// Add projectile to entity manager for tracking and drawing
					_manager->AddEntity(projectile);
					// Yeah we attack with a projectile
					bRetVal = true;
				}
				else
				{
					// Get entity from EntityManager
					LPENTITY entity = _manager->GetEntity(attPos);
					// Check if the entity is valid
					if (entity != NULL && entity != this)
					{
						// Convert entity to a monster
						LPATTACKER monster = dynamic_cast<LPATTACKER>(entity);
						// Check if we have a monster to attack and it isn't already dead
						if (monster != NULL && !monster->IsDead())
						{
							Log("PLAYER: Attacking!");
							// Attack monster
							Attack(monster);
						}// Endif monster is not NULL
						bRetVal = true;
					}// Endif entity is not NULL
				}// Endif range is greater than 1

				// Move the next attack reset to this code so that now all attack paths get reset
				if (bRetVal) data.character.NextAttack = 0;
			}
		}// Endif Player can attack
		return bRetVal;
	}

	void PlayerEntity::Draw(LPGRAPHICS gfx)
	{
		using Zaxis::Graphics::ConGraphics;
		ConGraphics* cGfx = dynamic_cast<ConGraphics*>(gfx);
		if (cGfx != NULL)
		{
			cGfx->DrawText("Player is to be drawn", 40, 26, ConColor::White);
		}
	}

	LPOBJECT PlayerEntity::SetUpdate(unsigned int interval)
	{
		// Set player update interval
		data.character.Move = interval;
		return this;
	}

	LPOBJECT PlayerEntity::SetSound(LPENGSOUND snd)
	{
		// Make sure to clean up the sound system
		if (_sound != NULL)
		{
			delete _sound;
			_sound = NULL;
		}
		// Set the sound object to provided pointer
		_sound = snd;
		// Return me 8-)
		return this;
	}

	LPENGSOUND PlayerEntity::Sound()
	{
		// Return my sound object
		return _sound;
	}

	void PlayerEntity::LoadDefaultWeapon()
	{
		LoadWeapon(HAND_WEAPON_ID);
	}

	LPPLAYERENTITY PlayerEntity::SetWeapon(WeaponData wpData)
	{
		// Check if we need to clean up weapon
		if (_rightWeapon != NULL)
		{
			// Cleaning up my mess
			delete _rightWeapon;
			_rightWeapon = NULL;
		}// Endif rightWeapoin is not null

		_rightWeapon = new Game::Items::Weapons::Weapon(wpData);
		data.weaponId = wpData.Id;

		// Return me
		return this;
	}

	LPPLAYERENTITY PlayerEntity::SetWeapon(unsigned int id)
	{
		data.weaponId = id;
		return this;
	}

	LPARMOR PlayerEntity::GetDefaultArmor()
	{
		// Return cloth armor as default armor
		Game::Items::Armor::Armor *defArmor = new Game::Items::Armor::Armor(_dataCtrl->GetArmor(1));
		return defArmor;
	}

	LPPLAYERENTITY PlayerEntity::SetArmor(LPARMOR armor)
	{
		// Store armor for player
		_armor = armor;
		return this;
	}

	LPPLAYERENTITY PlayerEntity::SetArmor(unsigned int id)
	{
		data.armorId = id;
		return this;
	}

	LPARMOR PlayerEntity::GetArmor()
	{
		// Return current equipped armor
		return _armor;
	}

	void PlayerEntity::Attack(LPATTACKER who)
	{
		if (rand == NULL)
		{
			Log("Error no random engine defined!!!!");
			return;
		}
		// Check if we have a valid entity to attack
		if (who != NULL)
		{
			int min = GetMinDamage();
			int max = GetDamage();
			unsigned int damage = rand->Next(GetMinDamage(), GetDamage()) + 1;
			int minRoll = 0 + (data.level.Level - 1) + GetWeapon()->GetPlus() - who->GetDefense();
			int maxRoll = 30;
			int attackRoll = rand->Next(minRoll, maxRoll);
			if (attackRoll > 20)
			{
				damage = damage * 2;
			}
			// Tell them they need to defend my attack
			who->Defend(attackRoll, damage);
			if (who->IsDead())
			{
				// Get monster's loot
				/*
				LPLOOT loot = who->GetLoot();
				if (loot != NULL)
				{
					// Update player statics
					double levelPerc = static_cast<double>(loot->data.level) / static_cast<double>(data.level.Level);
					int exp = static_cast<int>(static_cast<double>(loot->Exp) * levelPerc);
					int gold = static_cast<int>(static_cast<double>(loot->Gold) * levelPerc);
					data.level.Experience += exp;
					data.level.Gold += gold;
					// Delete loot object
					delete loot;
					loot = NULL;
					LevelUp();
				}// Endif loot is not NULL
				//*/
				// We won so time to exit the arena
				PlayerWon = true;
				_menuState->AddLoot(who->GetLoot());
				_monster = who;
			}
		}// Endif who is not NULL
	}

	unsigned int PlayerEntity::GetDamage()
	{
		LPCHARACTER cd = GetCharacter();
		// Return calculate damage for base damage and weapon damage combined
		return cd->AttackDamage + cd->AttackBonus;
	}

	unsigned int PlayerEntity::GetMinDamage()
	{
		LPCHARACTER cd = GetCharacter();
		return cd->AttackMinDamage + cd->AttackBonus;
	}

	int PlayerEntity::GetDefense()
	{
		LPCHARACTER cd = GetCharacter();
		return cd->DefenseRating + cd->DefenseBonus;
	}

	void PlayerEntity::Defend(int attackRoll, unsigned int damage)
	{
		// Process me being attacked
		unsigned int defense = GetDefense();
		// Check if the damage is greater then my defenses
		if (damage > defense || attackRoll > 19)
		{
			// I've been hurt so change my color
			unsigned int myDamage = damage;
			if (attackRoll < 20)
			{
				double percDamage = abs(static_cast<double>(attackRoll) + 10.0) / 30.0;
				myDamage = static_cast<unsigned int>(percDamage * static_cast<double>(damage));
			}

			std::ostringstream out;
			out << "MONSTER: hit for " << myDamage;
			Log(out.str());
			// Check if the damage is more then my available health
			if (myDamage >= data.character.Health)
			{
				// I am dead
				data.character.Health = 0;
				data.level.Experience += myDamage * 10;
				// TODO: Report to game engine we need to kill this object
				data.Deaths++;
				_manager->PlayerDead(_id);
			}
			else if (myDamage > 0)
			{
				_myMesh.color = _myHitColor;
				_hitDuration = 10;
				// Reduce my health, ouch that hurts!
				data.character.Health -= myDamage;
				data.level.Experience += (myDamage * 10);
				// Check if player can level up
				if ((data.level.Experience > data.level.NextLevelExp))
				{
					LevelUp();
				}
				// Rest attack cool down
				//data.character.NextAttack = 0;
			}
			else
			{
				Log("MONSTER: missed me what a wiffer!");
			}
		}
		else
		{
			Log("MONSTER: missed me what a wiffer!");
		}
	}

	bool PlayerEntity::IsAlive()
	{
		// Tell everyone if I'm alive!
		return data.character.Health > 0;
	}

	bool PlayerEntity::IsDead()
	{
		// Tell people if I'm dead
		return !IsAlive();
	}

	LPLOOT PlayerEntity::GetLoot()
	{
		// Give our my loot and reduce my player data
		Game::Data::Loot* loot = new Game::Data::Loot();
		loot->Exp = data.level.Level * 50;
		loot->Gold = data.level.Gold / 3;
		loot->Items = Game::Data::ItemList::IL_NONE;

		// Make sure we don't have negative gold
		data. level.Gold = max(0, data.level.Gold - loot->Gold);
		// Return loot object for me
		return loot;
	}

	void PlayerEntity::CalculateMove(unsigned int mSpeed)
	{
		// Calculate the movement speed based on the monster speed
		if (mSpeed > data.character.Speed)
		{
			SetUpdate(mSpeed - data.character.Speed + 1);
		}
		else
		{
			SetUpdate(1);
		}
	}

	unsigned int PlayerEntity::GetSpeed()
	{
		// Return how fast I am
		return data.character.Speed;
	}

	Game::Data::LevelData* PlayerEntity::GetLevel()
	{
		// Return my level object
		return &data.level;
	}

	Game::Data::CharacterData* PlayerEntity::GetStats()
	{
		// Return my character statistics
		return &data.character;
	}

	std::string PlayerEntity::GetName()
	{
		// Return my name
		return data.name;
	}

	LPWEAPONS PlayerEntity::GetWeapon()
	{
		// Return my weapon
		return _rightWeapon;
	}

	WORD PlayerEntity::GetColor()
	{
		return _myMesh.color;
	}

	LPPLAYERENTITY PlayerEntity::SetManager(Game::IEntityManager* manager)
	{
		// Set my entity manager
		_manager = manager;
		return this;
	}

	LPPLAYERENTITY PlayerEntity::SetRandom(LPRANDOM random)
	{
		// Set my random engine
		rand = random;
		return this;
	}

	LPPLAYERENTITY PlayerEntity::SetMenu(LPMENUSCREEN menu)
	{
		_plMenu = menu;
		return this;
	}

	LPPLAYERENTITY PlayerEntity::SetStateManager(LPMENUSTATE state)
	{
		_menuState = state;
		return this;
	}

	LPPLAYERENTITY PlayerEntity::LevelUp()
	{
		if (data.level.Experience > data.level.NextLevelExp)
		{
			while (data.level.Experience > data.level.NextLevelExp)
			{
				// Update player level and process all the updates to statistics
				data.level.Level++;
				data.level.PrevLevelExp = data.level.NextLevelExp;
				data.level.NextLevelExp = static_cast<unsigned int>(data.level.NextLevelExp * (2.0f - (data.level.Level * 0.02f)));
				unsigned int health = data.character.Con + 5;
				data.character.MaxHealth += health;
				data.character.Update();
				// Update player health stats
				data.character.Health = data.character.MaxHealth;
				data.character.HealingAmount = 0;
				data.character.NextHealing = 0;
			}
		}
		else if (data.level.Experience < data.level.PrevLevelExp)
		{
			while (data.level.Experience < data.level.PrevLevelExp)
			{
				data.level.Level--;
				if (data.level.PrevLevelExp < 500)
				{
					data.level.NextLevelExp = 500;
					data.level.PrevLevelExp = 0;
				}
				else
				{
					data.level.NextLevelExp = data.level.PrevLevelExp;
					data.level.PrevLevelExp = static_cast<int>(data.level.PrevLevelExp / (2.0f - (data.level.Level * 0.02f)));
				}
				unsigned int health = 5 + data.character.Con;
				data.character.MaxHealth -= health;
				// Make sure health doesn't flip to the end of the data
				data.character.Health = min(0, data.character.Health - health);
				data.character.AttackDamage = static_cast<unsigned int>((data.character.Str / 2) * 2.5);
				data.character.AttackSpeed = max(1, 15 - (data.level.Level / 3));
			}
		}

		return this;
	}

	bool PlayerEntity::IsAttackReady()
	{
		return data.character.NextAttack > data.character.AttackSpeed;
	}

	void PlayerEntity::AddItem(LPCHARACTER data)
	{
		// Add item to the back of the list
		items.push_back(data);
	}

	void PlayerEntity::RemoveItem(LPCHARACTER data)
	{
		// Need to find data element
		for (std::list<LPCHARACTER>::iterator it = items.begin(); it != items.end(); it++)
		{
			if (data->dataId == (*it)->dataId)
			{
				items.remove(*it);
				break;
			}
		}
	}

	LPCHARACTER PlayerEntity::GetCharacter()
	{

		// TODO: Need to cache this process so we don't create way to many version of this calulation.
		LPCHARACTER cd = new CharacterData();
		cd->Init(data.character);
		if (items.size() > 0)
		{
			// Add items to character data
			for (std::list<LPCHARACTER>::iterator it = items.begin(); it != items.end(); it++)
			{
				cd->Add(*it);
			}
		}// Endif items size is greater then 0

		return cd;
	}
	
	PlayerData* PlayerEntity::GetData()
	{
		return &data;
	}

	void PlayerEntity::SetData(PlayerData inData)
	{
		data = inData;
	}

	int PlayerEntity::LoadWeapon(unsigned int id)
	{
		int retVal = 0;
		WeaponData newData;

		newData = _dataCtrl->GetWeapon(id - 1);
		// Check if we have enough gold to pay for this item
		if (_rightWeapon != NULL)
		{
			RemoveItem(_rightWeapon->GetCharacter());
			delete _rightWeapon;
			_rightWeapon = NULL;
		}
		_rightWeapon = new Game::Items::Weapons::Weapon(newData);
		AddItem(_rightWeapon->GetCharacter());

		return retVal;
	}

	int PlayerEntity::LoadArmor(unsigned int id)
	{
		int retVal = 0;

		using Game::Items::Armor::Armor;
		if (_armor != NULL)
		{
			RemoveItem(_armor->GetCharacter());
			delete _armor;
			_armor = NULL;
		}
		ArmorData newData = _dataCtrl->GetArmor(id - 1);
		_armor = new Armor(newData);
		AddItem(_armor->GetCharacter());

		return retVal;
	}

	int PlayerEntity::GetObjectId()
	{
		return _id;
	}

	LPATTACKER PlayerEntity::GetMonster()
	{
		// Get address of monster
		LPATTACKER m = _monster;
		// Clear monster address out so we don't send the same monster twice
		_monster = NULL;
		return m;
	}

	int PlayerEntity::iGetLevel()
	{
		return data.level.Level;
	}

	void PlayerEntity::SetReady()
	{
		_myMesh.color = _myColor;
		_hitDuration = 0;
	}

} }// End namespace Game::Player


