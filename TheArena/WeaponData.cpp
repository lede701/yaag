#include "WeaponData.h"

bool Game::Data::WeaponData::operator== (const Game::Data::WeaponData &w2)
{
	return Id == w2.Id;
}

bool Game::Data::WeaponData::operator== (const Game::Data::WeaponData *w2)
{
	return Id == w2->Id;
}
