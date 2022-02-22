#ifndef H_MTEST
#define H_MTEST

#include <iostream>
#include <sstream>

#include "IMover.h"
#include "ILogger.h"
#include "zmath.h"

namespace Zaxis{ namespace Core
{

	class MTest :
		public IMover
	{
	private:
		Zaxis::Math::Vector2D speed;
		LPLOGGER _log;
		LPRECT2D _limits;

	public:
		MTest();
		MTest(LPRECT2D limits, int x, int y);
		MTest(LPLOGGER inLog);

		~MTest();

		void Move2D(LPVECTOR2D pos);
		virtual LPMOVER SetLogger(LPLOGGER inLog);

		void Log(std::string line);
	};

} }// End namespace Zaixs::Core

#endif