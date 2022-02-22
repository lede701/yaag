#ifndef H_IMENUSTATE
#define H_IMENUSTATE

#include "PlayerData.h"
#include "ILogin.h"
#include "IData.h"
#include "Loot.h"

#define LPMENUSTATE Game::Graphics::Menus::IMenuState*

namespace Game{ namespace Graphics{ namespace Menus
{

	enum MenuState
	{
		MS_NONE,
		MS_LOGIN,
		MS_CONFIG,
		MS_CONFIG_SAVE,
		MS_HOME,
		MS_SELECTION,
		MS_FIGHTMONSTER,
		MS_GAMEFIELD,
		MS_STORE,
		MS_DIED,
		MS_REVIVE,
		MS_RESURECTDEAD,
		MS_REVIVEENOUGH,
		MS_CHARACTER,
		MS_LEVELUP,
		MS_WIN,
		MS_FLEEWIN,
		MS_PLAYERLIST,
		MS_PLAYERDETAILS,
		MS_EXIT
	};

	class IMenuState
	{
	public:
		IMenuState();
		virtual ~IMenuState();

		virtual void LoadPlayer(int playerId) = 0;
		virtual void LoadPlayer(Game::Data::PlayerData* data) = 0;
		virtual void SavePlayer(bool saveScore) = 0;
		virtual void PushState(MenuState state) = 0;
		virtual void PopState() = 0;
		virtual void Pause(bool pause) = 0;

		virtual void SetLoginController(LPLOGIN login) = 0;
		virtual void SetDataController(LPDATA data) = 0;
		virtual void AddLoot(LPLOOT loot) = 0;
	};

} } }// End namespace Game::Graphics::Menus


#endif