#include "fLogin.h"
#include "StrToHash.h"
#include "PlayerCreator.h"

#include <algorithm>

namespace Game{ namespace File
{
	FLogin::FLogin()
	{
		paData = NULL;
		pmData = NULL;
		pwData = NULL;

		ZeroMemory(&_player, sizeof(PlayerData));
		_location = DataLocation::DL_LOCAL;
	}

	FLogin::~FLogin()
	{
		// Check if the files have been cleared yet
		if (paData != NULL)
		{
			delete paData;
			paData = NULL;
		}
		if (pmData != NULL)
		{
			delete pmData;
			pmData = NULL;
		}
		if (pwData != NULL)
		{
			delete pwData;
			pwData = NULL;
		}
		if (pPlData != NULL)
		{
			Save();
			delete pPlData;
			pPlData = NULL;
		}
	}

	int FLogin::Init()
	{
		int retVal = -1;

		plFile = GetAppPath() + "\\players.dat";
		// Define file data paths
		std::string aFile = GetAppPath() + "\\armor.dat";
		std::string mFile = GetAppPath() + "\\monster.dat";
		std::string wFile = GetAppPath() + "\\weapons.dat";

		// Check to see if we can load armor data
		if (FileExists(aFile))
		{
			paData = new FileData<ArmorData>();
			paData->Load(aFile);
		}
		else
		{
			retVal = FL_MISSING_ARDATA;
		}

		// Check to see if we can load monster data
		if (FileExists(mFile))
		{
			pmData = new FileData<MonsterData>();
			pmData->Load(mFile);
		}
		else
		{
			retVal = FL_MISSING_MODATA;
		}

		pPlData = new FileData<PlayerData>();
		// Check to see if we can load player data
		if (FileExists(plFile))
		{
			pPlData->Load(plFile);
		}
		else
		{
			CreateAdminPlayer("Admin", StrToHash("maser2015"), &_player);
			_player.id = pPlData->GetNextId();
			pPlData->Add(_player);
			pPlData->Save(plFile);
			ZeroMemory(&_player, sizeof(PlayerData));
			retVal = FL_MISSING_PLDATA;
		}

		if (FileExists(wFile))
		{
			pwData = new FileData<WeaponData>();
			pwData->Load(wFile);
		}
		else
		{
			retVal = FL_MISSING_WEDATA;
		}

		return retVal;
	}

	Zaxis::Network::ILogin::LoginMessage FLogin::Login(const std::string &login, const std::string &password)
	{
		return LoginNow(login, password);
	}

	int FLogin::Logout()
	{
		return 0;
	}

	int FLogin::Save()
	{
		pPlData->Add(_player, _player.id - 1);
		pPlData->Save(plFile);
		return 0;
	}

	Zaxis::Network::ILogin::LoginMessage FLogin::LoginCall(const std::string &login, const std::string &password)
	{
		ILogin::LoginMessage msg = ILogin::LoginMessage::LM_ERROR;

		return msg;
	}
	
	Zaxis::Network::ILogin::LoginMessage FLogin::LoginNow(const std::string &login, const std::string &password)
	{
		// Initialize login message to error by default
		ILogin::LoginMessage msg = ILogin::LoginMessage::LM_ERROR;
		// Convert login name to upper case for easier comparison

		std::string chkLogin = StrToUpper(login);
		// Get hash version of password
		std::string pwHash = StrToHash(password);

		// Setup do loop tracking parameters
		unsigned int lastPos = pPlData->Back().id;
		pPlData->Front();
		unsigned int pos = 0;
		do
		{
			// See if current position is login name
			if (chkLogin == StrToUpper(pPlData->Current().name))
			{
				if (pPlData->Current().passwd == pwHash)
				{
					msg = ILogin::LoginMessage::LM_OK;
					_player = pPlData->Current();
					// We found player and they are valid so quit looking
					break;
				}
			}

			// Move to next record for searching
			pos = pPlData->NextPos();
		} while (pos != lastPos);

		return msg;
	}

	int FLogin::Logout(bool savePlayerState)
	{
		Save();
		ZeroMemory(&_player, sizeof(PlayerData));
		return 0;
	}

	bool FLogin::CreatePassword()
	{
		return true;
	}

	int FLogin::CreatePlayer(const std::string &name, const std::string &password)
	{
		int retVal = 0;
		::CreatePlayer(name, StrToHash(password), &_player);
		_player.id = pPlData->GetNextId();
		pPlData->Add(_player);
		pPlData->Save(plFile);

		return retVal;
	}
	
	bool FLogin::UniqueName(const std::string &name)
	{
		bool bRetVal = true;
		int posBack = pPlData->Back().id;
		int pos = 0;
		std::string chkName = StrToUpper(name);
		do
		{
			if (chkName == StrToUpper(pPlData->Current().name))
			{
				bRetVal = false;
				break;
			}
			pos = pPlData->NextPos();
		} while (pos != posBack);

		return bRetVal;
	}

	Zaxis::Network::ILogin::LoginMessage FLogin::GetData(void* data, int size)
	{
		return GetData("Player", data, size);
	}
	
	Zaxis::Network::ILogin::LoginMessage FLogin::GetData(const std::string &key, void* data, int size)
	{
		ILogin::LoginMessage msg = ILogin::LoginMessage::LM_ERROR;
		if (key == "Player")
		{
			memcpy(data, &_player, size);
			msg = ILogin::LoginMessage::LM_OK;
		}

		return msg;
	}
	
	Zaxis::Network::ILogin::LoginMessage FLogin::SetData(void* data, int size)
	{
		Zaxis::Network::ILogin::LoginMessage msg = SetData("Player", data, size);
		Save();
		return msg;
	}
	
	Zaxis::Network::ILogin::LoginMessage FLogin::SetData(const std::string &key, void* data, int size)
	{
		ILogin::LoginMessage msg = ILogin::LoginMessage::LM_ERROR;
		if (key == "Player")
		{
			memcpy(&_player, data, size);
			msg = ILogin::LoginMessage::LM_OK;
		}

		return msg;
	}

	// The file version doesn't save a score yet
	void FLogin::SaveScore(int score, const std::string &name)
	{

	}
		
	ArmorData FLogin::GetArmor(int id)
	{
		ArmorData data;
		ZeroMemory(&data, sizeof(ArmorData));
		if (paData != NULL)
		{
			data = paData->GetAt(static_cast<unsigned int>(id));
		}

		return data;
	}
	
	MonsterData FLogin::GetMonster(int id)
	{
		MonsterData data;
		ZeroMemory(&data, sizeof(MonsterData));
		if (pmData != NULL)
		{
			data = pmData->GetAt(id);
		}

		return data;
	}
	
	WeaponData FLogin::GetWeapon(int id)
	{
		WeaponData data;
		ZeroMemory(&data, sizeof(WeaponData));
		if (pwData != NULL)
		{
			data = pwData->GetAt(id);
		}

		return data;
	}

	DataLocation FLogin::GetLocation()
	{
		return _location;
	}

	std::string FLogin::StrToUpper(const std::string &s)
	{
		std::string ns = s;
		std::transform(ns.begin(), ns.end(), ns.begin(), ::toupper);

		return ns;
	}

} }// End namepsace Game::File
