#ifndef H_FIELDBRICK
#define H_FIELDBRICK

#include "NullEntity.h"
#include "IEntityManager.h"
#include "IAttacker.h"
#include "IFriendlyEntity.h"

namespace Game{ namespace  Field
{ 
	class FieldBrick :
		public Zaxis::Entity::NullEntity, public Game::Entity::IFriendlyEntity
	{
	private:
		Game::IEntityManager* manager;

		unsigned int life;

	public:
		FieldBrick();
		virtual ~FieldBrick();

		virtual bool IsAlive();

		virtual bool IsFriendly(LPENTITY entity);

	};

} }


#endif