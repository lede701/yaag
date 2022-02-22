#ifndef H_IWEAPONS
#define H_IWEAPONS

#include <string>
#include "CharacterData.h"

#define LPWEAPONS Game::Items::Weapons::IWeapons*

namespace Game{ namespace Items{ namespace Weapons
{

	class IWeapons
	{
	public:
		IWeapons();
		virtual ~IWeapons();

		virtual unsigned int GetRange() = 0;
		virtual unsigned int GetDamage() = 0;
		virtual unsigned int GetAttackRating() = 0;
		virtual int GetPlus() = 0;
		virtual std::string GetName() = 0;
		virtual LPCHARACTER GetCharacter() = 0;
	};

} } }// End namespace Game::Items::Wepaons

#endif