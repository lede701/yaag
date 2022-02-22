#include "NullLogger.h"

namespace Zaxis{ namespace Logging
{

	NullLogger::NullLogger()
	{
	}


	NullLogger::~NullLogger()
	{
	}

	void NullLogger::Write(std::string line)
	{

	}

	void NullLogger::WriteLine(std::string line)
	{

	}

	void NullLogger::Save(bool append /* = true */)
	{

	}

} }// End namespace Zaxis::Logging

