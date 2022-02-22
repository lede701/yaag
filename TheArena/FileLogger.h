#ifndef H_FILELOGGER
#define H_FILELOGGER

#include <deque>
#include <iostream>
#include <fstream>
#include <sstream>

#include "ILogger.h"

namespace Zaxis{ namespace Logging
{
	using std::ofstream;
	using std::ostringstream;
	using std::endl;
	using std::deque;

	class FileLogger :
		public ILogger
	{
	private:
		deque<std::string> fileData;
		unsigned int MaxLines;

		std::string FileName;

	public:
		FileLogger(std::string inFileName, int inMaxSize = 200);
		virtual ~FileLogger();

		virtual void Write(std::string line);
		virtual void WriteLine(std::string line);

		virtual void Save(bool append=true);
	};

} }// End namespace Zaxis::Logging

#endif