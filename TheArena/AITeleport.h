#ifndef H_AITELEPORT
#define H_AITELEPORT

#include "AISight.h"
#include "AI_Type.h"

namespace Game{ namespace Entity{ namespace Monsters{ namespace AI
{

	class AITeleport :
		public AISight
	{
	private:
	public:
		AITeleport(LPVECTOR2D player, LPVECTOR2D me, LPVECTOR2D exit, unsigned int distance, AI_Type type = AI_Type::AI_BLIND);
		virtual ~AITeleport();

		virtual void ProcessAttack();

		virtual int GetRange();
		virtual LPVECTOR2D GetRangedVelocity();

	};

} } } }// End namespace Game::Entity::Monsters::AI

#endif