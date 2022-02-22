#include "AISight.h"

namespace Game{ namespace Entity{ namespace Monsters{ namespace AI
{

	AISight::AISight(LPVECTOR2D player, LPVECTOR2D me, LPVECTOR2D exit, unsigned int distance, AI_Type type) : AIMonster(player, me, exit)
	{
		_distance = distance;
		_type = type;
		HasSeen = false;
	}


	AISight::~AISight()
	{

	}

	bool AISight::ChkInput(int vk)
	{
		switch (_type)
		{
		case AI_ASLEEP:
			return ChkAsleep(vk);
			break;
		case AI_BLIND:
			return ChkBadVision(vk);
		}

		return false;
	}

	bool AISight::ChkBadVision(int vk)
	{
		unsigned int pDist = sqr(_player->x - _me->x) + sqr(_player->y - _me->y);
		if (pDist < sqr(_distance))
		{
			return AIMonster::ChkInput(vk);
		}

		return false;
	}

	bool AISight::ChkAsleep(int vk)
	{
		// Check if monster has not seen player
		if (!HasSeen)
		{
			// Calculate the distance form monster to player
			// A^2 + B^2 = C^2
			unsigned int pDist = sqr(_player->x - _me->x) + sqr(_player->y - _me->y);
			// AI calculation of my distance to player
			HasSeen = pDist < sqr(_distance);
		}

		// Check if player has been seen
		if (HasSeen)
		{
			// Process parent controller check input method
			return AIMonster::ChkInput(vk);
		}

		// No we can't move until the AI learn of player
		return false;
	}

	unsigned int AISight::sqr(unsigned int val)
	{
		return val * val;
	}

	int AISight::GetRange()
	{
		return 1;
	}

	LPVECTOR2D AISight::GetRangedVelocity()
	{
		return NULL;
	}

} } } }// End namespace Game::Entity::Monsters::AI