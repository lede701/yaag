#ifndef H_MONSTERDATA
#define H_MONSTERDATA

#include <windows.h>
#include <list>

#include "MonsterEnum.h"
#include "AI_Type.h"
#include "MovementData.h"
#include "CharacterData.h"

#define LPMONSTERDATA Game::Monsters::Entities::MonsterData*

namespace Game{ namespace Data
{
	// 80 Bytes
	struct MonsterData
	{
	public:
		int id;
		Game::Monsters::Entities::MonsterType type;
		Game::Entity::Monsters::AI::AI_Type AI;
		char name[35];
		/*
		unsigned int health;
		unsigned int maxHealth;
		unsigned int attackSpeed;
		unsigned int nextAttack;
		unsigned int defense;
		unsigned int minDamage;
		unsigned int damage;
		//*/
		unsigned int level;

		unsigned int weaponId;
		unsigned int armorId;

		CharacterData character;

		unsigned char mesh;
		WORD color;
		WORD hitColor;

		bool operator==(const MonsterData &m1);
		bool operator==(const MonsterData *m1);
	};


	bool CompareMonsterLevel(const MonsterData &first, const MonsterData &second);

} }// End namespace Game::Data

#endif