#include "NoRevival.h"
#include <sstream>

#include "ConGraphics.h"
#include "gamedefs.h"
#include "languagepack.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	NoRevival::NoRevival(int x, int y)
	{
		pos.x = x;
		pos.y = y;

		box = { x, y, 60, 15 };
		_isDirty = true;
	}

	NoRevival::~NoRevival()
	{

	}

	void NoRevival::Update()
	{
		if (_controller->ChkInput(LOSS_EXIT))
		{
			_player->GetStats()->Health = _player->GetStats()->MaxHealth / 4;
			_player->GetLevel()->Experience = _player->GetLevel()->PrevLevelExp;
			//_stateManager->PushState(MenuState::MS_REVIVE);
			_stateManager->PushState(MenuState::MS_RESURECTDEAD);
		}
		/*
		for (char k = 0; k < 128; k++)
		{
			if (_controller->ChkInput(k))
			{
				_stateManager->PushState(MenuState::MS_EXIT);
				break;
			}
		}
		*/
	}

	void NoRevival::Draw(LPGRAPHICS gfx)
	{
		using namespace Zaxis::Graphics;
		std::ostringstream out;
		// Create message for revival cost

		ConGraphics* cGfx = CONCAST(gfx);
		WORD color = ConColor::BkgRed | ConColor::LtRed;
		cGfx->DrawFillRect(&box, BoxType::Antique, color);

		color = ConColor::BkgRed | ConColor::White;
		int x = box.X + 4;
		int y = box.Y + 2;
		cGfx->DrawText(LOSS_TEXT1, x, y++, color);
		cGfx->DrawText(LOSS_TEXT2, x, y++, color);

		_isDirty = false;
	}

	void NoRevival::Clear(LPGRAPHICS gfx)
	{
		Zaxis::Graphics::ConGraphics* cGfx = CONCAST(gfx);
		UCHAR c = 32;
		cGfx->DrawRect(&box, &c, &c);
	}

	bool NoRevival::Shutdown()
	{
		return false;
	}

	bool NoRevival::IsDirty()
	{
		return _isDirty;
	}

	void NoRevival::DirtyMe()
	{
		_isDirty = true;
	}

	void NoRevival::SetPlayer(LPPLAYERENTITY player)
	{
		_player = player;
		_controller = player->GetMover()->GetController();
	}

	void NoRevival::SetStateManager(LPMENUSTATE manager)
	{
		_stateManager = manager;
	}

} } }// End namespace Game::Graphics::Menus