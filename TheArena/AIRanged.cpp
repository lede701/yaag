#include "AIRanged.h"

namespace Game{ namespace Entity{ namespace Monsters{ namespace AI
{
	
	AIRanged::AIRanged(LPVECTOR2D player, LPVECTOR2D me, LPVECTOR2D exit, unsigned int distance) : AIMonster(player, me, exit)
	{
		_distance = distance;
		_attackPos = new Zaxis::Math::Vector2D(0, 0);
	}

	AIRanged::~AIRanged()
	{

	}

	bool AIRanged::ChkInput(int vk)
	{
		bool bRetVal = false;
		// We want to try and get monster withing range
		unsigned int deltaX = abs(_me->x - _player->x);
		unsigned int deltaY = abs(_me->y - _player->y);
		unsigned int dist = deltaX + deltaY;
		if (dist > _distance || (deltaX != deltaY && deltaX != 0 && deltaY != 0))
		{
			if (calcPos.x != _player->x || calcPos.y != _player->y)
			{
				UpdateRange();
			}

			// Haandle X Movement
			if (velocity.x > 0 && vk == 'A')
			{
				bRetVal = true;
			}
			if (velocity.x < 0 && vk == 'D')
			{
				bRetVal = true;
			}

			// Handle Y Movement
			if (velocity.y > 0 && vk == 'W')
			{
				bRetVal = true;
			}
			if (velocity.y < 0 && vk == 'S')
			{
				bRetVal = true;
			}
		}
		else if (dist < _distance)
		{
			if (vk == VK_SHIFT)
			{
				bRetVal = true;
				_attackPos->x = _player->x;
				_attackPos->y = _player->y;
				UpdateRange();
			}
		}

		return bRetVal;
	}

	void AIRanged::UpdateRange()
	{
		float fastAttack = 1000000.0f;
		// Need to build a list of possible attack points
		Zaxis::Math::Vector2D *points[8];
		int pdx = 0;
		points[pdx++] = new Zaxis::Math::Vector2D(_player->x + 1, _player->y);			//  1, 0
		points[pdx++] = new Zaxis::Math::Vector2D(_player->x + 1, _player->y - 1);		//  1,-1
		points[pdx++] = new Zaxis::Math::Vector2D(_player->x, _player->y - 1);			//  0,-1
		points[pdx++] = new Zaxis::Math::Vector2D(_player->x - 1, _player->y - 1);		// -1,-1
		points[pdx++] = new Zaxis::Math::Vector2D(_player->x - 1, _player->y);			// -1, 0
		points[pdx++] = new Zaxis::Math::Vector2D(_player->x - 1, _player->y + 1);		// -1, 1
		points[pdx++] = new Zaxis::Math::Vector2D(_player->x, _player->y + 1);			//  0, 1
		points[pdx++] = new Zaxis::Math::Vector2D(_player->x + 1, _player->y + 1);		//  1, 1
		for (int i = 0; i < 8; i++)
		{
			float nDist = (float)((_me->x - points[i]->x) * (_me->x - points[i]->x)) + (float)((_me->y - points[i]->y) * (_me->y - points[i]->y));
			//nDist = sqrt(nDist);
			if (nDist < fastAttack)
			{
				fastAttack = nDist;
				pdx = i;
			}
		}

		// Now we have the best attack vector find the best position to attack from
		bool FindingAttack = true;
		velocity.x = points[pdx]->x - _player->x;
		velocity.y = points[pdx]->y - _player->y;

	}

	int AIRanged::GetRange()
	{
		unsigned int dist = abs(_player->x - _me->x) + abs(_player->y - _me->y);
		return _distance;
	}

	LPVECTOR2D AIRanged::GetRangedVelocity()
	{
		return velocity.Clone(true);
	}

} } } }// End namespace Game::Entity::Monsters::AI