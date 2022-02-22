#ifndef H_IENGINE
#define H_IENGINE

#define LPENGINE Zaxis::Engine::IEngine*

namespace Zaxis{ namespace Engine
{

	class IEngine
	{
	public:
		IEngine();
		virtual ~IEngine();

		virtual void Update() = 0;
		virtual int RunEngine() = 0;
		virtual bool IsRunning() = 0;
	};

} }// End namespace Zaxis::Engine

#endif