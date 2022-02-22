#include "PlayerHelper.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

namespace Game{ namespace Data
{
	using std::ifstream;
	using std::ofstream;

	unsigned int PlayerHelper::size = sizeof(PlayerData);
	std::string PlayerHelper::file = "players.dat";

	PlayerHelper::PlayerHelper() : plData(1)
	{
		plData.Load(file);
		if (plData.GetVersion() != 1)
		{
			// Uh oh we have a version mismatch
		}
	}

	PlayerHelper::~PlayerHelper()
	{

	}

	bool PlayerHelper::Load(PlayerData* p)
	{
		bool bRetVal = false;
		p = plData.GetAt(plData.NextPos());
		bRetVal = p != NULL;
		return bRetVal;
	}

	bool PlayerHelper::Load(PlayerData* p, unsigned int Id)
	{
		bool bRetVal = false;
		p = plData.GetAt(Id - 1);
		bRetVal = p != NULL;
		return bRetVal;
	}

	bool PlayerHelper::Load(PlayerData* p, std::string name)
	{
		bool bRetVal = false;
		// Create a data contrainer for the search algorithm
		PlayerData* data = NULL;
		// Set file position to the top
		pos = 0;
		// Create file stgream
		std::string plName(name);
		std::transform(plName.begin(), plName.end(), plName.begin(), ::toupper);

		data = plData.Front();
		do
		{
			if (data->name == plName)
			{
				bRetVal = true;
				p = data;
				break;
			}
			data = plData.GetAt(plData.NextPos());
		} while (data != NULL);

		return bRetVal;
	}

	bool PlayerHelper::Login(std::string name, std::string passwd)
	{
		bool bRetVal = false;
		// Try and find player login by name
		PlayerData data;
		if (Load(&data, name))
		{
			std::string pw(data.passwd);
			if (pw == passwd)
			{
				bRetVal = true;
			}
		}

		return bRetVal;
	}

	void PlayerHelper::Save(PlayerData* p)
	{
		plData.Save(file);
	}

	void PlayerHelper::Save(PlayerData* p, unsigned int id)
	{
		plData.Save(file);
	}

} }// End namespace Game::Data