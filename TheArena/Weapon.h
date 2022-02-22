#ifndef H_WEAPONS
#define H_WEAPONS

#include "IWeapons.h"
#include "WeaponData.h"
#include "FileData.h"

namespace Game{ namespace Items{ namespace Weapons
{
	using namespace Game::Data;
	using Zaxis::FileData;
	using Game::Data::CharacterData;
	
	class Weapon :
		public IWeapons
	{
	private:
		WeaponData data;
		std::string file;

	public:
		Weapon(WeaponData inData);
		virtual ~Weapon();

		virtual unsigned int GetRange();
		virtual unsigned int GetDamage();
		virtual unsigned int GetAttackRating();
		virtual int GetPlus();
		virtual std::string GetName();

		virtual LPCHARACTER GetCharacter();
	};

} } }// End namespace Game::Items::Weapons
#endif