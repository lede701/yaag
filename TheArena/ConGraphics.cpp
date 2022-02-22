#include "ConGraphics.h"

namespace Zaxis{ namespace Graphics
{

	ConGraphics::ConGraphics()
	{
		hnd = GetStdHandle(STD_OUTPUT_HANDLE);
		SetPos(0,23);
		SMALL_RECT rect = { 0, 0, 100, 100 };
		SetConsoleWindowInfo(hnd, TRUE, &rect);
#ifdef _DEBUG
		SetConsoleSize(80, 40);
#else
		SetConsoleSize(80, 37);
#endif

		// Turn off cursor
		info.dwSize = 4;
		info.bVisible = TRUE;
		SetConsoleCursorInfo(hnd, &info);
	}


	ConGraphics::~ConGraphics()
	{
	}

	COORD ConGraphics::GetCursorPos()
	{
		// Get the original position of cursor
		CONSOLE_SCREEN_BUFFER_INFO sbInfo;
		GetConsoleScreenBufferInfo(hnd, &sbInfo);
		COORD c = { sbInfo.dwCursorPosition.X, sbInfo.dwCursorPosition.Y };

		return c;
	}

	void ConGraphics::Draw(LPENTITY obj)
	{
		using Zaxis::Graphics::ConGraphicsData::ConColor;
		using Zaxis::Graphics::ConGraphicsData::ConObject;

		LPVECTOR2D pos = obj->GetPosition2D();
		LPVECTOR2D oPos = obj->GetOldPosition2D();
		COORD c = { pos->x, pos->y };
		COORD oc = { oPos->x, oPos->y };
		COORD cPos = GetCursorPos();

		// Clear old position
		SetColor(hnd, ConColor::Grey);
		SetPos(oc);
		cout << field[oc.X][oc.Y];
		// Get object data from entity
		ConObject* ch = static_cast<ConObject*>(obj->GetMesh());
		// Set draw location and color attribute from object
		SetPos(c);
		SetColor(hnd, ch->color);
		// Finally draw the idiot to the screen
		cout << ch->c;

		// Check if we are logging this position
		if (obj->GetPosition2D() == _pos)
		{
			COORD dbPos = { 5, 20 };
			SetColor(hnd, ConColor::LtYellow);
			SetPos(dbPos);
			cout << _pos->ToString();
		}

		// Return Cursor to the original position
		SetColor(hnd, ConColor::Grey);
		SetPos(cPos);
	}

	void ConGraphics::Draw(LPOBJECT obj)
	{
		LPENTITY entity = static_cast<LPENTITY>(obj);
		if (entity != NULL)
		{
			Draw(entity);
		}else
		{
			LPVECTOR2D pos = obj->GetPosition2D();
			COORD c = { pos->x, pos->y };
			COORD cPos = GetCursorPos();

			// Now draw new location
			SetPos(c);
			cout << "*";
			// Return Cursor to the original position
			SetPos(cPos);
		}// Endif entity is not NULL
	}

	void ConGraphics::DrawRect(LPRECT2D rect, void* ch)
	{
		char bkg = '.';
		DrawRect(rect, ch, &bkg);
	}

	void ConGraphics::DrawRect(LPRECT2D rect, void* ch, void* bkg)
	{
		COORD cPos = GetCursorPos();
		char cDraw = *static_cast<char*>(ch);
		char cBkg = *static_cast<char*>(bkg);

		// Draw top and bottom line of rect
		COORD drawPos;
		int size = rect->Width;
		std::string line = std::string(size, cDraw);
		std::string line2 = std::string(size, cBkg);
		line2[0] = cDraw;
		line2[size - 1] = cDraw;

		drawPos.X = rect->X;
		drawPos.Y = rect->Y;
		SetPos(drawPos);
		cout << line;
		drawPos.Y = rect->Height + rect->Y;
		SetPos(drawPos);
		cout << line;
		for (int y = 1; y < rect->Height; y++)
		{
			drawPos.X = rect->X;
			drawPos.Y = y + rect->Y;
			SetPos(drawPos);
			cout << line2;
		}

		SetPos(cPos);
	}// End method DrawRect

