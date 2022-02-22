#include "FileLogger.h"


namespace Zaxis{ namespace Logging
{

	FileLogger::FileLogger(std::string inFileName, int inMaxSize)
	{
		MaxLines = inMaxSize;
		FileName = inFileName;
	}


	FileLogger::~FileLogger()
	{
	}

	void FileLogger::Write(std::string line)
	{
		fileData.push_back(line);
		// Add to deque
		if (fileData.size() > MaxLines)
		{
			Save(true);
		}
	}

	void FileLogger::WriteLine(std::string line)
	{
		Write(line);
	}

	void FileLogger::Save(bool append)
	{

		ofstream out;
		if (append)
		{
			out.open(FileName, std::ofstream::app);
		}
		else
		{
			out.open(FileName);
		}

		while (!fileData.empty())
		{
			out << fileData.front() << endl;
			fileData.pop_front();
		}

		out.close();
	}

} }// End namespace Zaxis::Logging
