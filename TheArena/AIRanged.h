#ifndef H_AIRANGED
#define H_AIRANGED

#include "AIMonster.h"

namespace Game{ namespace Entity{ namespace Monsters{ namespace AI
{
	class AIRanged
		: public AIMonster
	{
	private:
		unsigned int _distance;
		unsigned int sqr(unsigned int val);
		bool HasSeen;

		Zaxis::Math::Vector2D calcPos;
		Zaxis::Math::Vector2D velocity;

	public:
		AIRanged(LPVECTOR2D player, LPVECTOR2D me, LPVECTOR2D exit, unsigned int distance);
		virtual ~AIRanged();

		virtual bool ChkInput(int vk);
		void UpdateRange();

		virtual int GetRange();
		virtual LPVECTOR2D GetRangedVelocity();

	};

} } } }// End namespace Game::Entity::Monsters::AI

#endif