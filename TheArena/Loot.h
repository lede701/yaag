#ifndef H_LOOT
#define H_LOOT

#include <Windows.h>
#include "MonsterData.h"

#define LPLOOT Game::Data::Loot*

namespace Game{ namespace Data
{
	struct Loot
	{
	public:
		unsigned int Gold;
		unsigned int Exp;
		Game::Data::MonsterData data;

		WORD Items;
	};
} }// End namespace Game::Data

#endif