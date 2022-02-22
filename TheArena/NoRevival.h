#ifndef H_NOREVIVAL
#define H_NOREVIVAL

#include "IMenuScreen.h"
#include "IMenuState.h"
#include "PlayerEntity.h"
#include "zmath.h"


namespace Game{ namespace Graphics{ namespace Menus
{

	class NoRevival
		: public IMenuScreen
	{
	private:
		bool _isDirty;
		Zaxis::Math::Vector2D pos;
		Zaxis::Math::Rect box;

		LPPLAYERENTITY _player;
		LPCONTROLLER _controller;
		LPMENUSTATE _stateManager;

	public:
		NoRevival(int x, int y);
		virtual ~NoRevival();

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