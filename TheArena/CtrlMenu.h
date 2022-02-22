#ifndef H_CTRLMENU
#define H_CTRLMENU

#include "IMenuScreen.h"
#include "zmath.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	using namespace Zaxis::Math;

	class CtrlMenu :
		public IMenuScreen
	{
	private:
		Vector2D pos;
		bool _isDirty;
		Rect box;

	public:
		CtrlMenu(int x = 1, int y = 20);
		virtual ~CtrlMenu();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();
		virtual bool IsDirty();
		virtual void DirtyMe();
	};

} } }// End namesapce Game::Graphics::Menus

#endif