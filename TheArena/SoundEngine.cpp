#include "SoundEngine.h"

namespace Zaxis{ namespace Engines
{

	SoundEngine::SoundEngine()
	{
		for (int i = 0; i < MAX_QUEUE; i++)
		{
			QueueSounds[i] = NULL;
		}

		tail = 0;
		head = 0;
		_isRunning = false;
		_log = NULL;
	}


	SoundEngine::~SoundEngine()
	{
		delete[] *QueueSounds;
	}

	bool SoundEngine::PlaySound(int Id, float vol)
	{
		bool bRetVal = false;
		if ((tail + 1) % MAX_QUEUE != head)
		{
			bRetVal = true;
			QueueSounds[tail] = new SoundNode(Id, vol);
			std::ostringstream out;
			// Log we have added something to the queue
			out << "Added " << Id << " to sound queue";
			WriteLine(out.str());
			tail = (tail + 1) % MAX_QUEUE;
		}

		return bRetVal;
	}

	void SoundEngine::Update()
	{
		while (head != tail)
		{
			SoundNode* node = QueueSounds[head];
			if (node != NULL)
			{
				// TODO: Load sound and play it
				std::ostringstream out;
				out << "Playing sound " << node->Id;
				WriteLine(out.str());
			}
			// Clear queue item
			QueueSounds[head] = NULL;
			head = (head + 1) % MAX_QUEUE;
		}
	}

	int SoundEngine::RunEngine()
	{
		// TODO: We need a way to communicate with the main engine before we can run this as a separate thread

		return 0;
	}

	bool SoundEngine::IsRunning()
	{
		return _isRunning;
	}

	LPENGINE SoundEngine::SetLog(LPLOGGER log)
	{
		_log = log;
		return this;
	}

	LPLOGGER SoundEngine::Log()
	{
		return _log;
	}

	LPLOGGER SoundEngine::WriteLine(std::string line)
	{
		if (Log() != NULL)
		{
			Log()->WriteLine(line);
		}

		return Log();
	}

} }//End namespace Zaxis::Engines

