#include "BaseSelector.h"

namespace Game{ namespace Graphics{ namespace Menus
{

	BaseSelector::BaseSelector(WORD color, WORD highlight, int width)
	{
		textColor = color;
		highlightColor = highlight;
		LineSize = width;
	}

	BaseSelector::~BaseSelector()
	{

	}

	void BaseSelector::DrawLine(Zaxis::Graphics::ConGraphics* cGfx, std::string line, int x, int y, bool IsSelected)
	{
		if (IsSelected)
		{
			int spaceSize = max(0, LineSize - line.length());
			if (spaceSize > 0)
			{
				std::string whiteSpace(spaceSize, ' ');
				line += whiteSpace;
			}
			cGfx->DrawText(line, x, y, highlightColor);
		}
		else
		{
			cGfx->DrawText(line, x, y, textColor);
		}
	}

	void BaseSelector::DrawLine(Zaxis::Graphics::ConGraphics* cGfx, char cmd, std::string line, int x, int y, WORD cmdColor, bool IsSelected)
	{
		std::ostringstream out;
		out << "[ ] ";
		int cmdWidth = out.str().length();
		cGfx->DrawText(out.str(), x, y, textColor);
		out.str(""); out.clear();

		out << cmd;
		cGfx->DrawText(out.str(), x + 1, y, cmdColor);
		out.str(""); out.clear();

		if (IsSelected)
		{
			int spaceSize = max(0, LineSize - line.length() - cmdWidth);
			if (spaceSize > 0)
			{
				std::string whiteSpace(spaceSize, ' ');
				line += whiteSpace;
			}
			cGfx->DrawText(line, x + cmdWidth, y, highlightColor);
		}
		else
		{
			cGfx->DrawText(line, x + cmdWidth, y, textColor);
		}
	}

	void BaseSelector::DrawTitle(Zaxis::Graphics::ConGraphics* cGfx, std::string text, Zaxis::Math::Rect* box, WORD color, WORD titleColor)
	{
		std::string title(text.length() + 4, ' ');
		title[0] = 221;
		title[title.length() - 1] = 222;
		int x = box->X + ((box->Width / 2) - (title.length() / 2));
		int y = box->Y;
		cGfx->DrawText(title, x, y, color);
		cGfx->DrawText(text, x + 2, y, titleColor);
	}

	void BaseSelector::DrawCmd(Zaxis::Graphics::ConGraphics* cGfx, char key, std::string cmd, int x, int y, WORD clr, WORD keyClr)
	{
		std::ostringstream out;
		out << "[ ] " << cmd;
		cGfx->DrawText(out.str(), x, y, clr);
		out.str(""); out.clear();

		out << key;
		cGfx->DrawText(out.str(), x + 1, y, keyClr);
		out.str(""); out.clear();
	}

	void BaseSelector::DrawCmd(Zaxis::Graphics::ConGraphics* cGfx, std::string key, std::string cmd, int x, int y, WORD clr, WORD keyClr)
	{
		DrawCmd(cGfx, key, cmd, x, y, 0, clr, keyClr);
	}

	void BaseSelector::DrawCmd(Zaxis::Graphics::ConGraphics* cGfx, std::string key, std::string cmd, int x, int y, int maxWidth, WORD clr, WORD keyClr)
	{
		std::ostringstream out;
		std::string space(key.length(), ' ');
		int extSpace = 0;
		if (key.length() < maxWidth)
		{
			extSpace = maxWidth - key.length();
		}
		std::string wSpace(extSpace, ' ');

		out << "[" << space << "] " << wSpace << cmd;

		cGfx->DrawText(out.str(), x, y, clr);
		out.str(""); out.clear();

		cGfx->DrawText(key, x + 1, y, keyClr);
	}

} } }// End namespace Game::Graphics::Menus
