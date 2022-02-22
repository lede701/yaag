#ifndef H_MSELECT
#define H_MSELECT

#include "BaseSelector.h"
#include "IMenuState.h"
#include "IData.h"
#include "PlayerEntity.h"
#include "PlayerMenu.h"
#include "ConGraphics.h"
#include "MonsterData.h"
#include "zmath.h"
#include <list>

namespace Game{ namespace Graphics{ namespace Menus
{
	using Zaxis::Graphics::ConGraphics;
	using Zaxis::Graphics::ConGraphicsData::ConColor;
	using Zaxis::Graphics::ConGraphicsData::BoxType;
	using Game::Data::MonsterData;

	class MSelect
		: public BaseSelector
	{
	private:
		Zaxis::Math::Rect box;

		std::string mFile;

		bool _isDirty;

		LPCONTROLLER _controller;
		LPDATA _data;
		LPMENUSTATE _manager;

		WORD boxColor;
		WORD color;
		WORD cmdColor;
		WORD keyColor;

		std::list<MonsterData> list;
		std::list<MonsterData>::iterator mPos;

		unsigned int SelectedId;

		int MaxSize;
		int SelectPos;
		int StartPos;

	public:
		MSelect(int x, int y);
		virtual ~MSelect();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void DrawMenu(LPGRAPHICS gfx, LPVECTOR2D pos);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();

		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual void SetStateManager(LPMENUSTATE manager);
		virtual void SetController(LPCONTROLLER ctrl);
		virtual void SetDataController(LPDATA data);

		virtual unsigned int GetMonsterId();
	};

} } }// End namespace Game::Graphics::Menus

#endif