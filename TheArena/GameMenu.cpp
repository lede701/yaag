#include "GameMenu.h"

#include <sstream>
#include <fstream>
#include <conio.h>

#include "ConGraphics.h"
#include "ConColor.h"
#include "BoxType.h"
#include "zmath.h"
#include "gamedefs.h"


namespace Game{ namespace Graphics{ namespace Menus
{
	using Zaxis::Graphics::ConGraphics;
	using Zaxis::Graphics::ConGraphicsData::ConColor;
	using Zaxis::Graphics::ConGraphicsData::BoxType;
	using namespace Zaxis::Math;

	GameMenu::GameMenu()
	{
		frameCnt = 0;
		_isDirty = true;
		IsLoggedIn = false;
		state = MS_WELCOME;
		_controller = NULL;
		rect = { 25, 5, 30, 7 };
	}


	GameMenu::~GameMenu()
	{
	}

	void GameMenu::Draw(LPGRAPHICS gfx)
	{
		switch (state)
		{
		case MS_WELCOME:
			DrawWelcome(gfx);
			break;
		case MS_LOGIN:
			DrawLogin(gfx);
			break;
		case MS_CREATENEW:
			DrawCreateNew(gfx);
			break;
		default:
			DrawMenu(gfx);
			break;
		}
		_isDirty = false;
	}

	void GameMenu::Clear(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		UCHAR c = 32;
		cGfx->DrawRect(&rect, &c, &c);
	}

	void GameMenu::DrawMenu(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		if (cGfx != NULL)
		{
			ostringstream out;
			Rect rect = { 20, 3, 40, 12 };
			WORD color = ConColor::White | ConColor::BkgPurple;
			cGfx->DrawFillRect(&rect, BoxType::Antique, color);

			int x = 23;
			int y = 3;

			out << (UCHAR)221 << " Arena Menu " << (UCHAR)222;
			x = (rect.Width / 2) + rect.X - (out.str().length() / 2);
			cGfx->DrawText(out.str(), x, y, color);
			out.str(""); out.clear();

			x = 23;
			y = 4;

			color = ConColor::BkgPurple | ConColor::LtYellow;

			cGfx->DrawText("Enter Arena", x, y++, color);
			cGfx->DrawText("Enter Armory", x, y++, color);
			cGfx->DrawText("Enter Potion Shop", x, y++, color);
			cGfx->DrawText("Enter Tavern", x, y++, color);

		}
	}

	void GameMenu::DrawLogin(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		if (cGfx != NULL)
		{
			cGfx->DrawFillRect(&rect, BoxType::Antique, ConColor::BkgBlue | ConColor::LtBlue);
			WORD color = ConColor::BkgBlue | ConColor::White;
			int x = rect.X + 3;
			int y = rect.Y + 2;
			std::string name;
			std::string passwd;
			cGfx->DrawText("Hero Name:", x, y, color);
			while (_kbhit()) _getch();
			name = GetInput(cGfx, x + 11, y, false, color);
			y++;
			cGfx->DrawText(" Password:", x, y, color);
			passwd = GetInput(gfx, x+11, y, true, color);
			y++;
			IsLoggedIn = true;
		}
	}

	std::string GameMenu::GetInput(LPGRAPHICS gfx, int x, int y, bool IsSecret, WORD color)
	{
		using std::cin;
		std::string sin;
		ConGraphics* cGfx = CONCAST(gfx);

		int ch = 0;
		do 
		{
			ch = _getch();
			if (ch != 13)
			{
				//ch = _toupper(ch);
				sin += (UCHAR)ch;
				if (IsSecret)
				{
					cGfx->DrawText("*", x++, y, color);
				}
				else
				{
					cGfx->DrawText(sin, x, y, color);
				}
			}
		} while (ch != 13);

		return sin;
	}

	void GameMenu::DrawWelcome(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		if (cGfx != NULL)
		{
			int x = 0;
			int y = 0;
			WORD color = ConColor::BkgBlue | ConColor::LtBlue;
			std::string line = "             ";
			line[0] = (UCHAR)221;
			line[12] = (UCHAR)222;
			cGfx->DrawFillRect(&rect, BoxType::Antique, color);
			cGfx->DrawText(line, 33, 5, color);
			color = ConColor::BkgBlue | ConColor::White;
			x = 27;
			y = 7;
			cGfx->DrawText("The Arena", 35, 5, color);
			cGfx->DrawText("[L] Login to The Arena", x, y++, color);
			cGfx->DrawText("[C] Create new Gladiator!", x, y++, color);
			cGfx->DrawText("[X] Exit game", x, y++, color);
		}
	}

	void GameMenu::DrawCreateNew(LPGRAPHICS gfx)
	{

	}

	void GameMenu::Update()
	{
		LPCONTROLLER ctrl = GetController();
		MenuState oState = state;
		switch (state)
		{
		case MS_WELCOME:
			if (ctrl->ChkInput('L'))
			{
				state = MS_LOGIN;
			}
			else if (ctrl->ChkInput('C'))
			{
				state = MS_CREATENEW;
			}
			else if (ctrl->ChkInput('X'))
			{
				state = MS_EXIT;
			}
			break;
		case MS_LOGIN:
			if (IsLoggedIn)
			{
				state = MS_MAINMENU;
			}
			break;
		}

		_isDirty = state != oState;
	}

	void GameMenu::SetController(LPCONTROLLER ctrl)
	{
		_controller = ctrl;
	}

	LPCONTROLLER GameMenu::GetController()
	{
		return _controller;
	}

	bool GameMenu::IsDirty()
	{
		return _isDirty;
	}

	void GameMenu::DirtyMe()
	{
		_isDirty = true;
	}

} } }// End namespace Game::Graphics::Menus

