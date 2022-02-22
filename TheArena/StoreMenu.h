#ifndef H_STOREMENU
#define H_STOREMENU

#include "BaseSelector.h"
#include "IMenuState.h"
#include "PlayerEntity.h"
#include "ConGraphics.h"
#include "IData.h"
#include "zmath.h"

#include <time.h>

#define MAX_SHOW_ITEMS 14

namespace Game{ namespace Graphics{ namespace Menus
{
	class StoreMenu
		: public BaseSelector
	{
	private:

		enum StoreTabs
		{
			ST_ARMOR = 0,
			ST_POTIONS = 1,
			ST_MELEE = 2,
			ST_RANGED = 3
		};

		struct TabData
		{
			StoreTabs type;
			unsigned int lineItem;
			unsigned int MaxItemsInList;
			unsigned int itemList[MAX_SHOW_ITEMS];
			unsigned int itemStart;
		};

		TabData TD[4];
		TabData* currentTD;
		
		// Game objects
		LPPLAYERENTITY _player;
		LPCONTROLLER _controller;
		LPMENUSTATE _stateManager;

		unsigned int currentTab;

		clock_t pauseTime;

		bool _isDirty;
		int pauseAmount;

		LPDATA _data;

		// Menu dimensions and position
		Zaxis::Math::Vector2D pos;
		Zaxis::Math::Rect box;

		// Menu color settings
		WORD color;
		//WORD textColor;
		//WORD highlightColor;
		WORD tabColor;
		WORD tabHighColor;

	public:
		StoreMenu(LPPLAYERENTITY player, int x, int y, LPDATA data);
		virtual ~StoreMenu();

		virtual void Draw(LPGRAPHICS gfx);
		//virtual void DrawLine(Zaxis::Graphics::ConGraphics* cGfx, std::string line, int x, int y, bool IsSelected);
		virtual int DrawTab(Zaxis::Graphics::ConGraphics* cGfx, std::string tab, int x, int y, bool IsSelected);
		virtual std::string ItemName(unsigned char name[38], int plus);
		virtual std::string ItemName(char name[30], int plus);

		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();

		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual void SetStateManager(LPMENUSTATE manager);
	};

} } }// End namsepsace Game::Graphics::Menus

#endif