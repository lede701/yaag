#include "MWin.h"
#include "languagepack.h"
#include "gamedefs.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	MWin::MWin(int x, int y, LPPLAYERENTITY player)
	{
		_player = player;
		
		/*
		LPATTACKER monster = _player->GetMonster();
		_loot = NULL;
		if (monster != NULL)
		{
			_loot = monster->GetLoot();
			// Calulcate the level difference between player and monster
			float lvlDiff = static_cast<float>(monster->iGetLevel()) / static_cast<float>(_player->iGetLevel());
			// Add gold and experience to player
			exp = static_cast<int>(static_cast<float>(_loot->Exp) * lvlDiff) + 1;
			gold = _loot->Gold;
			_player->GetLevel()->Experience += exp;
			_player->GetLevel()->Gold += gold;
		}
		//*/

		_box = { x, y, 50, 10 };
		_boxColor = ConColor::BkgBlue | ConColor::LtBlue;
		_textColor = ConColor::BkgBlue | ConColor::LtYellow;

		_isDirty = true;
		_hasFinished = false;
	}

	MWin::~MWin()
	{

	}

	void MWin::Draw(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		cGfx->DrawFillRect(&_box, BoxType::Antique, _boxColor);
		
		std::ostringstream out;
		int x = _box.X + 3;
		int y = _box.Y + 2;

		out << WIN_TEXT;
		cGfx->DrawText(out.str(), x, y++, _textColor);
		out.str(""); out.clear();

		char buff[80];
		sprintf_s(buff, WIN_EXP, _exp);

		out << buff;
		cGfx->DrawText(out.str(), x, y++, _textColor);
		out.str(""); out.clear();

		sprintf_s(buff, WIN_GOLD, _gold);
		out << buff;
		cGfx->DrawText(out.str(), x, y++, _textColor);
		out.str(""); out.clear();

		y = _box.Y + _box.Height - 2;
		out << ANYKEYTEXT;
		cGfx->DrawText(out.str(), x, y, _textColor);
		out.str(""); out.clear();

		_isDirty = false;
	}

	void MWin::Clear(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		unsigned char c = 32;
		cGfx->DrawRect(&_box, &c, &c);
	}

	void MWin::Update()
	{
		bool finished = true;
		if (_controller->ChkInput(EXITKEY) || _controller->ChkInput(CONTINUEKEY))
		{
			_manager->PopState();
			return;
		}
		else
		{
			for (unsigned char c = 0; c < 255; c++)
			{
				if (_controller->ChkInput(c))
				{
					if (_hasFinished)
					{
						_manager->PopState();
						return;
					}
					finished = false;
				}
			}
		}

		if (finished)
		{
			_hasFinished = true;
		}

		return;
	}

	bool MWin::Shutdown()
	{
		return false;
	}

	bool MWin::IsDirty()
	{
		return _isDirty;
	}

	void MWin::DirtyMe()
	{
		_isDirty = true;
	}

	void MWin::SetStateManager(LPMENUSTATE manager)
	{
		_manager = manager;
	}

	void MWin::SetController(LPCONTROLLER ctrl)
	{
		_controller = ctrl;
	}

	void MWin::AddLoot(LPLOOT loot)
	{
		// Add item to loot chest
		_lootChest.push_back(loot);
	}

	void MWin::CalculateLoot()
	{
		// See if there are any items in the loot chest
		if (_lootChest.size() > 0)
		{
			// Process each loot item
			for (std::list<LPLOOT>::iterator it = _lootChest.begin(); it != _lootChest.end(); it++)
			{
				_gold += (*it)->Gold;
				_exp += (*it)->Exp;
				// Clear loot object from memory
				delete (*it);
			}
			_lootChest.clear();
			_player->GetLevel()->Gold += _gold;
			_player->GetLevel()->Experience += _exp;
		}
	}

} } }// End namespace Game::Graphics::Menus
