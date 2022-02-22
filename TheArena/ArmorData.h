#ifndef H_ARMORDATA
#define H_ARMORDATA

#include "ItemList.h"
#include "CharacterData.h"

namespace Game{ namespace Data
{

	struct ArmorData
	{
		unsigned int id;
		ItemList type;
		ItemMaterial material;
		unsigned int defense;
		int plus;
		unsigned int price;
		unsigned int sellPrice;
		char name[30];

		CharacterData character;

		bool operator==(const ArmorData &a1);
		bool operator==(const ArmorData *a1);
	};

} }// End namespace Game::Stats

#endif