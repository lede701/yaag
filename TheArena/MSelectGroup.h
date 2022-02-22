#ifndef H_MSELECTGROUP
#define H_MSELECTGROUP

#include "MSelect.h"
#include "IData.h"

namespace Game{ namespace Graphics{ namespace Menus
{

	class MSelectGroup : public IMenuScreen
	{
	private:
		bool _isDirty;

		LPMENUSCREEN _selector;
		LPMENUSCREEN _bkg;
		LPMENUSCREEN _cmds;
		LPMENUSCREEN _player;

		LPMENUSTATE _manager;
		LPCONTROLLER _controller;
		LPPLAYERENTITY _plEntity;

	public:
		MSelectGroup(int x, int y);
		virtual ~MSelectGroup();

		virtual void Draw(LPGRAPHICS gfx);
		virtual void Clear(LPGRAPHICS gfx);
		virtual void Update();
		virtual bool Shutdown();

		virtual LPMENUSCREEN GetSelector();

		virtual bool IsDirty();
		virtual void DirtyMe();

		virtual void SetStateManager(LPMENUSTATE manager);
		virtual void SetController(LPCONTROLLER ctrl);
		virtual void SetDataController(LPDATA data);
		virtual void SetPlayer(LPPLAYERENTITY player);

	};

} } }// End namespace Game::Graphics::Menus


#endif