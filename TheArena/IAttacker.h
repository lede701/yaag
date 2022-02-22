#ifndef H_IATTACKER
#define H_IATTACKER

#define LPATTACKER Game::IAttacker*

#include "Loot.h"
#include "CharacterData.h"

namespace Game
{

	class IAttacker
	{
	public:
		IAttacker();
		virtual ~IAttacker();

		virtual void Attack(LPATTACKER who) = 0;
		virtual void Defend(int attackRoll, unsigned int damage) = 0;
		virtual int GetDefense() = 0;
		virtual bool IsDead() = 0;
		virtual LPLOOT GetLoot() = 0;
		virtual bool IsAttackReady() = 0;
		virtual int iGetLevel() = 0;
		virtual LPCHARACTER GetCharacter() = 0;
	};

}// End namespace Game


#endif