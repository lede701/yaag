#include "MSelect.h"
#include "gamedefs.h"
#include "FileIO.h"
#include "languagepack.h"

#define SELECT_TEXTCOLOR ConColor::BkgBlue | ConColor::White
#define SELECT_HIGHLIGHT ConColor::BkgPurple | ConColor::White
#define SELECT_LINEWIDTH 30

/**
Select monster screen
**/

namespace Game{ namespace Graphics{ namespace Menus
{
	
	MSelect::MSelect(int x, int y)
		: BaseSelector(SELECT_TEXTCOLOR, SELECT_HIGHLIGHT, SELECT_LINEWIDTH)
	{
		// Define size of menu
		box = { x, y, 38, 18 };
		// Define menu color scheme
		boxColor = ConColor::BkgBlue | ConColor::LtBlue;
		color = ConColor::BkgBlue | ConColor::LtYellow;
		cmdColor = ConColor::Black | ConColor::Red;
		keyColor = ConColor::Black | ConColor::LtGreen;

		// Load monsters
		/*
		mFile = GetAppPath() + "\\monster.dat";
		Zaxis::FileData<MonsterData> data;
		data.Load(mFile);
		data.Front();
		unsigned int pos = data.CurrentPos();
		// Create list from loaded monsters
		do
		{
			list.push_back(data.GetAt(pos));
			pos = data.NextPos(pos);
		} while (pos != data.Back().id);

		// Sort monsters
		list.sort(Game::Data::CompareMonsterLevel);
		//*/
		// Set menu to dirty
		_isDirty = true;
		// Setup list drawing
		MaxSize = 16;
		StartPos = 0;
		SelectPos = 0;
	}

	MSelect::~MSelect()
	{

	}

	void MSelect::Draw(LPGRAPHICS gfx)
	{

		ConGraphics* cGfx = CONCAST(gfx);
		cGfx->DrawFillRect(&box, BoxType::Antique, boxColor);
		std::ostringstream out;
		out << SMM_TITLE;
		DrawTitle(cGfx, out.str(), &box, boxColor, color);
		out.str(""); out.clear();

		int x = box.X + 3;
		int y = box.Y + 2;
		int cnt = 0;
		int shown = 0;
		for (std::list<MonsterData>::iterator it = list.begin(); it != list.end(); it++)
		{
			if (cnt >= StartPos && shown < MaxSize)
			{
				out << (cnt + 1) << ". " << (*it).name;
				DrawLine(cGfx, out.str(), x, y++, (*it).id == SelectedId);
				out.str(""); out.clear();
				shown++;
			}
			cnt++;
		}

		x = box.X + 2;
		y = box.Y + box.Height - 1;

		_isDirty = false;
	}

	void MSelect::DrawMenu(LPGRAPHICS gfx, LPVECTOR2D pos)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		int x = pos->x;
		int y = pos->y;

		// Draw Select Monster commands
		// Magic number 5 is the width of the largest key, this should be defined by the language pack
		int keyWidth = 5;
		DrawCmd(cGfx, CMD_UPKEY, CMD_UPSELECT, x, y++, keyWidth, cmdColor, keyColor);
		DrawCmd(cGfx, CMD_DOWNKEY, CMD_DOWNSELECT, x, y++, keyWidth, cmdColor, keyColor);
		DrawCmd(cGfx, CMD_ENTERKEY, CMD_SELECTMONSTER, x, y++, keyWidth, cmdColor, keyColor);
		// Move down an extra line
		y++;

		// Draw level up command
		DrawCmd(cGfx, CMD_LEVELUPKEY, CMD_LEVELUPTEXT, x, y++, cmdColor, keyColor);

		// Draw store command
		DrawCmd(cGfx, CMD_STOREKEY, CMD_STORETEXT, x, y++, cmdColor, keyColor);

		// Draw exit menu key
		y++;
		DrawCmd(cGfx, EXITKEY, EXITTEXT, x, y++, cmdColor, keyColor);

	}

	void MSelect::Clear(LPGRAPHICS gfx)
	{

	}

	void MSelect::Update()
	{
		if (_controller->ChkInput(VK_ESCAPE) || _controller->ChkInput(EXITKEY))
		{
			_manager->PopState();
			return;
		}
		else
		{
			if (_controller->ChkInput(VK_UP))
			{
				if ((*mPos).id != (*list.begin()).id)
				{
					mPos--;
					SelectPos--;
					SelectedId = (*mPos).id;
					DirtyMe();
				}
			}
			else if (_controller->ChkInput(VK_DOWN))
			{
				std::list<MonsterData>::iterator end = list.end();
				end--;
				if (mPos != end)
				{
					mPos++;
					SelectPos++;
					SelectedId = (*mPos).id;
					DirtyMe();
				}
			}
			else if (_controller->ChkInput(VK_RETURN))
			{
				_manager->PushState(Game::Graphics::Menus::MenuState::MS_FIGHTMONSTER);
			}
			else if (_controller->ChkInput(CMD_LEVELUPKEY))
			{
				_manager->PushState(Game::Graphics::Menus::MenuState::MS_LEVELUP);
			}
			else if (_controller->ChkInput(CMD_STOREKEY))
			{
				_manager->PushState(Game::Graphics::Menus::MenuState::MS_STORE);
			}

			StartPos = 0;
			if (SelectPos >= MaxSize)
			{
				StartPos = SelectPos - MaxSize + 1;
			}
		}
	}

	bool MSelect::Shutdown()
	{
		return false;
	}

	bool MSelect::IsDirty()
	{
		return _isDirty;
	}

	void MSelect::DirtyMe()
	{
		_isDirty = true;
	}

	void MSelect::SetStateManager(LPMENUSTATE manager)
	{
		_manager = manager;
	}

	void MSelect::SetController(LPCONTROLLER ctrl)
	{
		_controller = ctrl;
	}

	void MSelect::SetDataController(LPDATA data)
	{
		_data = data;

		// Get list of all monsters from the data controller
		for (int i = 0; i < 256; i++)
		{
			MonsterData m = _data->GetMonster(i);
			if (m.id == 0) 
			{
				break;
			}

			list.push_back(m);
		}

		list.sort(Game::Data::CompareMonsterLevel);

		// Set selected monster
		SelectedId = (*list.begin()).id;
		mPos = list.begin();

		DirtyMe();
	}

	unsigned int MSelect::GetMonsterId()
	{
		return SelectedId;
	}

} } }// End namespace Game::Graphics::Menus