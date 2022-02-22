#ifndef H_PLAYERHELPER
#define H_PLAYERHELPER

#include <string>
#include "PlayerData.h"
#include "FileData.h"

namespace Game{	namespace Data
{
	using Zaxis::FileData;

	class PlayerHelper
	{
	private:
		FileData<PlayerData*> plData;
	public:
		PlayerHelper();
		virtual ~PlayerHelper();

		static unsigned int size;
		static std::string file;

		unsigned int pos;
		bool Load(PlayerData* p);
		bool Load(PlayerData* p, unsigned int id);
		bool Load(PlayerData* p, std::string name);


		bool Login(std::string name, std::string passwd);

		void Save(PlayerData* p);
		void Save(PlayerData* p, unsigned int id);
	};

} }

#endif