#ifndef H_OBJECT
#define H_OBJECT

#define LPOBJECT Zaxis::Core::Object*

#include <stdlib.h>
#include <string>

#include "ILogger.h"
#include "ISound.h"
#include "Vector2D.h"

namespace Zaxis{ namespace Core
{
	class Object
	{
	private:
		// Game object Id value
		int Id;
		bool _isAsleep;
		LPVECTOR2D _pos2d;
		LPLOGGER _log;

	public:

		Object();
		virtual ~Object();

		virtual void Init();

		virtual LPOBJECT Update() = 0;

		int GetId();
		LPOBJECT SetId(int id);

		LPOBJECT SetPosition2D(LPVECTOR2D pos);
		LPVECTOR2D GetPosition2D();

		LPOBJECT SetX(int x);
		LPOBJECT SetY(int y);
		LPOBJECT SetXY(int x, int y);

		virtual bool IsAsleep();
		LPOBJECT SetSleeping(bool sleeping);
		virtual LPOBJECT GoingToSleep();

		LPOBJECT SetLogger(LPLOGGER log);
		LPLOGGER Log();
		LPLOGGER Log(std::string line);

		virtual LPOBJECT SetSound(LPENGSOUND sound) = 0;
		virtual LPENGSOUND Sound() = 0;
	};

} }// End namespace Zaxis::Core

#endif