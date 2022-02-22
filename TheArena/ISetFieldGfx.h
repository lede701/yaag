#ifndef H_ISETFIELDGFX
#define H_ISETFIELDGFX

#include "PlayerEntity.h"
#include "IController.h"
#include "IData.h"
#include "PlayerData.h"

#define LPFIELDGFX Game::Entity::ISetFieldGfx*

namespace Game{ namespace Entity
{

	class ISetFieldGfx
	{
	public:
		virtual LPPLAYERENTITY CreatePlayer(LPVECTOR2D pos, int id, Game::Data::PlayerData* pData, LPCONTROLLER ctrl) = 0;
		virtual void SetDrawField(LPDRAWFIELD gfx) = 0;
		virtual LPPLAYERENTITY SetPlayer(LPPLAYERENTITY player) = 0;
		virtual void SetField(LPRECT2D field, LPRECT2D arena) = 0;
		virtual void SetExit(LPVECTOR2D exit) = 0;
		virtual void SetDataController(LPDATA data) = 0;
		virtual void Pause(bool pause) = 0;
	};

} }// End namespace Game::Entity

#endif