#ifndef H_IMENUMONSTER
#define H_IMENUMONSTER

#include "IGraphics.h"
#include "MonsterEntity.h"

namespace Game{ namespace Graphics{ namespace Menus
{

	class IMenuMonster
	{
	public:
		IMenuMonster();
		~IMenuMonster();

		virtual void DrawMonster(LPGRAPHICS gfx, LPMONSTERENTITY monster) = 0;
	};

} } }// End namespace Game::Graphics::Menus

#endif