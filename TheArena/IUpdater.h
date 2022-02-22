#ifndef H_UPDATER
#define H_UPDATER

#define LPUPDATER Zaxis::Engine::IUpdater*

namespace Zaxis{ namespace Engine
{

	class IUpdater
	{
	public:
		IUpdater()
		{

		}
		virtual ~IUpdater()
		{

		}

		virtual void Update() = 0;
		virtual bool Shutdown() = 0;
	};

} }

#endif