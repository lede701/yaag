#ifndef H_ISTATEMANAGER
#define H_ISTATEMANAGER

#define LPSTATEMANAGER Zaxis::Controllers::IStateManager*

namespace Zaxis{ namespace Controllers
{
	class IStateManager
	{
	public:
		IStateManager();
		virtual ~IStateManager();

		virtual int Count() = 0;
		virtual void PopState() = 0;
		virtual void FlushStates() = 0;
	};
} }// End namespace Zaxis::Controllers

#endif