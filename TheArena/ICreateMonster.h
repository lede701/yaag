#ifndef H_ICREATEMONSTER
#define H_ICREATEMONSTER

#include "MonsterEntity.h"
#include "MonsterEnum.h"

#define LPMCREATOR Game::Entity::ICreateMonster*

namespace Game{ namespace Entity
{
	using Game::Monsters::Entities::MonsterType;

	class ICreateMonster
	{
	public:
		ICreateMonster();
		virtual ~ICreateMonster();

		virtual LPMONSTERENTITY CreateMonster(unsigned int type) = 0;
		virtual LPMONSTERENTITY CreateMonster(unsigned int type, LPVECTOR2D pos) = 0;
		virtual LPMONSTERENTITY CreateRndMonster() = 0;
		virtual LPMONSTERENTITY GetMonster() = 0;
	};

} }// End namespace Game::Entity

#endif