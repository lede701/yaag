#ifndef H_PLAYERDATA
#define H_PLAYERDATA

#include <string>

#include "CharacterData.h"
#include "LevelData.h"
#include "MovementData.h"

#define PLDBVER 10

namespace Game{ namespace Data
{
	struct PlayerData
	{
	public:
		// Unique ID of player
		unsigned int id;
		
		// World Data
		char name[30];
		char passwd[65];

		// Game data
		CharacterData character;
		LevelData level;

		UINTSTAT Losses;
		UINTSTAT Wins;
		UINTSTAT Deaths; // Added to Version 6 of database

		// Weapon data
		unsigned int weaponId;
		// Armor data
		unsigned int armorId;

		bool operator==(const PlayerData &p1);
		bool operator==(const PlayerData *p1);
	};


	// Sort algorithm for player by experience
	bool PlayerSortExp(const PlayerData &p1, const PlayerData &p2);
	bool PlayerSortLevel(const PlayerData &p1, const PlayerData &p2);

} }


#endif