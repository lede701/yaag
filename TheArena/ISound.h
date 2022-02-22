#ifndef H_ISOUND
#define H_ISOUND

#include <string>

#include "IEngine.h"
#include "ILogger.h"

#define LPENGSOUND Zaxis::Sound::ISound*

namespace Zaxis{ namespace Sound
{

	class ISound :
		 public Zaxis::Engine::IEngine
	{
	public:
		ISound();
		virtual ~ISound();

		virtual bool PlaySound(int Id, float vol) = 0;
		virtual LPENGINE SetLog(LPLOGGER log) = 0;
		virtual LPLOGGER Log() = 0;
		virtual LPLOGGER WriteLine(std::string line) = 0;
	};

} }// End namespace Zaxis::Sound

#endif