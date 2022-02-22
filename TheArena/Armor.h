#ifndef H_ARMOR
#define H_ARMOR

#include "IArmor.h"
#include "ArmorData.h"
#include "FileData.h"
#include <string>

namespace Game{ namespace Items{ namespace Armor
{
	using Game::Data::ArmorData;
	using Zaxis::FileData;
	using Game::Data::CharacterData;

	class Armor :
		public IArmor
	{
	private:
		ArmorData data;
		unsigned int size;

	public:
		Armor(ArmorData inData);
		~Armor();

		void Init();

		virtual int GetDefense();
		virtual int GetPlus();
		virtual std::string GetName();

		virtual void SetData(ArmorData* data);
		virtual LPCHARACTER GetCharacter();

		virtual int GetNextId();

	};

} } }// End namespace Game::Items::Armor


#endif