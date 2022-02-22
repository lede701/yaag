#include "PlayerCommand.h"

namespace Game{ namespace Commands
{

	PlayerCommand::PlayerCommand(unsigned char inKey, LPVECTOR2D inPos)
	{
		key = inKey;
		sKey += key;
		pos = inPos;
	}

	PlayerCommand::PlayerCommand(unsigned char inKey, std::string inSKey, LPVECTOR2D inPos)
	{
		key = inKey;
		sKey += inSKey;
		pos = inPos;
	}

	PlayerCommand::~PlayerCommand()
	{
	}

	void PlayerCommand::Execute()
	{

	}

	void PlayerCommand::Update(ConGraphics* graphics)
	{
		WORD clr = ConColor::Black;
		if (Controller()->ChkInput(key))
		{
			clr = clr | ConColor::White;
		}
		else
		{
			clr = clr | ConColor::LtGreen;
		}
		if (graphics != NULL)
		{
			graphics->DrawText(sKey, pos->x, pos->y, clr);
		}
	}

	LPCONTROLLER PlayerCommand::Controller()
	{
		return _controller;
	}

	LPPLCOMMAND PlayerCommand::SetController(LPCONTROLLER ctrl)
	{
		_controller = ctrl;
		return this;
	}

} }// End namespace Game::Commands

