#ifndef H_PLAYERMENU
#define H_PLAYERMENU

#include "IMenuScreen.h"
#include "PlayerEntity.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	using namespace Zaxis::Math;

	class PlayerMenu :
		public IMenuScreen
	{
	private:
		Vector2D pos;
		bool _isDirty;
		bool _playerDirty;
		Rect box;

	public:
		PlayerMenu(int x = 6, int y = 3, int width = 39, int height = 7);
		virtual ~PlayerMenu();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		
		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual void DrawPlayer(LPGRAPHICS gfx, LPPLAYERENTITY player);
		virtual void Update();
		virtual bool Shutdown();

	};

} } }// End namespace Game::Graphics::Menus

#endif