	void ConGraphics::DrawRect(LPRECT2D rect, BoxType type)
	{
		COORD oc = GetCursorPos();

		std::string top;
		std::string bottom;
		std::string line;
		int end = rect->Width - 1;
		switch (type)
		{
		case BoxType::Single:
			{
				unsigned char tmp = 0xC4;
				top = std::string(rect->Width, tmp);
				bottom = std::string(rect->Width, tmp);
				tmp = 0x20;
				line = std::string(rect->Width, tmp);
				tmp = 0xB3;
				line[0] = line[end] = tmp;
				// Set box corners
				tmp = 0xDA;
				top[0] = tmp;
				tmp = 0xBF;
				top[end] = tmp;
				tmp = 192;
				bottom[0] = tmp;
				tmp = 217;
				bottom[end] = tmp;
			}
			break;
		case BoxType::Double:
			{
				unsigned char tmp = 205;
				top = std::string(rect->Width, tmp);
				bottom = std::string(rect->Width, tmp);
				tmp = 32;
				line = std::string(rect->Width, tmp);
				tmp = 201;
				top[0] = tmp;
				tmp = 187;
				top[end] = tmp;
				tmp = 200;
				bottom[0] = tmp;
				tmp = 188;
				bottom[end] = tmp;
				tmp = 186;
				line[0] = line[end] = tmp;
			}
			break;
		case BoxType::Antique:
			{
				int end = rect->Width - 1;
				unsigned char tmp = 223;
				top = std::string(rect->Width, tmp);
				tmp = 220;
				bottom = std::string(rect->Width, tmp);
				tmp = 219;
				bottom[0] = bottom[end] = top[end] = top[0] = tmp;
				line = std::string(rect->Width, 32);
				tmp = 221;
				line[0] = tmp;
				tmp = 222;
				line[end] = tmp;
			}
			break;
		case BoxType::Solid:
			{
				unsigned char tmp = 178;
				top = std::string(rect->Width, tmp);
				bottom = std::string(rect->Width, tmp);
				line = std::string(rect->Width, 32);
				line[0] = line[end] = tmp;
			}
			break;
		}

		COORD c = { rect->X, rect->Y };
		SetPos(c);
		cout << top;
		c.Y = rect->Y + rect->Height;
		SetPos(c);
		cout << bottom;
		for (int i = 1; i < rect->Height; i++)
		{
			c.Y = i + rect->Y;
			SetPos(c);
			cout << line;
		}
		SetPos(oc);
	}

	void ConGraphics::DrawFillRect(LPRECT2D rect, BoxType type, WORD color)
	{
		SetColor(hnd, color);
		DrawRect(rect, type);
		SetColor(hnd, ConColor::Grey);
	}

	void ConGraphics::DrawText(const std::string& line, LPVECTOR2D pos)
	{
		DrawText(line, pos->x, pos->y);
	}

	void ConGraphics::DrawText(const std::string& line, LPVECTOR2D pos, WORD color)
	{
		DrawText(line, pos->x, pos->y, color);
	}

	void ConGraphics::DrawText(const std::string& line, int x, int y)
	{
		COORD oPos = GetCursorPos();
		COORD pos = { x, y };
		SetPos(pos);
		cout << line;
		SetPos(oPos);
	}

	void ConGraphics::DrawText(const std::string& line, int x, int y, WORD color)
	{
		SetColor(hnd, color);
		DrawText(line, x, y);
		SetColor(hnd, ConColor::Grey);
	}

	void ConGraphics::DrawText(unsigned char c, int x, int y)
	{
		WORD clr = ConColor::Black | ConColor::Grey;
		DrawText(c, x, y, clr);
	}

	void ConGraphics::DrawText(unsigned char c, int x, int y, WORD color)
	{
		COORD oPos = GetCursorPos();
		COORD pos = { x, y };
		SetPos(pos);
		SetColor(hnd, color);
		cout << c;
		SetColor(hnd, ConColor::Black | ConColor::Grey);
		SetPos(oPos);
	}

	void ConGraphics::SetDebugPoint(LPVECTOR2D pos)
	{
		_pos = pos;
	}

	void ConGraphics::Update()
	{

	}

	void ConGraphics::Init()
	{
		UpdateField();
	}

	void ConGraphics::Dispose()
	{

	}

	void ConGraphics::UpdateField()
	{
		for (int x = 0; x < SIZE_X; x++)
		{
			for (int y = 0; y < SIZE_Y; y++)
			{
				COORD scPos = { x, y };
				CHAR buff;
				DWORD scRead;
				ReadConsoleOutputCharacterA(hnd, &buff, 1, scPos, &scRead);
				field[x][y] = buff;
			}
		}
	}

	void ConGraphics::SetConsoleSize(int width, int height)
	{
		COORD c = { width, height };
		SMALL_RECT size = { 0, 0, c.X-1, c.Y-1 };
		SetConsoleScreenBufferSize(hnd, c);
		SetConsoleWindowInfo(hnd, TRUE, &size);
	}

	void ConGraphics::SetConCursor(bool bVal)
	{
		if (bVal)
		{
			info.bVisible = TRUE;
		}
		else
		{
			info.bVisible = FALSE;
		}

		SetConsoleCursorInfo(hnd, &info);
	}

	void ConGraphics::SetPos(COORD c)
	{
		SetConPos(hnd, c);
	}

	void ConGraphics::SetPos(int x, int y)
	{
		COORD c = { x, y };
		SetPos(c);
	}

	void ConGraphics::SetCursorPos(int x, int y)
	{
		COORD c = { x, y };
		SetPos(c);
	}

	void ConGraphics::SetTextColor(int clr)
	{
		currentColor = clr;
		SetColor(hnd, clr);
	}

	void ConGraphics::Flush()
	{
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	}

	int ConGraphics::GetTextColor()
	{
		return currentColor;
	}

	void ConGraphics::SetPos(LPVECTOR2D pos)
	{
		COORD c = { pos->x, pos->y };
		SetPos(c);
	}

} }// End namespace Zaxis::Graphics

