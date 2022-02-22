#include "NullSound.h"

namespace Zaxis{ namespace Sound
{

	NullSound::NullSound()
	{
		_isRunning = true;
	}


	NullSound::~NullSound()
	{
	}

	bool NullSound::PlaySound(int Id, float vol)
	{
		return true;
	}

	LPENGINE NullSound::SetLog(LPLOGGER log)
	{
		_log = log;
		return this;
	}

	LPLOGGER NullSound::Log()
	{
		return _log;
	}

	LPLOGGER NullSound::WriteLine(std::string line)
	{
		Log()->WriteLine(line);
		return Log();
	}

	void NullSound::Update()
	{

	}

	int NullSound::RunEngine()
	{
		// TODO: Build communication between engines so the main game engine can shut down this engine
		return 0;
	}

	bool NullSound::IsRunning()
	{
		return _isRunning;
	}

} }// End namespace Zaxis::Sound

