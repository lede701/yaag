#ifndef H_NULL_LOGGER
#define H_NULL_LOGGER

#include "ILogger.h"

namespace Zaxis{ namespace Logging
{

	class NullLogger :
		public ILogger
	{
	public:
		NullLogger();
		~NullLogger();

		virtual void WriteLine(std::string line);
		virtual void Write(std::string line);

		virtual void Save(bool append = true);
	};

} }// End namespace Zaxis::Logging

#endif