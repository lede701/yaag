#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wincon.h>
#include <locale>
#include <codecvt>
#include <cstdlib>

#include "zmath.h"
//Menu System
#include "MenuSystem.h"
#include "IMenuState.h"

// Core Engine Utilities
#include "stdxgame.h"

// The Egnine!!!!
#include "GameEngine.h"

int TheGame(void);

int main() {

	return TheGame();
}

int TheGame() {
	using Zaxis::Graphics::ConGraphics;
	using Zaxis::Math::Vector2D;
	using Zaxis::Math::Rect;
	using Zaxis::Controllers::KeyboardController;

	using Game::Graphics::MenuState;
	using Game::Graphics::MenuSystem;
	using Game::EntityManager;

	ConGraphics* gfx = new ConGraphics();
	MenuSystem* menu = new MenuSystem(gfx);
	KeyboardController* ctrl = new KeyboardController();

	LPGAME game = new Zaxis::Engines::GameEngine();
	game->SetGraphics(gfx)
		->AddUpdater(ctrl)
		->AddStater(ctrl);

	EntityManager* em = new EntityManager();
	em->SetEntityManager(game);
	em->SetStateManager(menu);

	game->AddUpdater(em)
		->AddUpdater(menu);
	menu->SetManager(em)
		->SetController(ctrl)
		->PushState(MenuState::MS_LOGIN);

	return game->RunEngine();
}