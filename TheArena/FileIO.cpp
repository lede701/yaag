#include "FileIO.h"

std::string GetAppPath()
{
	std::string path = "";

	char result[MAX_PATH];
	std::string appFile = std::string(result, GetModuleFileNameA(NULL, result, MAX_PATH));
	int endPos = 0;
	int slashes = 1;
	for (int i = appFile.length() - 1; i > 0; i--)
	{
		if (appFile[i] == '\\')
			slashes--;
		if (slashes == 0)
		{
			endPos = i;
			break;
		}
	}

	path = appFile.substr(0, endPos);

	return path;
}

bool DirExists(std::string path, bool create)
{
	DWORD dAttr = GetFileAttributesA(path.c_str());
	bool bRetVal = false;
	if (dAttr == INVALID_FILE_ATTRIBUTES && create)
	{
		// Time to create directory
		CreateDirectoryA(path.c_str(), NULL);
		bRetVal = true;
	}
	else
	{
		bRetVal = true;
	}

	return bRetVal;
}

bool FileExists(std::string file)
{
	DWORD fAttr = GetFileAttributesA(file.c_str());
	bool bRetVal = false;

	if (fAttr != INVALID_FILE_ATTRIBUTES)
	{
		bRetVal = true;
	}

	return bRetVal;
}
