#ifndef H_AI_TYPE
#define H_AI_TYPE

namespace Game{ namespace Entity{ namespace Monsters{ namespace AI
{

	enum AI_Type
	{
		AI_BASIC =  0x00000001,
		AI_BLIND =  0x00000002,
		AI_ASLEEP = 0x00000004,
		AI_PATROL = 0x00000010,
		AI_RANGED = 0x00000020
	};

} } } }// End namespace Game::Entity::Monsters::AI
#endif