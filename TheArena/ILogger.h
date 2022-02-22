#ifndef H_ILOGGER
#define H_ILOGGER

#include <string>

#define LPLOGGER Zaxis::Logging::ILogger*

namespace Zaxis{ namespace Logging
{

	class ILogger
	{
	public:
		ILogger();
		virtual ~ILogger();

		virtual void WriteLine(std::string line) = 0;
		virtual void Write(std::string line) = 0;

		virtual void Save(bool append=true) = 0;
	};

} }// End namespace Zaxis::Logging

#endif