#include "AttackCommand.h"

namespace Game{ namespace Commands
{

	AttackCommand::AttackCommand(unsigned char inKey, LPVECTOR2D inPos) : PlayerCommand(inKey, inPos)
	{
		_player = NULL;
		key = inKey;
		pos = inPos;
		sKey = inKey;
	}

	AttackCommand::AttackCommand(unsigned char inKey, std::string inSKey, LPVECTOR2D inPos) : PlayerCommand(inKey, inSKey, inPos)
	{
		_player = NULL;
		key = inKey;
		pos = inPos;
		sKey = inSKey;
	}

	AttackCommand::~AttackCommand()
	{
	}

	void AttackCommand::Update(ConGraphics* graphics)
	{
		// Set default draw color to black so text is not seen
		WORD keyColor = ConColor::Black;
		// Check if player is defined
		if (_player != NULL)
		{
			// Check if player attack is ready
			if (_player->IsAttackReady())
			{
				// Process update through normal command object
				PlayerCommand::Update(graphics);
			}
			else
			{
				// Attack isn't ready so check if graphics is not null
				if (graphics != NULL)
				{
					// Draw black text to screen
					graphics->DrawText(sKey, pos->x, pos->y, keyColor);
				}
			}
		}
	}

	void AttackCommand::SetPlayer(LPATTACKER player)
	{
		// Assign _player to provided object
		_player = player;
	}

} }// End namespace Game::Commands
