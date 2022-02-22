#ifndef H_MENULEVELUP
#define H_MENULEVELUP

#include "IMenuScreen.h"
#include "IMenuState.h"
#include "PlayerEntity.h"
#include "ConGraphics.h"
#include "zmath.h"

#include <time.h>

#define MAX_STATS 32

namespace Game{ namespace Graphics{ namespace Menus
{
	class MLevelUp
		: public IMenuScreen
	{
	private:
		bool _isDirty;
		Zaxis::Math::Vector2D pos;
		Zaxis::Math::Rect box;

		LPPLAYERENTITY _player;
		LPCONTROLLER _controller;
		LPMENUSTATE _stateManager;

		clock_t pauseTime;
		int pauseAmount;
		int statLine;
		int addStat[MAX_STATS];
		int availPoints;

		enum STATLINES
		{
			SL_STR = 0,
			SL_DEX = 1,
			SL_CON = 2,
			SL_INT = 3,
			SL_SPEED = 4,
			SL_HEAL = 5
		};

		Game::Data::PlayerData* plData;

	public:
		MLevelUp(LPPLAYERENTITY player, int x, int y);
		virtual ~MLevelUp();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void DrawLine(Zaxis::Graphics::ConGraphics* cGfx, std::string line, int x, int y, bool IsSelected);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();

		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual void SetStateManager(LPMENUSTATE manager);

	};
} } }// End namespace Game::Graphics::Menus

#endif