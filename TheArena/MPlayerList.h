#ifndef H_MPLAYERLIST
#define H_MPLAYERLIST

#include "BaseSelector.h"
#include "IMenuState.h"
#include "PlayerEntity.h"
#include "ConGraphics.h"
#include "zmath.h"
#include "PlayerData.h"

#include <time.h>
#include <list>

namespace Game{ namespace Graphics{ namespace Menus
{
	using Zaxis::Graphics::ConGraphicsData::ConColor;

	class MPlayerList
		: public BaseSelector
	{
	private:
		LPCONTROLLER _controller;
		LPMENUSTATE _stateManager;

		Zaxis::Math::Rect box;

		bool _isDirty;

		WORD boxColor;
		WORD color;
		WORD cmdColor;

		std::string plFile;
		int start;
		int count;
		int selectedLine;

		std::list<Game::Data::PlayerData> plList;

	public:
		MPlayerList(int x, int y);
		virtual ~MPlayerList();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();

		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual void SetStateManager(LPMENUSTATE manager);
		virtual void SetController(LPCONTROLLER ctrl);

		virtual Game::Data::PlayerData GetSelectedPlayer();
	};
} } }// End namespace Game::Graphics::Menus

#endif