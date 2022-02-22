#include "MTest.h"


namespace Zaxis{ namespace Core
{

	MTest::MTest()
	{
		speed.x = speed.y = 1;
		_log = NULL;
	}

	MTest::MTest(LPRECT2D limits, int x, int y)
	{
		_limits = limits;
		speed.x = x;
		speed.y = y;
	}

	MTest::MTest(LPLOGGER inLog)
	{
		speed.y = speed.x = 1;
		_log = inLog;
	}


	MTest::~MTest()
	{
	}

	void MTest::Move2D(LPVECTOR2D pos)
	{
		using std::endl;
		using std::ostringstream;
		ostringstream out;

		int orgX = pos->x;
		// Handle x movement
		if (pos->x > 70 && speed.x > 0)
		{
			speed.x = speed.x * -1;
		}else if (pos->x < 5 && speed.x < 0)
		{
			speed.x = speed.x * -1;
		}

		if (pos->y > 15 && speed.y > 0)
		{
			speed.y = speed.y * -1;
		}else if (pos->y < 5 && speed.y < 0)
		{
			speed.y = speed.y * -1;
		}

		pos->x += speed.x;
		pos->y += speed.y;

		out << "Point[" << pos->x << ", " << pos->y << "]";
		Log(out.str());
	}

	LPMOVER MTest::SetLogger(LPLOGGER inLog)
	{
		_log = inLog;
		return this;
	}

	void MTest::Log(std::string line)
	{
		if (_log != NULL)
		{
			_log->WriteLine(line);
		}
	}

} }// End namespace Zaxis::Core