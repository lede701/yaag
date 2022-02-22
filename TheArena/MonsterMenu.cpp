#include "MonsterMenu.h"
#include "ConGraphics.h"
#include "gamedefs.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	using Zaxis::Graphics::ConGraphicsData::ConColor;
	using Zaxis::Graphics::ConGraphicsData::BoxType;
	using Zaxis::Graphics::ConGraphics;

	MonsterMenu::MonsterMenu(int x, int y)
	{
		pos.x = x;
		pos.y = y;
		_current = NULL;
		_isDirty = true;
		box = { pos.x, pos.y, 39, 7 };
	}


	MonsterMenu::~MonsterMenu()
	{
	}

	void MonsterMenu::Draw(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);

		WORD color = ConColor::LtGreen | ConColor::BkgGreen;
		cGfx->DrawFillRect(&box, BoxType::Antique, color);

		int x = pos.x + 2;
		int y = pos.y + 2;

		cGfx->DrawText("Weapon", x, y++, color);
		cGfx->DrawText("Armor", x, y++, color);

		_isDirty = false;
		_monDirty = true;
	}

	void MonsterMenu::Clear(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		UCHAR c = 32;
		cGfx->DrawRect(&box, &c, &c);
	}

	void MonsterMenu::DrawMonster(LPGRAPHICS gfx, LPMONSTERENTITY monster)
	{
		ConGraphics* cGfx = dynamic_cast<ConGraphics*>(gfx);
		if (monster != _current || _monDirty)
		{
			Draw(gfx);
			WORD color = ConColor::White | ConColor::BkgGreen;
			std::ostringstream out;
			cGfx->DrawText("OPPONENT", 15, pos.y, ConColor::White | ConColor::BkgGreen);
			cGfx->DrawText((char)221, 14, pos.y, ConColor::LtGreen | ConColor::BkgGreen);
			cGfx->DrawText((char)222, 23, pos.y, ConColor::LtGreen | ConColor::BkgGreen);
			int x = 0;
			int y = pos.y + 2;

			std::string line = std::string(37, ' ');
			cGfx->DrawText(line, 2, pos.y + 1, ConColor::BkgPurple);
			out << monster->GetData()->name;
			x = (37 / 2) - (out.str().length() / 2);
			cGfx->DrawText(out.str(), x, pos.y + 1, ConColor::BkgPurple | ConColor::LtYellow);
			out.str(""); out.clear();

			x = pos.x + 9;
			out << monster->GetWeapon()->GetName();
			cGfx->DrawText(out.str(), x, y++, color);
			out.str(""); out.clear();

			out << monster->GetArmor()->GetName();
			cGfx->DrawText(out.str(), x, y++, color);
			out.str(""); out.clear();

			_current = monster;
			_monDirty = false;
		}


		// Draw monster lifebar
		int h = monster->GetCharacter()->Health;
		int mh = monster->GetCharacter()->MaxHealth;
		float size = (((float)h / (float)mh) * 28.0f);;
		std::string lifebar = "OPPONENT " + std::string((int)size, (unsigned char)219);
		lifebar += std::string(29 - static_cast<int>(size), ' ');
		cGfx->DrawText(lifebar, 41, 21, monster->GetColor() | ConColor::BkgRed);

	}

	void MonsterMenu::Update()
	{

	}

	bool MonsterMenu::Shutdown()
	{
		return false;
	}

	bool MonsterMenu::IsDirty()
	{
		return _isDirty;
	}

	void MonsterMenu::DirtyMe()
	{
		_isDirty = true;
	}

} } }// End namespace Game::Graphics::Menus
