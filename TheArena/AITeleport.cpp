#include "AITeleport.h"

namespace Game{ namespace Entity{ namespace Monsters{ namespace AI
{

	AITeleport::AITeleport(LPVECTOR2D player, LPVECTOR2D me, LPVECTOR2D exit, unsigned int distance, AI_Type type) : AISight(player, me, exit, distance, type)
	{
	}


	AITeleport::~AITeleport()
	{
	}

	void AITeleport::ProcessAttack()
	{
		// Teleport to new position
	}

	int AITeleport::GetRange()
	{
		return 1;
	}

	LPVECTOR2D AITeleport::GetRangedVelocity()
	{
		return NULL;
	}

} } } }// End namespace Game::Entity::Monsters::AI


