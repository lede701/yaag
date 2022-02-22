#ifndef H_AIMONSTER
#define H_AIMONSTER

#include <Windows.h>
#include "IController.h"
#include "IAttacker.h"
#include "zmath.h"

namespace Game{ namespace Entity{ namespace Monsters{ namespace AI
{

	class AIMonster :
		public Zaxis::Controllers::IController
	{
	protected:
		LPVECTOR2D _player;
		LPVECTOR2D _me;
		LPVECTOR2D _attackPos;
		LPVECTOR2D _exit;

		bool BeenHit;
		bool _doIFlee;

	public:
		AIMonster(LPVECTOR2D player, LPVECTOR2D me, LPVECTOR2D exit);
		virtual ~AIMonster();

		virtual void Update();

		virtual bool ChkInput(int vk);
		virtual char GetInput();
		virtual void ProcessAttack();
		virtual LPVECTOR2D GetAttackPos();
		virtual int GetRange() = 0;
		virtual LPVECTOR2D GetRangedVelocity() = 0;

		virtual bool DoIFlee(LPATTACKER player, LPATTACKER me);
	};

} } } }// End namespace Game::Entity::Monsters::AI
#endif