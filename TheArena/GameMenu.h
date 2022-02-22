#ifndef H_GAMEMENU
#define H_GAMEMENU

#include "IMenuScreen.h"
#include "Rect.h"
#include <Windows.h>

namespace Game{ namespace Graphics{ namespace Menus
{

	class GameMenu : 
		public IMenuScreen
	{
	private:
		int frameCnt;
		bool _isDirty;
		bool IsLoggedIn;

		enum MenuState
		{
			MS_WELCOME,
			MS_MAINMENU,
			MS_ARENA,
			MS_WEAPONS,
			MS_ARMOR,
			MS_POTIONS,
			MS_LOGIN,
			MS_CREATENEW,
			MS_EXIT
		};

		MenuState state;
		LPCONTROLLER _controller;
		Zaxis::Math::Rect rect;

	public:
		GameMenu();
		~GameMenu();

		// Draw menu
		virtual void Draw(LPGRAPHICS gfx);
		virtual void DrawLogin(LPGRAPHICS gfx);
		virtual void DrawMenu(LPGRAPHICS gfx);
		virtual void DrawCreateNew(LPGRAPHICS gfx);
		virtual void DrawWelcome(LPGRAPHICS gfx);

		virtual void Clear(LPGRAPHICS gfx);

		// Menu dirty state
		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual std::string GetInput(LPGRAPHICS gfx, int x, int y, bool IsSecret, WORD color);

		// Update menu
		virtual void Update();

		// Set controller
		void SetController(LPCONTROLLER ctrl);
		LPCONTROLLER GetController();
	};

} } }// End namespace Game::Graphics::Menus

#endif
