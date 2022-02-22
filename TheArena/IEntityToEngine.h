#ifndef H_ENTITYTOENGINE
#define H_ENTITYTOENGINE

#include "IEntity.h"

#define LPENTITYENGINE Zaxis::Engines::IEntityToEngine*

namespace Zaxis{ namespace Engines
{

	class IEntityToEngine
	{
	public:
		IEntityToEngine();
		virtual ~IEntityToEngine();

		virtual LPENTITY AddEntity(LPENTITY obj, bool AddLogger = true) = 0;
		virtual bool RmEntity(LPENTITY obj) = 0;
		virtual void RmAll() = 0;
		virtual void Pause(bool pause) = 0;
	};

} }// End namespace Zaxis::Engines


#endif