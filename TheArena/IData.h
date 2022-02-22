#ifndef H_IDATA
#define H_IDATA

#include "ArmorData.h"
#include "MonsterData.h"
#include "WeaponData.h"
#include "DataLocation.h"

#define LPDATA Game::Data::IData*

namespace Game{ namespace Data
{
	using Zaxis::Data::DataLocation;

	class IData
	{
	public:
		virtual ArmorData GetArmor(int id) = 0;
		virtual MonsterData GetMonster(int id) = 0;
		virtual WeaponData GetWeapon(int id) = 0;

		virtual DataLocation GetLocation() = 0;
	};
} }// End namespace Game::Data

#endif