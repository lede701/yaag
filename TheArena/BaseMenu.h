#ifndef H_BASEMENU
#define H_BASEMENU

#include "IMenuScreen.h"
#include "zmath.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	using namespace Zaxis::Math;

	class BaseMenu :
		public IMenuScreen
	{
	private:
		bool _isDirty;
		Rect bkgBox;

	public:
		BaseMenu();
		virtual ~BaseMenu();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();
		virtual bool IsDirty();
		virtual void DirtyMe();
	};

} } }// End namespace Game::Graphics::Menus



#endif