#ifndef H_FIELDGROUP
#define H_FIELDGROUP

#include "IMenuScreen.h"
#include "IDrawField.h"
#include "IMenuMonster.h"
#include "IMenuState.h"
#include "BaseMenu.h"
#include "CtrlMenu.h"
#include "PlayerMenu.h"
#include "MonsterMenu.h"
#include "PlayerEntity.h"
#include "PlayerCommand.h"
#include "GameField.h"
#include "zmath.h"

#define PLCMDCOUNT 16

namespace Game{ namespace Graphics{ namespace Menus
{

	class FieldGroup :
		public IMenuScreen, public IDrawField, public IMenuMonster
	{
		LPMENUSCREEN _back;
		PlayerMenu* _player;
		MonsterMenu* _monster;
		LPMENUSCREEN _field;
		LPMENUSCREEN _cmds;
		LPMENUSTATE _stateManager;

		bool _isDirty;

		LPPLCOMMAND cmds[PLCMDCOUNT];
		// Input controller
		LPCONTROLLER _controller;
		LPGRAPHICS graphics;

		LPPLAYERENTITY plEntity;
		LPMONSTERENTITY monEntity;

		LPRECT2D _gameField;
		LPVECTOR2D _exit;

	public:
		FieldGroup(LPRECT2D GameFeild, LPVECTOR2D exit);
		virtual ~FieldGroup();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();

		virtual bool IsDirty();
		virtual void DirtyMe();


		virtual LPMENUSCREEN SetController(LPCONTROLLER ctrl);
		virtual LPMENUSCREEN SetGraphics(LPGRAPHICS gfx);

		virtual LPMENUSCREEN SetPlayer(LPPLAYERENTITY player);
		virtual void SetMonster(LPMONSTERENTITY monster);

		virtual void SetStateManager(LPMENUSTATE manager);

		// Get field information
		virtual LPVECTOR2D GetExit();
		virtual LPRECT2D GetArean();

		virtual void DrawField();
		virtual void PlayerDied();

		// Interface to draw monster menu
		virtual void DrawMonster(LPGRAPHICS gfx, LPMONSTERENTITY monster);

	};

} } }// End namespace Game::Graphics::Menus


#endif