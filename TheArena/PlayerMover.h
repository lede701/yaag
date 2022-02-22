#ifndef H_PLAYERMOVER
#define H_PLAYERMOVER

#include "NullController.h"
#include "NullLogger.h"
#include "IMover.h"
#include "IDirection.h"
#include "zmath.h"

namespace Game { namespace Controllers
{
	class PlayerMover :
		public Zaxis::Core::IMover, public Game::Entity::IDirection
	{
	private:
		LPCONTROLLER controller;
		LPVECTOR2D speed;

		LPLOGGER _log;
		LPRECT2D _limits;

	public:
		PlayerMover(LPRECT2D limits);
		virtual ~PlayerMover();

		virtual void Move2D(LPVECTOR2D pos);
		virtual LPMOVER SetLogger(LPLOGGER log);

		virtual LPMOVER SetController(LPCONTROLLER cont);
		virtual LPCONTROLLER GetController();

		virtual LPLOGGER Log();
		virtual LPLOGGER Log(std::string line);

		virtual bool MoveUp();
		virtual bool MoveDown();
		virtual bool MoveLeft();
		virtual bool MoveRight();
	};

} }

#endif