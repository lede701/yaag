#ifndef H_WEAPONDATA
#define H_WEAPONDATA

#include <string>
#include "ItemList.h"
#include "CharacterData.h"

namespace Game{ namespace Data
{ 

	struct WeaponData
	{
	public:
		unsigned int Id;
		ItemList type;
		ItemMaterial material;
		unsigned int damage;
		int plus;
		unsigned int range;
		unsigned int price;
		unsigned int sellPrice;
		unsigned char name[38];

		CharacterData character;

		bool operator==(const WeaponData &m1);
		bool operator==(const WeaponData *m1);
	};

} }//End namespace Game::Data

#endif