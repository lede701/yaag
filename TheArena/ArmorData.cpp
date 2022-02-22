#include "ArmorData.h"

bool Game::Data::ArmorData::operator==(const ArmorData &a1)
{
	return id == a1.id;
}

bool Game::Data::ArmorData::operator==(const ArmorData *a1)
{
	return id == a1->id;
}