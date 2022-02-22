#ifndef H_AISIGHT
#define H_AISIGHT

#include "AIMonster.h"
#include "AI_Type.h"

namespace Game{ namespace Entity{ namespace Monsters{ namespace AI
{

	class AISight :
		public AIMonster
	{
	private:
		unsigned int _distance;
		unsigned int sqr(unsigned int val);
		bool HasSeen;

		AI_Type _type;

	public:
		AISight(LPVECTOR2D player, LPVECTOR2D me, LPVECTOR2D exit, unsigned int distance, AI_Type type = AI_BLIND);
		virtual ~AISight();

		virtual bool ChkInput(int vk);

		virtual bool ChkBadVision(int vk);
		virtual bool ChkAsleep(int vk);

		virtual int GetRange();
		virtual LPVECTOR2D GetRangedVelocity();

	};


} } } }// End namespace Game::Entity::Monsters::AI

#endif