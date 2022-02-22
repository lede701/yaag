#ifndef H_PLAYERTYPE
#define H_PLAYERTYPE

namespace Zaxis{ namespace Entity
{
	//////////////////////////////////////////////////////////////////////////
	/// Player types are the VM definitions for the game engine
	//////////////////////////////////////////////////////////////////////////

	enum PlayerType
	{
		PT_LOCAL = 0x00,
		PT_NETWORK = 0x01,
		PT_AI = 0x02
	};

} }// End namespace Zaxis::Entity

#endif