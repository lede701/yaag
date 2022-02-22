#include "PlayerMover.h"
#include "KeyboardController.h"

namespace Game { namespace Controllers
{

	PlayerMover::PlayerMover(LPRECT2D limits)
	{
		controller = new Zaxis::Controllers::NullController();
		speed = new Zaxis::Math::Vector2D();
		_log = new Zaxis::Logging::NullLogger();
		_limits = limits;
	}


	PlayerMover::~PlayerMover()
	{
		if (controller != NULL)
		{
			delete controller;
			controller = NULL;
		}
		if (speed != NULL)
		{
			delete speed;
			speed = NULL;
		}
	}

	void PlayerMover::Move2D(LPVECTOR2D pos)
	{
		using Zaxis::Controllers::KeyboardController;
		// Check if controller keys are down
		KeyboardController* ctrl = static_cast<KeyboardController*>(controller);
		speed->SetXY(0, 0);
		if (ctrl != NULL)
		{
			// Handle moving left and right
			if (MoveRight())
			{
				speed->x = 1;
			}
			else if (MoveLeft())
			{
				speed->x = -1;
			}

			if (MoveUp())
			{
				speed->y = -1;
			}
			else if (MoveDown())
			{
				speed->y = 1;
			}
		}

		pos->x += speed->x;
		pos->y += speed->y;
	}

	LPMOVER PlayerMover::SetController(LPCONTROLLER cont)
	{
		if (controller != NULL)
		{
			delete controller;
			controller = NULL;
		}
		controller = cont;

		return this;
	}

	LPCONTROLLER PlayerMover::GetController()
	{
		return controller;
	}

	LPMOVER PlayerMover::SetLogger(LPLOGGER log)
	{
		if (_log != NULL)
		{
			delete _log;
			_log = NULL;
		}

		_log = log;
		return this;
	}

	LPLOGGER PlayerMover::Log()
	{
		return _log;
	}

	LPLOGGER PlayerMover::Log(std::string line)
	{
		_log->WriteLine(line);
		return _log;
	}

	bool PlayerMover::MoveUp()
	{
		return controller->ChkInput('W') || controller->ChkInput(VK_UP);
	}

	bool PlayerMover::MoveDown()
	{
		return controller->ChkInput('S') || controller->ChkInput(VK_DOWN);
	}

	bool PlayerMover::MoveLeft()
	{
		return controller->ChkInput('A') || controller->ChkInput(VK_LEFT);
	}

	bool PlayerMover::MoveRight()
	{
		return controller->ChkInput('D') || controller->ChkInput(VK_RIGHT);
	}

} }// End namespace Game::Controllers