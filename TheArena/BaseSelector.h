#ifndef H_BASESELECTOR
#define H_BASESELECTOR

#include "IMenuScreen.h"
#include "ConGraphics.h"
#include "zmath.h"

namespace Game{ namespace Graphics{ namespace Menus
{

	class BaseSelector
		: public IMenuScreen
	{
	private:
		WORD textColor;
		WORD highlightColor;

		int LineSize;

	protected:

	public:
		BaseSelector(WORD color, WORD highlight, int width);
		virtual ~BaseSelector();

		virtual void DrawLine(Zaxis::Graphics::ConGraphics* cGfx, std::string line, int x, int y, bool IsSelected);
		virtual void DrawLine(Zaxis::Graphics::ConGraphics* cGfx, char cmd, std::string line, int x, int y, WORD cmdColor, bool IsSelected);
		virtual void DrawTitle(Zaxis::Graphics::ConGraphics* cGfx, std::string line, Zaxis::Math::Rect* box, WORD color, WORD titleColor);
		virtual void DrawCmd(Zaxis::Graphics::ConGraphics* cGfx, char key, std::string cmd, int x, int y, WORD clr, WORD keyClr);
		virtual void DrawCmd(Zaxis::Graphics::ConGraphics* cGfx, std::string key, std::string cmd, int x, int y, WORD clr, WORD keyClr);
		virtual void DrawCmd(Zaxis::Graphics::ConGraphics* cGfx, std::string key, std::string cmd, int x, int y, int width, WORD clr, WORD keyClr);

	};

} } }// End namespace Game::Graphics::Menus

#endif