#ifndef H_MPLAYERINFO
#define H_MPLAYERINFO

#include "BaseSelector.h"
#include "IMenuState.h"
#include "PlayerEntity.h"
#include "ConGraphics.h"
#include "zmath.h"
#include "PlayerData.h"

#include <time.h>

namespace Game{ namespace Graphics{ namespace Menus
{
	using Zaxis::Graphics::ConGraphicsData::ConColor;

	class MPlayerInfo
		: public BaseSelector
	{
	private:
		LPCONTROLLER _controller;
		LPMENUSTATE _stateManager;

		bool _isDirty;

		Zaxis::Math::Rect box;

		WORD color;
		WORD boxColor;
		WORD statColor;
		WORD cmdColor;

		Game::Data::PlayerData player;

		// File paths
		std::string aFile;
		std::string wFile;

	public:
		MPlayerInfo(int x, int y);
		virtual ~MPlayerInfo();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();

		virtual bool IsDirty();
		virtual void DirtyMe();

		// Menu state manager
		virtual void SetStateManager(LPMENUSTATE manager);
		// Menu keyboard controller (Doesn't have to be a direct connection to the keyboard)
		virtual void SetController(LPCONTROLLER ctrl);
		// Player data mutator
		virtual void SetPlayer(Game::Data::PlayerData pl);

	};
} } }// End namespace Game::Graphics::Menus

#endif