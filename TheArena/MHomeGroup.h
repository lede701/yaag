#ifndef H_MHOMEGROUP
#define H_MHOMEGROUP

#include "IMenuScreen.h"
#include "IMenuState.h"
#include "PlayerEntity.h"
#include "PlayerMenu.h"
#include "ConGraphics.h"
#include "zmath.h"

namespace Game{ namespace Graphics{ namespace Menus
{

	class MHomeGroup : public IMenuScreen
	{
	private:
		LPMENUSTATE _manager;
		LPCONTROLLER _controller;

		// Sub Menu items
		LPMENUSCREEN _bkg;
		LPMENUSCREEN _cmds;
		LPMENUSCREEN _field;
		PlayerMenu* _plMenu;

		LPPLAYERENTITY _player;

		bool _isDirty;
		bool _isRunning;
		Zaxis::Math::Rect box;

		// Menu color definitions
		WORD boxColor;

	public:
		MHomeGroup(int x, int y);
		virtual ~MHomeGroup();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();

		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual void SetStateManager(LPMENUSTATE manager);
		virtual void SetController(LPCONTROLLER ctrl);

		// Menu specific mutators
		virtual void SetPlayer(LPPLAYERENTITY player);
	};

} } }// End namespace Game::Graphics::Menus

#endif