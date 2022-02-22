#include "FileUtilities.h"
#include "PlayerData.h"
#include "FileData.h"

#include <algorithm>

void ValidateFile(std::string file, ValidateType type)
{
	switch (type)
	{
	case ValidateType::VT_PLAYER:
		Zaxis::FileData<Game::Data::PlayerData> pData;
		pData.Load(file);
		if (pData.GetVersion() != PLDBVER)
		{
			PlayerDbUpdate(file, pData.GetVersion());
		}
		break;
	}
}

bool PlayerDbUpdate(std::string file, int ver)
{
	bool bRetVal = false;
	int nVer = 0;

	switch (ver)
	{
	default:
		bRetVal = false;
		break;
	}

	if (bRetVal) PlayerDbUpdate(file, nVer);

	return bRetVal;
}