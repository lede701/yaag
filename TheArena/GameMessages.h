#ifndef H_SHOWMESSAGE
#define H_SHOWMESSAGE

#include "ConGraphics.h"
#include <string>
#include <iostream>
#include <sstream>

enum MessageType
{
	MT_LOGIN,
	MT_CREATEACCOUNT,
	MT_HELLO,
	MT_LOGINHELP
};

using Zaxis::Graphics::ConColor;
using Zaxis::Graphics::ConGraphics;

int ShowMessage(ConGraphics* gfx, MessageType type);

#endif
// 12345678901234567890123456789012345678901234567890123456789012345678901234567890
// 
// 
// 
// Player Name: 