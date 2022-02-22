#include <sstream>
#include "CtrlMenu.h"
#include "ConGraphics.h"
#include "gamedefs.h"
#include "FileData.h"
#include "WeaponData.h"
#include "languagepack.h"


namespace Game{ namespace Graphics{ namespace Menus
{

	using namespace Zaxis::Graphics;
	using namespace Zaxis::Graphics::ConGraphicsData;
	using namespace Zaxis::Math;
	using Zaxis::FileData;
	using Game::Data::WeaponData;

	CtrlMenu::CtrlMenu(int x, int y)
	{
		pos.x = x;
		pos.y = y;
		_isDirty = true;
		box = { pos.x, pos.y, 78, 11 };
	}


	CtrlMenu::~CtrlMenu()
	{
	}

	void CtrlMenu::Draw(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		int x = pos.x;
		int y = pos.y;
		// Draw player control box
		box = { pos.x, pos.y, 78, 11 };
		WORD color = ConColor::Black | ConColor::LtBlue;
		cGfx->DrawFillRect(&box, Antique, color);
		std::string line = std::string(78, (unsigned char)196);
		for (int i = 0; i < 80; i = i + 2)
		{
			line[i] = (unsigned char)205;
		}
		cGfx->DrawText(line, 1, y-1, ConColor::LtYellow | ConColor::BkgYellow);
		// Draw position for gold
		line = std::string(20, 32);
		line[0] = static_cast<unsigned char>(221);
		line[line.length() - 1] = static_cast<unsigned char>(222);
		cGfx->DrawText(line, 50, pos.y + 11, color);


		color = ConColor::Red;
		y = pos.y + 5;
		x = pos.x + 7;
		cGfx->DrawText("   [ ]", x, y++, color);
		cGfx->DrawText("[ ]   [ ]", x, y++, color);
		cGfx->DrawText("   [ ]", x, y++, color);
		std::string txt = "[     ] " + std::string(KEYATTACKMENU);
		cGfx->DrawText(txt, x, y + 1, color);

		// Draw keys for game menus
		x = pos.x + 50;
		y = pos.y + 2;
		txt = "[ ] " + std::string(CMD_LEVELUPTEXT);
		cGfx->DrawText(txt, x, y++, color);

		txt = "[ ] " + std::string(CMD_HEALTEXT);
		cGfx->DrawText(txt, x, y++, color);

		_isDirty = false;
	}

	void CtrlMenu::Clear(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		UCHAR c = 32;
		cGfx->DrawRect(&box, &c, &c);
	}

	void CtrlMenu::Update()
	{
	}

	bool CtrlMenu::Shutdown()
	{
		return false;
	}

	bool CtrlMenu::IsDirty()
	{
		return _isDirty;
	}

	void CtrlMenu::DirtyMe()
	{
		_isDirty = true;
	}

} } }// End namespace Game::Graphics::Menus