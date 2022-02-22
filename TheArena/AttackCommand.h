#ifndef H_ATTACKCOMMAND
#define H_ATTACKCOMMAND

#include "PlayerCommand.h"
#include "IAttacker.h"

namespace Game{ namespace Commands
{

	class AttackCommand : 
		public PlayerCommand
	{
	private:
		LPATTACKER _player;
		unsigned char key;
		std::string sKey;
		LPVECTOR2D pos;

	public:
		AttackCommand(unsigned char inKey, LPVECTOR2D inPos);
		AttackCommand(unsigned char inKey, std::string inSKey, LPVECTOR2D inPos);
		virtual ~AttackCommand();

		virtual void Update(ConGraphics* graphics);

		virtual void SetPlayer(LPATTACKER player);
	};

} }// End namespace Game::Commands

#endif