#ifndef H_NULLSOUND
#define H_NULLSOUND

#include "ISound.h"

namespace Zaxis{ namespace Sound
{

	class NullSound :
		public ISound
	{
	private:
		LPLOGGER _log;

		bool _isRunning;
	public:
		NullSound();
		~NullSound();

		virtual bool PlaySound(int Id, float vol);
		virtual LPENGINE SetLog(LPLOGGER log);
		virtual LPLOGGER Log();
		virtual LPLOGGER WriteLine(std::string line);

		virtual void Update();
		virtual int RunEngine();
		virtual bool IsRunning();
	};

} }// End namespace Zaxis::Sound

#endif;