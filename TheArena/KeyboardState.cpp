#include "KeyboardState.h"
#include <stdio.h>

namespace Zaxis{ namespace Controllers
{

	KeyboardState::KeyboardState()
	{
		for (int i = 0; i < MAX_KEYVALUE; i++)
			keys[i] = false;
	}

} }// End namespace Zaxis::Controllers