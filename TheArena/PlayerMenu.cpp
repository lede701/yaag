#include <sstream>

#include "PlayerMenu.h"
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

	PlayerMenu::PlayerMenu(int x, int y, int width, int height)
	{
		pos.x = x;
		pos.y = y;
		_isDirty = true;
		_playerDirty = true;
		box = { pos.x - 5, pos.y, width, height };
	}


	PlayerMenu::~PlayerMenu()
	{
	}

	void PlayerMenu::Draw(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		std::ostringstream out;
		// Draw the main backdrop for the game
		WORD color = ConColor::LtBlue | ConColor::BkgBlue;
		cGfx->DrawFillRect(&box, Antique, color);
		cGfx->DrawText((char)221, 17, pos.y, color);
		cGfx->DrawText((char)222, 21, pos.y, color);
		color = ConColor::LtYellow | ConColor::BkgBlue;

		// Create a way to manage the line we are drawing on
		int x = pos.x;
		int y = pos.y + 2;

		out << PG_YOU;
		cGfx->DrawText(out.str(), 18, pos.y, color);
		out.str(""); out.clear();

		out << PG_WEAPON;
		cGfx->DrawText(out.str(), x, y++, color);
		out.str(""); out.clear();

		out << PG_ARMOR;
		cGfx->DrawText(out.str(), x+1, y++, color);
		out.str(""); out.clear();

		out << PG_HEALTH;
		cGfx->DrawText(out.str(), x, y++, color);
		out.str(""); out.clear();

		out << PG_LEVEL;
		cGfx->DrawText(out.str(), x+1, y++, color);
		out.str(""); out.clear();

		out << PG_EXPERIENCE;
		cGfx->DrawText(out.str(), x + 2, y++, color);
		out.str(""); out.clear();

		if (box.Height > 7)
		{
			// Draw extended stats
			out << PS_STR;
			cGfx->DrawText(out.str(), x + 3, y++, color);
			out.str(""); out.clear();

			out << PS_DEX;
			cGfx->DrawText(out.str(), x + 3, y++, color);
			out.str(""); out.clear();

			out << PS_CON;
			cGfx->DrawText(out.str(), x + 3, y++, color);
			out.str(""); out.clear();

			out << PS_SPEED;
			cGfx->DrawText(out.str(), x + 1, y++, color);
			out.str(""); out.clear();

		}

		_isDirty = false;
		_playerDirty = true;

	}

	void PlayerMenu::Clear(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		UCHAR c = 32;
		cGfx->DrawRect(&box, &c, &c);
	}

	void PlayerMenu::DrawPlayer(LPGRAPHICS gfx, LPPLAYERENTITY player)
	{
		ConGraphics* cGfx = dynamic_cast<ConGraphics*>(gfx);
		ostringstream out;
		WORD color = ConColor::BkgBlue | ConColor::White;
		WORD gldColor = ConColor::Black | ConColor::LtYellow;
		int x = 0;
		int y = pos.y + 1;
		LPCHARACTER ch = player->GetCharacter();

		if (_playerDirty)
		{
			out << player->GetName();
			x = 20 - (out.str().length() / 2);
			std::string str = std::string(37, ' ');
			cGfx->DrawText(str, 2, y, ConColor::LtYellow | ConColor::BkgTorquoise);
			cGfx->DrawText(out.str(), x, y++, ConColor::LtYellow | ConColor::BkgTorquoise);
			out.str(""); out.clear();

			x = pos.x + 7;
			out << player->GetWeapon()->GetName() << " (" << player->GetWeapon()->GetDamage() << ")";
			cGfx->DrawText(out.str(), x, y++, color);
			out.str(""); out.clear();

			out << player->GetArmor()->GetName() << " (" << player->GetArmor()->GetDefense() << ")";
			cGfx->DrawText(out.str(), x, y++, color);
			out.str(""); out.clear();

			_playerDirty = false;
		}
		else
		{
			x = pos.x + 7;
			y += 3;
		}

		out << ch->Health << "(" << ch->MaxHealth << ")";
		cGfx->DrawText(out.str(), x, y++, color);
		out.str(""); out.clear();

		out << player->GetLevel()->Level;
		cGfx->DrawText(out.str(), x, y++, color);
		out.str(""); out.clear();

		// Calculate the experience bar
		double percComp = static_cast<double>(player->GetLevel()->Experience - player->GetLevel()->PrevLevelExp) /
			static_cast<double>(player->GetLevel()->NextLevelExp - player->GetLevel()->PrevLevelExp);
		int compBar = 24;
		// Make sure that we don't go over complete
		if (percComp < 1.0f)
		{
			compBar = compBar * percComp;
		}
		std::string bar(compBar, 219);
		std::string sbar(24 - compBar, 176);
		// Draw experience bar
		out << bar << sbar;
		if ((player->GetLevel()->Level * 5) > player->GetLevel()->AssignedPoints)
		{
			out << "+";
		}

		cGfx->DrawText(out.str(), x, y++, color);
		out.str(""); out.clear();

		out << "Gold " << player->GetLevel()->Gold << "  ";
		cGfx->DrawText(out.str(), 52, 34, gldColor);
		out.str(""); out.clear();

		// Check if player is in the home screen
		if (box.Height > 7)
		{ 
			out << ch->Str;
			cGfx->DrawText(out.str(), x, y++, color);
			out.str(""); out.clear();

			out << ch->Dex;
			cGfx->DrawText(out.str(), x, y++, color);
			out.str(""); out.clear();

			out << ch->Con;
			cGfx->DrawText(out.str(), x, y++, color);
			out.str(""); out.clear();

			out << ch->Speed;
			cGfx->DrawText(out.str(), x, y++, color);
			out.str(""); out.clear();

		}
		else
		{
			// Draw player life bar
			int h = ch->Health;
			int mh = ch->MaxHealth;
			float size = (((float)h / (float)mh) * 28.0f);;
			std::string lifebar = "     YOU " + std::string((int)size, (unsigned char)219);
			lifebar += std::string(29 - (int)size, ' ');
			cGfx->DrawText(lifebar, 41, 20, player->GetColor() | ConColor::BkgRed);
		}
	}

	void PlayerMenu::Update()
	{

	}

	bool PlayerMenu::Shutdown()
	{
		return false;
	}

	bool PlayerMenu::IsDirty()
	{
		return _isDirty;
	}

	void PlayerMenu::DirtyMe()
	{
		_isDirty = true;
	}

} } }// End namespace Game::Graphics::Menus

