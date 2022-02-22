#ifndef H_FLOGIN
#define H_FLOGIN

#include <string>

#include "ILogin.h"
#include "IData.h"
#include "FileData.h"
#include "FileIO.h"
#include "ArmorData.h"
#include "MonsterData.h"
#include "PlayerData.h"
#include "WeaponData.h"

#define FL_OK 0x00000000;
#define FL_MISSING_ARDATA 0x00000001;
#define FL_MISSING_MODATA 0x00000010;
#define FL_MISSING_WEDATA 0x00000100;
#define FL_MISSING_PLDATA 0x00001000;

namespace Game{ namespace File
{
	using Zaxis::FileData;
	using Zaxis::Data::DataLocation;
	using Game::Data::ArmorData;
	using Game::Data::MonsterData;
	using Game::Data::WeaponData;
	using Game::Data::PlayerData;

	class FLogin
		: public Zaxis::Network::ILogin, public Game::Data::IData
	{
	private:

		FileData<ArmorData> *paData;
		FileData<MonsterData> *pmData;
		FileData<WeaponData> *pwData;
		FileData<PlayerData> *pPlData;

		std::string plFile;
		PlayerData _player;

		std::string StrToUpper(const std::string &s);

		DataLocation _location;

	public:
		FLogin();
		virtual ~FLogin();

		virtual int Init();

		virtual Zaxis::Network::ILogin::LoginMessage Login(const std::string &login, const std::string &password); // Alias to login now
		virtual int Logout();
		virtual int Save();

		virtual Zaxis::Network::ILogin::LoginMessage LoginCall(const std::string &login, const std::string &password);
		virtual Zaxis::Network::ILogin::LoginMessage LoginNow(const std::string &login, const std::string &password);

		virtual int Logout(bool savePlayerState);

		virtual bool CreatePassword();
		virtual int CreatePlayer(const std::string &name, const std::string &password);
		virtual bool UniqueName(const std::string &name);

		virtual Zaxis::Network::ILogin::LoginMessage GetData(void* data, int size); // Get primary player data
		virtual Zaxis::Network::ILogin::LoginMessage GetData(const std::string &key, void* data, int size);
		virtual Zaxis::Network::ILogin::LoginMessage SetData(void* data, int size); // Set the primary player data
		virtual Zaxis::Network::ILogin::LoginMessage SetData(const std::string &key, void* data, int size);

		virtual void SaveScore(int score, const std::string &name);

		virtual Game::Data::ArmorData GetArmor(int id);
		virtual Game::Data::MonsterData GetMonster(int id);
		virtual Game::Data::WeaponData GetWeapon(int id);

		virtual DataLocation GetLocation();

	};

} }// End namepsace Game::File

#endif