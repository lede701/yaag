#include "AIMonster.h"
#include "CharacterData.h"

namespace Game{ namespace Entity{ namespace Monsters{ namespace AI
{

	AIMonster::AIMonster(LPVECTOR2D player, LPVECTOR2D me, LPVECTOR2D exit)
	{
		_player = player;
		_me = me;
		_attackPos = me->Clone();
		_exit = exit;
		_doIFlee = false;  // Of course I don't flee what kind of monster to you take me for?
	}


	AIMonster::~AIMonster()
	{
	}

	void AIMonster::Update()
	{

	}

	bool AIMonster::ChkInput(int vk)
	{
		LPVECTOR2D goal = _player->Clone();
		if (_doIFlee)
		{
			goal = _exit->Clone();
			int dx = abs(_me->x - goal->x);
			if (dx > 1)
			{
				// Goal needs to be a little lower then the exit so we don't walk on the fence
				goal->y++;
			}
		}
		// Calculate the distance from player
		int deltaX = abs(_me->x - goal->x);
		int deltaY = abs(_me->y - goal->y);
		int dist = deltaX + deltaY;
		int AttackDistance = 2;
		if (deltaX > 1 || deltaY > 1 || dist > AttackDistance || _doIFlee)
		{
			// Handle X movement
			if (_me->x > goal->x && vk == 'A')
			{
				return true;
			}
			if (_me->x < goal->x && vk == 'D')
			{
				return true;
			}

			// Handle Y Movement
			if (_me->y > goal->y && vk == 'W')
			{
				return true;
			}
			if (_me->y < goal->y && vk == 'S')
			{
				return true;
			}
		}
		else if (dist < AttackDistance && vk == VK_SHIFT)
		{
			// Need to figure out if we can attack on the grid based on the 8 directions
			bool bRetVal = deltaX == deltaY || (deltaX > 0 && deltaY == 0) || (deltaY > 0 && deltaX == 0);
			_attackPos->x = _player->x;
			_attackPos->y = _player->y;
			return bRetVal;
		}

		// Clean up my memory mess err sorry mom!
		delete goal;

		return false;
	}

	char AIMonster::GetInput()
	{
		return 0;
	}
	
	// Something to do when I get attacked
	void AIMonster::ProcessAttack()
	{
	}

	LPVECTOR2D AIMonster::GetAttackPos()
	{
		return _attackPos;
	}

	bool AIMonster::DoIFlee(LPATTACKER enemy, LPATTACKER me)
	{
		_doIFlee = false;
		// Need to figure out if I can beat this enemy
		LPCHARACTER enemyChar = enemy->GetCharacter();
		LPCHARACTER meChar = me->GetCharacter();

		int enemyScore = enemyChar->GetScore();
		// This score is not calulating properly need to step into this line
		int meScore = meChar->GetScore();
		float myLifePercent = static_cast<float>(meChar->Health) / static_cast<float>(meChar->MaxHealth);
		float ourDiffernce = static_cast<float>(meScore) / static_cast<float>(enemyScore);
		// Check if we have a tough enemy
		if ((myLifePercent < 0.50f && ourDiffernce < 0.50f) || (ourDiffernce < 0.40))
		{
			// Yikes this enemy is to tough for me so I need to run away
			_doIFlee = true;
		}

		return _doIFlee;
	}

} } } } // End namespace Game::Entity::Monsters::AI
