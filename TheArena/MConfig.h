#ifndef H_MCONFIG
#define H_MCONFIG

#include "BaseSelector.h"
#include "IMenuState.h"
#include "ILogin.h"
#include "IData.h"
#include "ConGraphics.h"
#include "DataLocation.h"

namespace Game{ namespace Graphics{ namespace Menus
{
	using Zaxis::Data::DataLocation;

	class MConfig : public BaseSelector
	{
	private:
		bool _isDirty;

		LPMENUSTATE _stateManager;

		Zaxis::Math::Rect _box;

		WORD txtColor;
		WORD cmdColor;
		WORD highColor;
		WORD boxColor;

		LPLOGIN _loginCtrl;
		LPDATA _dataCtrl;

		LPCONTROLLER _controller;

		DataLocation _loginDb;
		DataLocation _gameDb;

	public:
		MConfig(int x, int y);
		virtual ~MConfig();

		void InitControllers();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();

		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual void SetStateManager(LPMENUSTATE manager);
		virtual void SetController(LPCONTROLLER ctrl);

		virtual bool Shutdown();

		// TODO: Do we really need this?
		virtual LPDATA GetDataController();
		virtual LPLOGIN GetLoginController();

	};
} } }// End namespace Game::Graphics::Menus
#endif