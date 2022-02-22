#ifndef H_MHOMECOMMANDS
#define H_MHOMECOMMANDS

#include "BaseSelector.h"
#include "IMenuState.h"
#include "PlayerEntity.h"
#include "PlayerMenu.h"
#include "ConGraphics.h"
#include "zmath.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	using Zaxis::Graphics::ConGraphics;
	using Zaxis::Graphics::ConGraphicsData::ConColor;
	using Zaxis::Graphics::ConGraphicsData::BoxType;

	class MHomeCommands
		: public BaseSelector
	{
		Zaxis::Math::Rect box;

		bool _isDirty;

		WORD textColor;
		WORD cmdColor;
		
	public:
		MHomeCommands(int x, int y);
		virtual ~MHomeCommands();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void DrawMenu(LPGRAPHICS gfx, LPVECTOR2D pos);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();

		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual void SetStateManager(LPMENUSTATE manager);
		virtual void SetController(LPCONTROLLER ctrl);
	};

} } }// End namespace Game::Graphics::Menus

#endif