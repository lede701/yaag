#include "PlayerData.h"

bool Game::Data::PlayerData::operator==(const PlayerData &p1)
{
	return id == p1.id;
}
bool Game::Data::PlayerData::operator==(const PlayerData *p1)
{
	return id == p1->id;
}


namespace Game{ namespace Data
{

	bool PlayerSortExp(const PlayerData &p1, const PlayerData &p2)
	{
		bool bRetVal = false;
		// Check if experience is equal
		if (p1.level.Experience == p2.level.Experience)
		{
			bRetVal = p1.name < p2.name;
		}
		else
		{
			// Compate player by experience
			bRetVal = p1.level.Experience < p2.level.Experience;
		}

		return bRetVal;
	}// End function PlayerSortExp

	bool PlayerSortLevel(const PlayerData &p1, const PlayerData &p2)
	{
		bool bRetVal = false;

		if (p1.level.Level == p2.level.Level)
		{
			bRetVal = p1.name < p2.name;
		}
		else
		{
			bRetVal = p1.level.Level < p2.level.Level;
		}

		return bRetVal;
	}

} }