#ifndef H_GAMEOVER
#define H_GAMEOVER

#include "IMenuScreen.h"
#include "IMenuState.h"
#include "PlayerEntity.h"
#include "zmath.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	using namespace Zaxis::Math;

	class GameOver :
		public IMenuScreen
	{
	private:
		bool _isDirty;
		Vector2D pos;
		Rect box;

		LPPLAYERENTITY _player;
		LPCONTROLLER _controller;
		LPMENUSTATE _stateManager;

	public:
		GameOver(int x, int y);
		virtual ~GameOver();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();

		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual void SetPlayer(LPPLAYERENTITY player);
		virtual void SetStateManager(LPMENUSTATE manager);
	};

} } }// End namespace Game::Graphics::Menus

#endif