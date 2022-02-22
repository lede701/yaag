#include "MLevelUp.h"
#include "gamedefs.h"
#include "languagepack.h"

#include <iomanip>

namespace Game{ namespace Graphics{ namespace Menus
{
	MLevelUp::MLevelUp(LPPLAYERENTITY player, int x, int y)
	{
		pos.x = x;
		pos.y = y;

		box = { x, y, 30, 15 };

		_player = player;
		_controller = _player->GetMover()->GetController();
		plData = _player->GetData();
		pauseAmount = 300;
		for (int i = 0; i < MAX_STATS; i++)
		{
			addStat[i] = 0;
		}
		// Make sure the engine knows to draw me for the first time
		_isDirty = true;

		availPoints = max(0, (plData->level.Level * 5) - plData->level.AssignedPoints);
	}

	MLevelUp::~MLevelUp()
	{

	}

	void MLevelUp::Draw(LPGRAPHICS gfx)
	{
		using Zaxis::Graphics::ConGraphicsData::ConColor;
		Zaxis::Graphics::ConGraphics* cGfx = CONCAST(gfx);

		WORD color = ConColor::BkgPurple | ConColor::LtPurple;
		cGfx->DrawFillRect(&box, Zaxis::Graphics::ConGraphicsData::BoxType::Antique, color);

		std::string line(LUM_TITLE);
		std::string title(line.length() + 2, ' ');
		title[0] = 221;
		title[title.length() - 1] = 222;
		int x = pos.x + (box.Width / 2) - ((title.length() + 2) / 2);
		int y = pos.y;
		cGfx->DrawText(title, x, y, color);
		color = ConColor::BkgPurple | ConColor::White;
		cGfx->DrawText(line, x + 1, y++, color);

		x = pos.x + 2;

		// Show number of points to spread
		std::ostringstream out;
		out << LUM_POINTS << ": " << availPoints;
		DrawLine(cGfx, out.str(), x, y++, false);
		out.str(""); out.clear();

		// Show Strength
		out << PS_STR << ": " << (plData->character.Str + addStat[STATLINES::SL_STR]);
		DrawLine(cGfx, out.str(), x, y++, statLine == STATLINES::SL_STR);
		out.str(""); out.clear();

		// Show Dex
		out << PS_DEX << ": " << (plData->character.Dex + addStat[STATLINES::SL_DEX]);
		DrawLine(cGfx, out.str(), x, y++, statLine == STATLINES::SL_DEX);
		out.str(""); out.clear();

		// Show Con
		out << PS_CON << ": " << (plData->character.Con + addStat[STATLINES::SL_CON]);
		DrawLine(cGfx, out.str(), x, y++, statLine == STATLINES::SL_CON);
		out.str(""); out.clear();

		// Show Int
		out << PS_INT << ": " << (plData->character.Int + addStat[STATLINES::SL_INT]);
		DrawLine(cGfx, out.str(), x, y++, statLine == STATLINES::SL_INT);
		out.str(""); out.clear();

		// Show Speed
		out << PS_SPEED << ": " << (plData->character.Speed + addStat[STATLINES::SL_SPEED]);
		DrawLine(cGfx, out.str(), x, y++, statLine == STATLINES::SL_SPEED);
		out.str(""); out.clear();

		// Show Heal
		out << PS_HEAL << ": " << (plData->character.HealingSpeed + addStat[STATLINES::SL_HEAL]);
		DrawLine(cGfx, out.str(), x, y++, statLine == STATLINES::SL_HEAL);
		out.str(""); out.clear();

		// Show commands
		out << "[" << PS_SAVEKEY << "] " << PS_SAVETEXT << "\t";
		out << "[" << EXITKEY << "] " << EXITTEXT;
		cGfx->DrawText(out.str(), x, (pos.y + box.Height - 2), color);
		out.str(""); out.clear();

		_isDirty = false;
	}

	void MLevelUp::DrawLine(Zaxis::Graphics::ConGraphics* cGfx, std::string line, int x, int y, bool IsSelected)
	{
		WORD color = Zaxis::Graphics::ConGraphicsData::ConColor::BkgPurple | Zaxis::Graphics::ConGraphicsData::ConColor::White;
		WORD highlight = Zaxis::Graphics::ConGraphicsData::ConColor::BkgBlue | Zaxis::Graphics::ConGraphicsData::ConColor::LtYellow;
		if (IsSelected)
		{
			int spaceSize = 20 - line.length();
			std::string whiteSpace(spaceSize, ' ');
			line += whiteSpace;
			cGfx->DrawText(line, x, y, highlight);
		}
		else
		{
			cGfx->DrawText(line, x, y, color);
		}

	}

	void MLevelUp::Clear(LPGRAPHICS gfx)
	{
		Zaxis::Graphics::ConGraphics* cGfx = CONCAST(gfx);
		UCHAR c = 32;
		cGfx->DrawRect(&box, &c, &c);
	}

	void MLevelUp::Update()
	{
		if (_controller->ChkInput(VK_ESCAPE) || _controller->ChkInput(EXITKEY))
		{
			// Close down menu
			_stateManager->Pause(false);
			_stateManager->PopState();
			return;
		}

		// Calculate the key entry so it isn't to fast.
		clock_t pauseCount = clock() - pauseTime;
		if (pauseCount > pauseAmount)
		{
			// Move highlight up one
			if (_controller->ChkInput(VK_UP))
			{
				statLine--;
				if (statLine < 0)
				{
					statLine = 5;
				}
				pauseTime = clock();
			}
			// Move highlight down one
			if (_controller->ChkInput(VK_DOWN))
			{
				statLine = (statLine + 1) % 6;
				pauseTime = clock();
			}

			if (_controller->ChkInput(VK_LEFT))
			{
				if (addStat[statLine] > 0)
				{
					availPoints++;
					addStat[statLine]--;
					pauseTime = clock();
				}
			}
			if (_controller->ChkInput(VK_RIGHT))
			{
				if (availPoints > 0)
				{
					availPoints--;
					addStat[statLine]++;
					pauseTime = clock();
				}
			}

			if (_controller->ChkInput(PS_SAVEKEY))
			{
				plData->character.Str += addStat[STATLINES::SL_STR];
				plData->character.Dex += addStat[STATLINES::SL_DEX];
				plData->character.Con += addStat[STATLINES::SL_CON];
				plData->character.Int += addStat[STATLINES::SL_INT];
				plData->character.Speed += addStat[STATLINES::SL_SPEED];
				plData->character.HealingSpeed += addStat[STATLINES::SL_HEAL];
				plData->character.AttackSpeed = max(1, 20 - plData->character.Dex);
				plData->character.Update();

				int pntUsed = 0;
				for (int i = 0; i < MAX_STATS; i++)
				{
					pntUsed += addStat[i];
				}
				plData->level.AssignedPoints += pntUsed;

				// Close window
				_stateManager->Pause(false);
				_stateManager->SavePlayer(false);
				_stateManager->PopState();
				return;
			}

			if (pauseTime == clock())
			{
				DirtyMe();
			}
		}
	}

	bool MLevelUp::Shutdown()
	{
		return false;
	}

	bool MLevelUp::IsDirty()
	{
		return _isDirty;
	}

	void MLevelUp::DirtyMe()
	{
		_isDirty = true;
	}

	void MLevelUp::SetStateManager(LPMENUSTATE manager)
	{
		_stateManager = manager;
		_stateManager->Pause(true);
	}

} } }// End namespace Game::Graphics::Menus