#include "MHomeCommands.h"
#include "gamedefs.h"
#include "languagepack.h"

namespace Game{ namespace Graphics{ namespace Menus
{

	MHomeCommands::MHomeCommands(int x, int y)
		: BaseSelector(0, 0, 0)
	{
		box = { x, y, 78, 11 };
		_isDirty = true;
		textColor = ConColor::Black | ConColor::Red;
		cmdColor = ConColor::Black | ConColor::LtGreen;
	}

	MHomeCommands::~MHomeCommands()
	{

	}

	void MHomeCommands::Draw(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		int x = box.X;
		int y = box.Y;
		// Draw player control box
		WORD color = ConColor::Black | ConColor::LtBlue;
		cGfx->DrawFillRect(&box, BoxType::Antique, color);
		std::string line = std::string(78, (unsigned char)196);
		for (int i = 0; i < 80; i = i + 2)
		{
			line[i] = (unsigned char)205;
		}
		cGfx->DrawText(line, 1, y - 1, ConColor::LtYellow | ConColor::BkgYellow);
		// Draw position for gold
		line = std::string(20, 32);
		line[0] = static_cast<unsigned char>(221);
		line[line.length() - 1] = static_cast<unsigned char>(222);
		cGfx->DrawText(line, 50, box.Y + 11, color);


		_isDirty = false;
	}

	void MHomeCommands::DrawMenu(LPGRAPHICS gfx, LPVECTOR2D pos)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		// Draw command menu
		int x = pos->x;
		int y = pos->y;

		// Enter Arena
		DrawCmd(cGfx, CMD_ENTERARENAKEY, CMD_ENTERARENATEXT, x, y++, textColor, cmdColor);

		// Random monster
		DrawCmd(cGfx, CMD_RANDOMKEY, CMD_RANDOMTEXT, x, y++, textColor, cmdColor);

		// Level Up
		DrawCmd(cGfx, CMD_LEVELUPKEY, CMD_LEVELUPTEXT, x, y++, textColor, cmdColor);

		// Game Store
		DrawCmd(cGfx, CMD_STOREKEY, CMD_STORETEXT, x, y++, textColor, cmdColor);

		// Healing
		DrawCmd(cGfx, CMD_HEALKEY, CMD_HEALTEXT, x, y++, textColor, cmdColor);

		// List players maybe even move into combat later
		DrawCmd(cGfx, CMD_PLAYERLISTKEY, CMD_PLAYERLISTTEXT, x, y++, textColor, cmdColor);

		// Exit menu item
		y++;
		DrawCmd(cGfx, EXITKEY, EXITTEXT, x, y++, textColor, cmdColor);

	}

	void MHomeCommands::Clear(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = CONCAST(gfx);
		unsigned char c = 32;
		cGfx->DrawRect(&box, &c, &c);
	}

	void MHomeCommands::Update()
	{

	}

	bool MHomeCommands::Shutdown()
	{
		return false;
	}

	bool MHomeCommands::IsDirty()
	{
		return _isDirty;
	}

	void MHomeCommands::DirtyMe()
	{
		_isDirty = true;
	}

	void MHomeCommands::SetStateManager(LPMENUSTATE manager)
	{

	}

	void MHomeCommands::SetController(LPCONTROLLER ctrl)
	{

	}

} } }// End namespace Game::Graphics::Menus