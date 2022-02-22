#include "GameMessages.h"
#include "languagepack.h"

int ShowMessage(ConGraphics* gfx, MessageType type)
{
	int line = 0;

	std::ostringstream out;
	WORD color = ConColor::White;

	switch (type)
	{
	case MessageType::MT_HELLO:
	{
		std::istringstream sin(NEWWELCOME);
		while (!sin.eof())
		{
			std::string txt;
			char buff[80];
			sin.getline(buff, 79, '\n');
			out << buff;
			gfx->DrawText(out.str(), 1, line++, color);
		}
		line++;
	}
	break;
	case MessageType::MT_LOGIN:
	{
		std::istringstream sin(LOGINMSG);
		while (!sin.eof())
		{
			std::string txt;
			char buff[80];
			sin.getline(buff, 79, '\n');
			out << buff;
			gfx->DrawText(out.str(), 1, line++, color);
			out.str(""); out.clear();
		}
		line++;
	}
	break;
	case MessageType::MT_CREATEACCOUNT:
	{
		std::istringstream sin(CREAETACCOUNT);
		while (!sin.eof())
		{
			std::string txt;
			char buff[80];
			sin.getline(buff, 79, '\n');
			out << buff;
			gfx->DrawText(out.str(), 1, line++, color);
			out.str(""); out.clear();
		}
		line++;
	}
	break;
	case MessageType::MT_LOGINHELP:
	{
		std::istringstream sin(LOGINHELP);

		while (!sin.eof())
		{
			std::string txt;
			char buff[80];
			sin.getline(buff, 79, '\n');
			out << buff;
			gfx->DrawText(out.str(), 1, line++, color);
			out.str(""); out.clear();
		}
		line++;
	}
	break;
	}

	return line;
}
