#include "Weapon.h"

#include <fstream>
#include <sstream>

namespace Game{ namespace Items{ namespace Weapons
{

	Weapon::Weapon(WeaponData inData)
	{
		data = inData;
	}

	Weapon::~Weapon()
	{
	}

	unsigned int Weapon::GetRange()
	{
		return data.character.AttackRange;
	}

	unsigned int Weapon::GetAttackRating()
	{
		return data.character.AttackBonus;
	}

	unsigned int Weapon::GetDamage()
	{
		return data.character.AttackDamage;
	}

	int Weapon::GetPlus()
	{
		return data.character.AttackBonus;
	}

	std::string Weapon::GetName()
	{
		std::ostringstream out;
		out << data.name;
		if (data.character.AttackBonus > 0)
		{
			out << " +" << data.character.AttackBonus;
		}
		else if (data.plus < 0)
		{
			out << " -" << data.character.AttackBonus;
		}
		return out.str();
	}

	LPCHARACTER Weapon::GetCharacter()
	{
		return &data.character;
	}

} } }// End namespace Game::Items::Weapons