#include "GetInput.h"

std::string GetInput(bool IsMasked)
{
	using std::cout;

	// Clear rhe buffer

	const char BACKSPACE = 8;
	const char RETURN = 13;
	const char TAB = 9;
	std::string txt;
	char ch;

	while (1)
	{
		ch = _getch();
		if (ch == RETURN || ch == TAB)
		{
			break;
		}

		if (ch == BACKSPACE)
		{
			if (txt.length() > 0)
			{
				std::cout << "\b \b";
				txt.resize(txt.length() - 1);
			}
		}
		else
		{
			txt += ch;
			if (IsMasked)
			{
				std::cout << "*";
			}
			else
			{
				std::cout << ch;
			}
		}
	}

	return txt;
}
