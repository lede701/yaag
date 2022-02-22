#ifndef H_MOVER
#define H_MOVER

#define LPMOVER Zaxis::Core::IMover*

#include "ILogger.h"
#include "IController.h"
#include "Vector2D.h"

namespace Zaxis{ namespace Core
{

	class IMover
	{
	private:

	public:
		IMover();
		virtual ~IMover();

		virtual void Move2D(LPVECTOR2D pos) = 0;
		virtual LPMOVER SetLogger(LPLOGGER log) = 0;

		virtual LPMOVER SetController(LPCONTROLLER cont) = 0;
		virtual LPCONTROLLER GetController() = 0;
	};

} }// End namespace Zaxis::Core

#endif