#ifndef H_IFRIENDLYENTITY
#define H_IFRIENDLYENTITY

#include "IEntity.h"

#define LPFRIENDLY Game::Entity::IFriendlyEntity*

namespace Game{ namespace Entity
{

	/// Use this interface to define if the entity can be check if it is friednly
	class IFriendlyEntity
	{
	public:
		IFriendlyEntity();
		~IFriendlyEntity();

		// Pass reference of entity that want to check if fridenly to entity
		virtual bool IsFriendly(LPENTITY entity) = 0;
	};

} }// End namespace Game::Entity


#endif