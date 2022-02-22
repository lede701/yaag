#ifndef H_ILOGIN
#define H_ILOGIN

#include <string>
#include "ArmorData.h"
#include "MonsterData.h"
#include "WeaponData.h"
#include "DataLocation.h"

#define LPLOGIN Zaxis::Network::ILogin*

namespace Zaxis{ namespace Network
{
	using Zaxis::Data::DataLocation;

	class ILogin
	{
	public:
		enum LoginMessage
		{
			LM_OK = 0,
			LM_NEW = 1,
			LM_ERROR = 2,
			LM_SAVEERROR = 3,
			LM_LOADERROR = 4
		};

		virtual int Init() = 0;
		virtual LoginMessage LoginCall(const std::string &login, const std::string &password) = 0;
		virtual LoginMessage LoginNow(const std::string &login, const std::string &password) = 0;
		virtual LoginMessage Login(const std::string &login, const std::string &password) = 0; // Alias to login now
		virtual int Logout() = 0;
		virtual int Logout(bool savePlayerState) = 0;

		virtual int Save() = 0;

		virtual bool CreatePassword() = 0;
		virtual int CreatePlayer(const std::string &name, const std::string &password) = 0;
		virtual bool UniqueName(const std::string &name) = 0;

		virtual LoginMessage GetData(void* data, int size) = 0; // Get primary player data
		virtual LoginMessage GetData(const std::string &key, void* data, int size) = 0;
		virtual LoginMessage SetData(void* data, int size) = 0; // Set the primary player data
		virtual LoginMessage SetData(const std::string &key, void* data, int size) = 0;

		virtual void SaveScore(int score, const std::string &name) = 0;

		virtual DataLocation GetLocation() = 0;

	};
} }// End namespace Zaxis::Network

#endif