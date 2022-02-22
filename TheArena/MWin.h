#ifndef H_MWIN
#define H_MWIN

#include <list>

#include "IMenuScreen.h"
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

	class MWin
		: public IMenuScreen
	{
	private:
		bool _isDirty;
		LPPLAYERENTITY _player;
		LPLOOT _loot;

		LPCONTROLLER _controller;
		LPMENUSTATE _manager;

		int _exp;
		int _gold;

		Zaxis::Math::Rect _box;
		WORD _boxColor;
		WORD _textColor;

		bool _hasFinished;

		std::list<LPLOOT> _lootChest;

	public:
		MWin(int x, int y, LPPLAYERENTITY player);
		virtual ~MWin();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();

		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual void SetStateManager(LPMENUSTATE manager);
		virtual void SetController(LPCONTROLLER ctrl);

		virtual void AddLoot(LPLOOT loot);
		virtual void CalculateLoot();
	};
} } }// End namespace Game::Graphics::Menus

#endif