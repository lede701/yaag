#ifndef H_IARMOR
#define H_IARMOR

#include <string>
#include "CharacterData.h"

#define LPARMOR Game::Items::Armor::IArmor*

namespace Game{ namespace Items{ namespace Armor
{

	class IArmor
	{
	public:
		IArmor();
		virtual ~IArmor();

		virtual int GetDefense() = 0;
		virtual int GetPlus() = 0;
		virtual std::string GetName() = 0;
		virtual LPCHARACTER GetCharacter() = 0;
	};

} } }// End namespace Game::Items::Armor


#endif