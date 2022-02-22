#ifndef H_PLAYERCOMMAND
#define H_PLAYERCOMMAND

#include <sstream>

#include "ICommand.h"
#include "IController.h"
#include "ConGraphics.h"
#include "zmath.h"

#define LPPLCOMMAND Game::Commands::PlayerCommand*

namespace Game{ namespace Commands
{
	using Zaxis::Graphics::ConGraphics;
	using Zaxis::Graphics::ConColor;

	class PlayerCommand :
		Zaxis::Commands::ICommand
	{
	private:
		unsigned char key;
		std::string sKey;
		LPVECTOR2D pos;
		LPCONTROLLER _controller;

	public:
		PlayerCommand(unsigned char inKey, LPVECTOR2D inPos);
		PlayerCommand(unsigned char inKey, std::string inSKey, LPVECTOR2D inPos);
		~PlayerCommand();

		virtual void Execute();

		LPPLCOMMAND SetController(LPCONTROLLER ctrl);
		LPCONTROLLER Controller();

		virtual void Update(ConGraphics* graphics);

	};

} }// End namespace Game::Commands


#endif