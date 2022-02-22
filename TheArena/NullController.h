#ifndef H_NULLCONTROLLER
#define H_NULLCONTROLLER

#include "IController.h"

namespace Zaxis{ namespace Controllers
{

	class NullController :
		public IController
	{
	public:
		NullController();
		virtual ~NullController();

		virtual bool ChkInput(int vk);
		virtual char GetInput();
		virtual void Update();
	};

} }// End namespace Zaxis::Controllers

#endif