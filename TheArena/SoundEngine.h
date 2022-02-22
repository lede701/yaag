#ifndef H_SOUNDENGINE
#define H_SOUNDENGINE

#define LPSOUND Zaxis::Engines::SoundEngine*
#define MAX_QUEUE 24

#include <sstream>
#include <stdlib.h>
#include "ISound.h"

#define LPSOUNDENGINE Zaxis::Engines::SoundEngine*

// TODO: Need to create a sound interface

namespace Zaxis{ namespace Engines
{
	struct SoundNode
	{
	public:
		SoundNode(int iId, float iVol){ Id = iId; vol = iVol; }
		int Id;
		float vol;
	};

	class SoundEngine :
		public Zaxis::Sound::ISound
	{
	private:
		SoundNode *QueueSounds[MAX_QUEUE];
		int head;
		int tail;

		bool _isRunning;

		LPLOGGER _log;
	public:
		SoundEngine();
		virtual  ~SoundEngine();

		virtual bool PlaySound(int Id, float vol);
		virtual LPENGINE SetLog(LPLOGGER log);
		virtual LPLOGGER Log();
		virtual LPLOGGER WriteLine(std::string line);

		virtual void Update();
		virtual bool IsRunning();
		virtual int RunEngine();
	};

} }//End namespace Zaxis::Engines
#endif