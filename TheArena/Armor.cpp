#include "Armor.h"
#include <fstream>
#include <sstream>

namespace Game{ namespace Items{ namespace Armor
{
	using std::ostringstream;
	using std::ifstream;
	using std::ofstream;

	Armor::Armor(ArmorData inData)
	{
		data = inData;
	}

	Armor::~Armor()
	{
	}

	void Armor::Init()
	{
		// Aha here is the bug, SQUASHING TIME!!
	}

	int Armor::GetDefense()
	{
		return data.character.DefenseRating;
	}

	int Armor::GetPlus()
	{
		return data.character.DefenseBonus;
	}

	std::string Armor::GetName()
	{
		ostringstream out;
		out << data.name;
		if (data.character.DefenseBonus > 0)
		{
			out << " +" << data.character.DefenseBonus;
		}
		else if (data.plus < 0)
		{
			out << " " << data.character.DefenseBonus;
		}

		return out.str();
	}

	void Armor::SetData(ArmorData* armor)
	{
		data = *armor;
		if (data.id == 0)
		{
			data.id = GetNextId();
		}
	}

	LPCHARACTER Armor::GetCharacter()
	{
		return &data.character;
	}

	int Armor::GetNextId()
	{
		int nextId = data.character.dataId + 1;
		// Return next id
		return nextId;
	}

} } }// End namespace Game::Items::Armor

