#include "GameOver.h"
#include "ConGraphics.h"
#include "gamedefs.h"

#include <sstream>

namespace Game{ namespace Graphics{ namespace Menus
{
	using namespace Zaxis::Graphics;
	using namespace Zaxis::Graphics::ConGraphicsData;
	using std::ostringstream;

	GameOver::GameOver(int x, int y)
	{
		_isDirty = true;
		pos.x = x;
		pos.y = y;

		box = { x, y, 60, 15 };
	}

	GameOver::~GameOver()
	{

	}

	void GameOver::Update()
	{
		if (_controller->ChkInput('Y'))
		{
			if (_player->GetLevel()->Gold > _player->GetLevel()->Level * 100)
			{
				_player->GetLevel()->Gold -= _player->GetLevel()->Level * 100;
				_player->GetStats()->Health = _player->GetStats()->MaxHealth * 0.75;
				_stateManager->PushState(MenuState::MS_REVIVE);
			}
			else
			{
				_stateManager->PushState(MenuState::MS_REVIVEENOUGH);
			}
		}else if (_controller->ChkInput('N'))
		{
			// Perform loss of experience
			_player->GetLevel()->Experience = _player->GetLevel()->PrevLevelExp;
			_player->GetStats()->Health = _player->GetStats()->MaxHealth / 4;
			_stateManager->PushState(MenuState::MS_EXIT);
		}
	}

	bool GameOver::Shutdown()
	{
		return false;
	}

	void GameOver::Draw(LPGRAPHICS gfx)
	{
		ostringstream out;
		// Create message for revival cost
		out << "You can try again for " << _player->GetLevel()->Level * 100;

		ConGraphics* cGfx = CONCAST(gfx);
		WORD color = ConColor::BkgRed | ConColor::LtRed;
		cGfx->DrawFillRect(&box, BoxType::Antique, color);

		color = ConColor::BkgRed | ConColor::White;
		int x = box.X + 4;
		int y = box.Y + 2;
		cGfx->DrawText("You have been killed in the Arena!", x, y++, color);
		cGfx->DrawText("The ogers have enjoyed making stew from your body and", x, y++, color);
		cGfx->DrawText("jelly from your eyes.", x, y++, color);
		y = y + 3;
		cGfx->DrawText(out.str(), x, y++, color);
		cGfx->DrawText("Would you like to try again? [Y] Yes/ [N] No", x, y++, color);

		_isDirty = false;

	}

	void GameOver::Clear(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		UCHAR c = 32;
		cGfx->DrawRect(&box, &c, &c);
	}

	bool GameOver::IsDirty()
	{
		return _isDirty;
	}

	void GameOver::DirtyMe()
	{
		_isDirty = true;
	}

	void GameOver::SetPlayer(LPPLAYERENTITY player)
	{
		_player = player;
		_controller = _player->GetMover()->GetController();
	}

	void GameOver::SetStateManager(LPMENUSTATE manager)
	{
		_stateManager = manager;
	}

} } }// End namespace Game::Graphics::Menus