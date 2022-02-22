#ifndef H_ENTITY
#define H_ENTITY

#include <stdlib.h>

#include "EntityType.h"
#include "Object.h"
#include "IMover.h"

#define LPENTITY Zaxis::Entity::IEntity*

namespace Zaxis{ namespace Entity
{

	class IEntity :
		public Zaxis::Core::Object
	{
		LPMOVER _mover;
		void* _mesh;

		EntityType Type;
		LPVECTOR2D _oldPos;

	public:
		IEntity();
		IEntity(EntityType inType);

		virtual ~IEntity();

		virtual void Init();

		virtual LPOBJECT Update();

		virtual LPOBJECT SetPosition2D(LPVECTOR2D pos);

		LPENTITY SetMover(LPMOVER mover);
		LPMOVER GetMover();

		virtual LPENTITY SetMesh(void* mesh);
		virtual void* GetMesh();

		virtual LPENTITY SetOldPosition2D(LPVECTOR2D pos);
		virtual LPVECTOR2D GetOldPosition2D();

		//virtual void ClearMesh() = 0;

	};

} }// End namespace Zaxis::Entity

#endif