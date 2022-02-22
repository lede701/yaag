#ifndef H_KEYBOARDSTATE
#define H_KEYBOARDSTATE

#define MAX_KEYVALUE 256

namespace Zaxis{ namespace Controllers
{
	struct KeyboardState
	{
	public:
		bool keys[MAX_KEYVALUE];

		KeyboardState();
	};
} }// End namespace Zaxis::Controllers

#endif