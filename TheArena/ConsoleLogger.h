#ifndef H_CONSOLELOGGER
#define H_CONSOLELOGGER

#include <iostream>
#include <deque>

#include "ILogger.h"

namespace Zaxis{ namespace Logging
{
	using std::cout;
	using std::endl;

	class ConsoleLogger :
		public ILogger
	{
	private:
		std::deque<std::string> Log;
	public:
		ConsoleLogger();
		~ConsoleLogger();

		virtual void WriteLine(std::string line);
		virtual void Write(std::string line);

		virtual void Save(bool append=true);
	};

} }// End namespace Zaxis::Logging

#endif