#include "MPlayerInfo.h"
// Need the language pack for key controls.
#include "languagepack.h"
#include "gamedefs.h"
// Need these to load player information for armor and weapons
#include "WeaponData.h"
#include "ArmorData.h"
#include "FileData.h"
#include "FileIO.h"

#define PLINFO_COLOR ConColor::BkgPurple | ConColor::White
#define PLINFO_BOXCOLOR ConColor::BkgPurple | ConColor::LtPurple
#define PLINFO_HIGLIGHT ConColor::BkgBlue | ConColor::White

namespace Game{ namespace Graphics{ namespace Menus
{
	MPlayerInfo::MPlayerInfo(int x, int y) : BaseSelector(PLINFO_COLOR, PLINFO_HIGLIGHT, 26)
	{
		box = { x, y, 40, 8 };
		// Make sure the update loop draws this menu screen
		_isDirty = true;
		boxColor = PLINFO_BOXCOLOR;
		color = PLINFO_COLOR;
		statColor = ConColor::BkgPurple | ConColor::LtYellow;
		cmdColor = ConColor::BkgPurple | ConColor::LtYellow;

		// Yeah these should be stored in one place and later will be the death of me
		aFile = GetAppPath() + "\\armor.dat";
		wFile = GetAppPath() + "\\weapons.dat";
	}

	MPlayerInfo::~MPlayerInfo()
	{

	}

	void MPlayerInfo::Draw(LPGRAPHICS gfx)
	{
		// Graphic menu programming is tedious and boaring
		using Zaxis::Graphics::ConGraphicsData::BoxType;

		Zaxis::Graphics::ConGraphics* cGfx = CONCAST(gfx);
		cGfx->DrawFillRect(&box, BoxType::Antique, boxColor);
		std::ostringstream out;
		out << player.name;
		DrawTitle(cGfx, out.str(), &box, boxColor, color);
		out.str(""); out.clear();

		Zaxis::FileData<Game::Data::ArmorData> aData;
		aData.Load(aFile);

		Zaxis::FileData<Game::Data::WeaponData> wData;
		wData.Load(wFile);

		int x = box.X + 3;
		int y = box.Y + 2;

		out << PLLEVEL << ":";
		// Need to store this so we can place the data next to it
		int sx = x + out.str().length() + 1;
		cGfx->DrawText(out.str(), x, y, color);
		out.str(""); out.clear();

		out << player.level.Level;
		cGfx->DrawText(out.str(), sx, y++, statColor);
		out.str(""); out.clear();

		// Show player health
		out << PG_HEALTH << ":";
		sx = x + out.str().length() + 1;
		cGfx->DrawText(out.str(), x, y, color);
		out.str(""); out.clear();

		out << player.character.Health << "(" << player.character.MaxHealth << ")";
		cGfx->DrawText(out.str(), sx, y++, statColor);
		out.str(""); out.clear();

		// Now to load up the weapon information
		Game::Data::WeaponData w = wData.GetAt(player.weaponId - 1);
		out << PG_WEAPON << ":";
		sx = x + out.str().length() + 1;
		cGfx->DrawText(out.str(), x, y, color);
		out.str(""); out.clear();

		out << w.name;
		if (w.plus > 0)
		{
			out << " +" << w.plus;
		}
		else if (w.plus < 0)
		{
			out << " " << w.plus;
		}// Endif check if there is a plus to weapon

		cGfx->DrawText(out.str(), sx, y++, statColor);
		out.str(""); out.clear();

		Game::Data::ArmorData a = aData.GetAt(player.armorId - 1);
		out << PG_ARMOR << ":";
		sx = x + out.str().length() + 1;
		cGfx->DrawText(out.str(), x, y, color);
		out.str(""); out.clear();

		out << a.name;
		if (a.plus > 0)
		{
			out << " +" << a.plus;
		}
		else if (a.plus < 0)
		{
			out << " " << a.plus;
		}
		cGfx->DrawText(out.str(), sx, y++, statColor);
		out.str(""); out.clear();

		// Need to set the y position based on box height and position
		y = box.Y + box.Height - 1;

		// Adding in menu commands to this menu
		out << "[ ] " << EXITTEXT;
		cGfx->DrawText(out.str(), x, y, color);
		out.str(""); out.clear();

		// Add in command key now
		out << EXITKEY;
		cGfx->DrawText(out.str(), x + 1, y, cmdColor);
		out.str(""); out.clear();

		// Screen is complete so don't need to do a redraw
		_isDirty = false;
	}

	void MPlayerInfo::Clear(LPGRAPHICS gfx)
	{
		// Cast graphic object to the ConGraphics
		Zaxis::Graphics::ConGraphics* cGfx = CONCAST(gfx);
		UCHAR c = 32; // White Space could just be ' '
		// Draw clearing rectangle
		cGfx->DrawRect(&box, &c, &c);
	}

	void MPlayerInfo::Update()
	{
		if (_controller->ChkInput(VK_ESCAPE) || _controller->ChkInput(EXITKEY))
		{
			// Nock layer off stack
			_stateManager->PopState();
			// We are not valid anymore so return control to calling system
			return;
		}
	}
	
	bool MPlayerInfo::IsDirty()
	{
		return _isDirty;
	}

	void MPlayerInfo::DirtyMe()
	{
		_isDirty = true;
	}

	bool MPlayerInfo::Shutdown()
	{
		// No direct path to shutting down the game engine
		return false;
	}

	void MPlayerInfo::SetStateManager(LPMENUSTATE manager)
	{
		_stateManager = manager;
	}

	void MPlayerInfo::SetController(LPCONTROLLER ctrl)
	{
		_controller = ctrl;
	}

	void MPlayerInfo::SetPlayer(Game::Data::PlayerData pl)
	{
		player = pl;
	}

} } }// End namespace Game::Graphics::Menus