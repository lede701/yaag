#ifndef H_MFLEEWIN
#define H_MFLEEWIN

#include <list>

#include "IMenuScreen.h"
#include "IMenuState.h"
#include "PlayerEntity.h"
#include "MonsterEntity.h"
#include "PlayerMenu.h"
#include "ConGraphics.h"
#include "zmath.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	class MFleeWin
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

		std::list<LPLOOT> lootChest;

		bool _hasFinished;
	public:
		MFleeWin(int x, int y, LPPLAYERENTITY player);
		virtual ~MFleeWin();

		virtual void CalculateLoot();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();

		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual void SetStateManager(LPMENUSTATE manager);
		virtual void SetController(LPCONTROLLER ctrl);

		virtual void AddLoot(LPLOOT loot);
	};

} } }// End namespace Game::Graphics::Menu
#endif