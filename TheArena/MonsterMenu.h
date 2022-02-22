#ifndef H_MONSTERMENU
#define H_MONSTERMENU

#include "IMenuScreen.h"
#include "IMenuMonster.h"
#include "MonsterEntity.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	using namespace Zaxis::Math;

	class MonsterMenu :
		public IMenuScreen, public IMenuMonster
	{
	private:
		Vector2D pos;
		LPMONSTERENTITY _current;
		bool _isDirty;
		bool _monDirty;
		Rect box;

	public:
		MonsterMenu(int x, int y);
		virtual ~MonsterMenu();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void DrawMonster(LPGRAPHICS gfx, LPMONSTERENTITY monster);
		virtual void Update();
		virtual bool Shutdown();

		virtual bool IsDirty();
		virtual void DirtyMe();
	};

} } }// End namespace Game::Graphics::Menus

#endif