#include "ConsoleLogger.h"

namespace Zaxis{ namespace Logging
{

	ConsoleLogger::ConsoleLogger()
	{
		while (!Log.empty())
		{
			Log.pop_front();
		}
	}


	ConsoleLogger::~ConsoleLogger()
	{
		while (!Log.empty())
		{
			Log.pop_front();
		}
	}

	void ConsoleLogger::WriteLine(std::string line)
	{
		Write(line);
	}

	void ConsoleLogger::Write(std::string line)
	{
		Log.push_back(line);
		// Make sure we have not reached the max size of the deque
		if (Log.size() == Log.max_size())
		{
			// Clear deque by saving
			Save();
		}
	}

	void ConsoleLogger::Save(bool append)
	{
		while (!Log.empty())
		{
			cout << Log.front() << endl;
			Log.pop_front();
		}
	}

} }// End namespace Zaxis::Logging

