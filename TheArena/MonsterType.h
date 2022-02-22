#ifndef H_MONSTERTYPE
#define H_MONSTERTYPE
namespace Zaxis{ namespace Entity
{
	//////////////////////////////////////////////////////////////////////////
	/// Entity types are the VM definitions for the game engine
	//////////////////////////////////////////////////////////////////////////

	enum MonsterType
	{
		MT_NONE = 0x00,
		MT_BLOB = 0x01,
		MT_GOBLIN = 0x02,
		MT_SKELETON = 0x03
	};

} }// End namespace Zaxis::Entity

#endif