#ifndef H_ENTITYTYPE
#define H_ENTITYTYPE

namespace Zaxis{ namespace Entity
{
	//////////////////////////////////////////////////////////////////////////
	/// Entity types are the VM definitions for the game engine
	//////////////////////////////////////////////////////////////////////////

	enum EntityType
	{
		ET_OBJECT = 0x00,
		ET_ENTITY = 0x01,
		ET_PLAYER = 0x02,
		ET_MONSTER = 0x03
	};

} }// End namespace Zaxis::Entity

#endif