#include "MPlayerList.h"

#include "gamedefs.h"
#include "languagepack.h"
#include "FileData.h"
#include "WeaponData.h"
#include "ArmorData.h"
#include "FileIO.h"

#include <iomanip>
#define LIST_LINEWIDTH 54
#define LIST_TEXTCOLOR ConColor::BkgBlue | ConColor::White
#define LIST_HIGHLIGHT ConColor::BkgPurple | ConColor::White


namespace Game{ namespace Graphics{ namespace Menus
{
	using Game::Data::PlayerData;

	MPlayerList::MPlayerList(int x, int y) : BaseSelector(LIST_TEXTCOLOR, LIST_HIGHLIGHT, LIST_LINEWIDTH)
	{
		_isDirty = true;
		box = { x, y, 60, 20 };
		color = LIST_TEXTCOLOR;
		boxColor = ConColor::BkgBlue | ConColor::LtBlue;
		cmdColor = ConColor::BkgBlue | ConColor::LtYellow;

		plFile = GetAppPath() + "\\players.dat";
		start = 0;
		count = 16;
		selectedLine = 0;

		Zaxis::FileData<PlayerData> plData;
		plData.Load(plFile);
		plData.Front();
		unsigned int pos = plData.CurrentPos();

		// Fill list of all players in database
		do
		{
			plList.push_back(plData.GetAt(pos));
			pos = plData.NextPos(pos);
		} while (pos != plData.Back().id);

		// Sort player list
		plList.sort(Game::Data::PlayerSortExp);
		plList.reverse();
	}

	MPlayerList::~MPlayerList()
	{

	}

	void MPlayerList::Draw(LPGRAPHICS gfx)
	{
		using Zaxis::Graphics::ConGraphicsData::BoxType;

		Zaxis::Graphics::ConGraphics* cGfx = CONCAST(gfx);
		// Draw base box for screen
		cGfx->DrawFillRect(&box, BoxType::Antique, boxColor);
		// Draw title
		DrawTitle(cGfx, PLLISTHEADING, &box, boxColor, color);

		std::ostringstream out;
		int x = box.X + 2;
		int y = box.Y + 2;
		out << std::setw(36) << std::left << PLNAME << std::setw(8) << PLEXP << std::setw(6) << PLWINS << std::setw(6) << PLLOSSES;
		cGfx->DrawText(out.str(), x, y++, color);
		out.str(""); out.clear();

		// Draw list of players
		int line = 0;
		for (std::list<PlayerData>::iterator it = plList.begin(); it != plList.end(); it++)
		{
			PlayerData d = (*it);
			out << (line + 1) << ". " << d.name;
			std::string name = out.str();
			out.str(""); out.clear();

			out << std::setw(36) << std::left << name;
			out << std::setw(8) << d.level.Experience;
			out << std::setw(6) << d.Wins;
			out << std::setw(6) << d.Losses;
			DrawLine(cGfx, out.str(), x, y++, line++ == selectedLine);
			out.str(""); out.clear();
		}

		// Show menu commands
		x = box.X + 2;
		y = box.Y + box.Height - 1;

		out << "[";
		cGfx->DrawText(out.str(), x, y, color);
		out.str(""); out.clear();
		x += 1;

		out << PLIST_SELECTKEY;
		cGfx->DrawText(out.str(), x, y, cmdColor);
		x += out.str().length();
		out.str(""); out.clear();

		out << "]";
		cGfx->DrawText(out.str(), x, y, color);
		out.str(""); out.clear();
		x += 2;

		out << PLIST_SELECTTEXT;
		cGfx->DrawText(out.str(), x, y, color);
		x += out.str().length();
		out.str(""); out.clear();

		x += 1;
		out << "[ ] " << EXITTEXT;
		cGfx->DrawText(out.str(), x, y, color);
		out.str(""); out.clear();

		out << EXITKEY;
		cGfx->DrawText(out.str(), x + 1, y, cmdColor);
		out.str(""); out.clear();

		_isDirty = false;
	}

	void MPlayerList::Clear(LPGRAPHICS gfx)
	{
		Zaxis::Graphics::ConGraphics* cGfx = CONCAST(gfx);
		UCHAR c = 32;
		cGfx->DrawRect(&box, &c, &c);
	}

	void MPlayerList::Update()
	{
		if (_controller->ChkInput(VK_ESCAPE) || _controller->ChkInput(EXITKEY))
		{
			_stateManager->PopState();
			return;
		}
		else
		{
			if (_controller->ChkInput(VK_UP))
			{
				selectedLine--;
				if (selectedLine < 0)
				{
					// Adjust the selected line to the first item on the list
					selectedLine = 0;
				}
				else
				{
					// Tell the graphics engine I need to be redrawn
					DirtyMe();
				}// End if selectedLine range check
			}// Endif up key is pressed check

			if (_controller->ChkInput(VK_DOWN))
			{
				selectedLine++;
				if (selectedLine >= plList.size())
				{
					// Adjust the selected line to the last item on the list
					selectedLine = plList.size() - 1;
				}
				else
				{
					// Tell the graphic engine we need to be redrawn
					DirtyMe();
				}// End if selectedLine range check
			}// Endif down key is pressed check

			// Check if player wants to view selected player information
			if (_controller->ChkInput(VK_RETURN))
			{
				_stateManager->PushState(Game::Graphics::Menus::MenuState::MS_PLAYERDETAILS);
			}// Endif return is pressed check
		}
	}

	bool MPlayerList::Shutdown()
	{
		return false;
	}

	bool MPlayerList::IsDirty()
	{
		return _isDirty;
	}

	void MPlayerList::DirtyMe()
	{
		_isDirty = true;
	}

	void MPlayerList::SetStateManager(LPMENUSTATE manager)
	{
		_stateManager = manager;
	}

	void MPlayerList::SetController(LPCONTROLLER ctrl)
	{
		_controller = ctrl;
	}

	Game::Data::PlayerData MPlayerList::GetSelectedPlayer()
	{
		Game::Data::PlayerData data;
		// Don't want to do this so I will make it work then later research a faster way
		int line = 0;
		for (std::list<PlayerData>::iterator it = plList.begin(); it != plList.end(); it++)
		{
			if (line == selectedLine)
			{
				data = (*it);
				break;
			}
			line++;
		}

		return data;
	}


} } }// End namespace Game::Graphics::Menus