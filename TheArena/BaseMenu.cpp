#include <sstream>

#include "BaseMenu.h"
#include "ConGraphics.h"
#include "gamedefs.h"


namespace Game{ namespace Graphics{ namespace Menus
{
	using namespace Zaxis::Graphics;
	using namespace Zaxis::Graphics::ConGraphicsData;

	BaseMenu::BaseMenu()
	{
		_isDirty = true;
		bkgBox = { 0, 0, 80, 35 };
	}


	BaseMenu::~BaseMenu()
	{
	}

	void BaseMenu::Draw(LPGRAPHICS gfx)
	{
		std::ostringstream out;
		ConGraphics* cGfx = CONCAST(gfx);
		cGfx->DrawFillRect(&bkgBox, Antique, ConColor::Grey | ConColor::BkgRed);
		_isDirty = false;
	}

	void BaseMenu::Clear(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		UCHAR c = 32;
		cGfx->DrawRect(&bkgBox, &c, &c);
	}

	void BaseMenu::Update()
	{

	}

	bool BaseMenu::Shutdown()
	{
		return false;
	}

	bool BaseMenu::IsDirty()
	{
		return _isDirty;
	}

	void BaseMenu::DirtyMe()
	{
		_isDirty = true;
	}

} } }// End namespace Game::Graphics::Menus

