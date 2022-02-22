#ifndef H_GAMEFIELDMENU
#define H_GAMEFIELDMENU

#include "IMenuScreen.h"
#include "IFieldExit.h"
#include "zmath.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	using Zaxis::Math::Rect;
	using Game::Data::IFieldExit;

	class GameField :
		public IMenuScreen, IFieldExit
	{
	private:
		Rect _gameField;
		LPVECTOR2D _exit;
		bool _isDirty;
		LPGRAPHICS _gfx;

	public:
		GameField(Rect GameField, LPVECTOR2D exit);
		virtual ~GameField();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();
		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual LPVECTOR2D GetExit();
		virtual void SetExit(LPVECTOR2D exit);
	};

} } }// End namespace Game::Graphics::Menus

#endif