#ifndef H_IENTITYMANAGER
#define H_IENTITYMANAGER

#include "zmath.h"
#include "IEntity.h"

namespace Game
{
	class IEntityManager
	{
	public:
		IEntityManager();
		virtual ~IEntityManager();

		virtual bool MoveEntity(LPENTITY entity, LPVECTOR2D pos) = 0;
		virtual bool AddEntity(LPENTITY entity) = 0;
		virtual LPENTITY GetEntity(LPVECTOR2D pos) = 0;
		virtual bool RmEntity(LPENTITY entity, bool AutoSpawn=true) = 0;
		virtual void PlayerDead(int id) = 0;
		virtual bool IsExit(LPVECTOR2D pos) = 0;
		virtual void Exit() = 0;
	};
}

#endif;