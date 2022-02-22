#ifndef H_MONSTERENUM
#define H_MONSTERENUM

namespace Game{ namespace Monsters{ namespace Entities
{ 
	
	enum MonsterType
	{
		MT_BASIC =  0x00000001,
		MT_HUMAN =  0x00000002,
		MT_DOG =    0x00000004,
		MT_ELF =    0x00000008,
		MT_ORC =    0x00000010,
		MT_DWARF =  0x00000020,
		MT_OGRE =   0x00000040,
		MT_GIANT =  0x00000080,
		MT_SNAKE =  0x00000100,
		MT_LIZARD = 0x00000200,
		MT_LION   = 0x00000400,
		MT_CAT    = 0x00000800
	};

} } }// End namespace Game::Monsters::Entities

#endif