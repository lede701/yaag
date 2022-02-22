#ifndef H_CONGRAPHICS
#define H_CONGRAPHICS

#include <iostream>
#include <windows.h>

#include "IGraphics.h"
#include "Vector2D.h"
#include "ConColor.h"
#include "ConObject.h"
#include "BoxType.h"

#define SIZE_X 79
#define SIZE_Y 23

// I'm freaking lazy and am tired of typing this large function name
#define SetConPos SetConsoleCursorPosition
#define SetColor SetConsoleTextAttribute

/// Links:
/// http://www.asciitable.com/
/// http://www.gamefaqs.com/bbs/924352-the-pit/images/screen-2

namespace Zaxis{ namespace Graphics
{
	using std::cout;
	using Zaxis::Graphics::ConGraphicsData::BoxType;
	using Zaxis::Graphics::ConGraphicsData::ConColor;

	class ConGraphics :
		public IGraphics
	{
	private:
		HANDLE hnd;
		CONSOLE_CURSOR_INFO info;
		LPVECTOR2D _pos;

		char field[SIZE_X][SIZE_Y];

		WORD currentColor;
	public:
		ConGraphics();
		virtual ~ConGraphics();

		virtual void Init();
		virtual void Dispose();
		virtual void Update();

		virtual void SetConsoleSize(int wiodth, int height);
		virtual void SetConCursor(bool bVal);

		virtual void Draw(LPENTITY obj);
		virtual void Draw(LPOBJECT obj);
		virtual void DrawRect(LPRECT2D rect, void* ch, void* bkg);
		virtual void DrawRect(LPRECT2D rect, void* ch);

		// Special draw rect
		virtual void DrawRect(LPRECT2D rect, BoxType type);
		virtual void DrawFillRect(LPRECT2D rect, BoxType type, WORD color);

		virtual void DrawText(const std::string& line, LPVECTOR2D pos);
		virtual void DrawText(const std::string& line, LPVECTOR2D pos, WORD color);
		virtual void DrawText(const std::string& line, int x, int y);
		virtual void DrawText(const std::string& line, int x, int y, WORD color);
		virtual void DrawText(unsigned char c, int x, int y);
		virtual void DrawText(unsigned char c, int x, int y, WORD color);

		virtual void SetPos(COORD c);
		virtual void SetPos(int x, int y);
		virtual void SetCursorPos(int x, int y);
		virtual void SetTextColor(int clr);
		virtual int GetTextColor();
		virtual void SetPos(LPVECTOR2D pos);

		virtual void Flush();

		void SetDebugPoint(LPVECTOR2D pos);

		COORD GetCursorPos();
		void UpdateField();
	};

} }// End namespace Zaxis::Graphics

#endif