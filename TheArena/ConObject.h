#ifndef H_CONOBJECT
#define H_CONOBJECT

#define LPCONOBJECT Zaxis::Graphics::ConGraphics::ConObject*

#include "ConColor.h"
#include <Windows.h>

namespace Zaxis{ namespace Graphics{ namespace ConGraphicsData
{

	struct ConObject
	{
	public:
		unsigned char c;
		WORD color;
	};

} } }// End namespace Zaxis::Graphics::ConGraphics

#endif