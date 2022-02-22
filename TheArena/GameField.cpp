#include "GameField.h"
#include "ConGraphics.h"
#include "gamedefs.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	using namespace Zaxis::Graphics;
	using namespace Zaxis::Graphics::ConGraphicsData;
	using namespace Zaxis::Math;

	GameField::GameField(Rect GameField, LPVECTOR2D exit)
	{
		_gameField = GameField;
		_exit = new Zaxis::Math::Vector2D(68, 1);
		_isDirty = true;
		_gfx = NULL;
		SetExit(exit);
	}


	GameField::~GameField()
	{
	}

	void GameField::Draw(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);

		Rect GameBorder = { _gameField.X - 1, _gameField.Y - 1, _gameField.Width + 2, _gameField.Height + 2 };
		unsigned char ch = 219;
		unsigned char bch = 46;
		cGfx->DrawRect(&GameBorder, &ch, &bch);

		int sy = (GameBorder.Height / 2) + GameBorder.Y - 1;
		int ey = sy + 3;
		// Put exit on the game field
		cGfx->DrawText(bch, _exit->x, _exit->y);
		_gfx = gfx;
		_isDirty = false;
	}

	void GameField::Clear(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		if (cGfx != NULL)
		{
			Rect GameBorder = { _gameField.X - 1, _gameField.Y - 1, _gameField.Width + 2, _gameField.Height + 2 };
			UCHAR c = 32;
			cGfx->DrawRect(&GameBorder, &c, &c);
		}
	}

	void GameField::Update()
	{
		if (_isDirty && _gfx != NULL)
		{
			Draw(_gfx);
		}
	}

	bool GameField::Shutdown()
	{
		return false;
	}

	LPVECTOR2D GameField::GetExit()
	{
		return _exit;
	}

	void GameField::SetExit(LPVECTOR2D exit)
	{
		_exit = exit;
		_isDirty = true;
	}

	bool GameField::IsDirty()
	{
		return _isDirty;
	}

	void GameField::DirtyMe()
	{
		_isDirty = true;
	}


} } }// End namespace Game::Graphics::Menus


