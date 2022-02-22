#ifndef H_IMENUSCREEN
#define H_IMENUSCREEN

#include "IGraphics.h"
#include "IUpdater.h"

#define LPMENUSCREEN Game::Graphics::Menus::IMenuScreen*

namespace Game{ namespace Graphics{ namespace Menus
{

	class IMenuScreen :
		public Zaxis::Engine::IUpdater
	{
	public:
		IMenuScreen();
		virtual ~IMenuScreen();

		virtual void Draw(LPGRAPHICS gfx) = 0;
		virtual void Clear(LPGRAPHICS gfx) = 0;
		virtual void Update() = 0;

		virtual bool IsDirty() = 0;
		virtual void DirtyMe() = 0;
	};

} } }// End namespace Game::Graphics::Menus


#endif