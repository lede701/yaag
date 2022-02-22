#ifndef _X86
#define _X86
#endif

#include "MonsterData.h"

bool Game::Data::MonsterData::operator== (const Game::Data::MonsterData &m2)
{
	return id == m2.id;
}

bool Game::Data::MonsterData::operator== (const Game::Data::MonsterData *m2)
{
	return id == m2->id;
}

namespace Game{ namespace Data
{
	bool CompareMonsterLevel(const Game::Data::MonsterData &first, const Game::Data::MonsterData &second)
	{
		if (first.level == second.level)
		{
			unsigned int i = 0;
			while (i++ < 35)
			{
				if (first.name[i] < second.name[i])
				{
					return true;
				}
				else if (first.name[i] > second.name[i])
				{
					return false;
				}
			}
		}
		else
		{
			return first.level < second.level;
		}

		return false;
	}

} }// End namespace Game::Data