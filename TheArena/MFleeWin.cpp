#include "MFleeWin.h"
#include "languagepack.h"
#include "ConGraphics.h"
#include "gamedefs.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	using Zaxis::Graphics::ConGraphics;
	using Zaxis::Graphics::ConColor;
	using Zaxis::Graphics::BoxType;

	MFleeWin::MFleeWin(int x, int y, LPPLAYERENTITY player)
	{
		_player = player;
		_exp = 0;
		_gold = 0;

		_box = { x, y, 70, 10 };
		_boxColor = ConColor::BkgBlue | ConColor::LtBlue;
		_textColor = ConColor::BkgBlue | ConColor::LtYellow;

		_isDirty = true;
		_hasFinished = false;
	}

	MFleeWin::~MFleeWin()
	{

	}

	void MFleeWin::Draw(LPGRAPHICS gfx)
	{
		CalculateLoot();
		ConGraphics* cGfx = CONCAST(gfx);
		cGfx->DrawFillRect(&_box, BoxType::Antique, _boxColor);

		std::ostringstream out;
		int x = _box.X + 1;
		int y = _box.Y + 2;

		out << WIN_FLEE_TEXT;
		cGfx->DrawText(out.str(), x, y++, _textColor);
		out.str(""); out.clear();


		out << WIN_FLEE_EXP;
		cGfx->DrawText(out.str(), x, y++, _textColor);
		out.str(""); out.clear();

		char buff[80];
		sprintf_s(buff, WIN_FLEE_GOLD, _gold);
		out << buff;
		cGfx->DrawText(out.str(), x, y++, _textColor);
		out.str(""); out.clear();

		y = _box.Y + _box.Height - 2;
		out << ANYKEYTEXT;
		cGfx->DrawText(out.str(), x, y, _textColor);
		out.str(""); out.clear();

		_isDirty = false;
	}

	void MFleeWin::Clear(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		unsigned char c = 32;
		cGfx->DrawRect(&_box, &c, &c);
	}

	void MFleeWin::Update()
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

	bool MFleeWin::Shutdown()
	{
		return false;
	}

	bool MFleeWin::IsDirty()
	{
		return _isDirty;
	}

	void MFleeWin::DirtyMe()
	{
		_isDirty = true;
	}

	void MFleeWin::SetStateManager(LPMENUSTATE manager)
	{
		_manager = manager;
	}

	void MFleeWin::SetController(LPCONTROLLER ctrl)
	{
		_controller = ctrl;
	}

	void MFleeWin::AddLoot(LPLOOT loot)
	{
		lootChest.push_back(loot);
	}

	void MFleeWin::CalculateLoot()
	{
		// See if there are any items in the loot chest
		if (lootChest.size() > 0)
		{
			// Process each loot item
			for (std::list<LPLOOT>::iterator it = lootChest.begin(); it != lootChest.end(); it++)
			{
				_gold += (*it)->Gold * 0.5f;
				delete (*it);
			}
			lootChest.clear();
			_player->GetLevel()->Gold += _gold;
		}
	}

} } }// End namespace Game::Graphics::Menu