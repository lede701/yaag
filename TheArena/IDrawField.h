#ifndef H_IDRAWFIELD
#define H_IDRAWFIELD

#define LPDRAWFIELD Game::Graphics::IDrawField*
#include "MonsterEntity.h"

namespace Game{ namespace Graphics{

	class IDrawField
	{
	public:
		IDrawField();
		virtual ~IDrawField();

		virtual void DrawField() = 0;
		virtual void PlayerDied() = 0;

		virtual void SetMonster(LPMONSTERENTITY monster) = 0;
	};


} }// End namespace Game::Graphics



#endif