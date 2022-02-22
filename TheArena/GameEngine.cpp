#include "GameEngine.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include <ctime>
#include <chrono>
#include <thread>


namespace Zaxis{ namespace Engines
{

	GameEngine::GameEngine()
	{
		Init();
	}

	GameEngine::GameEngine(LPLOGGER log)
	{
		Init();
		// Delete the default Null Logger
		delete _log;
		_log = log;
	}

	void GameEngine::Init()
	{
		// Initialize game engine
		_isRunning = true;
		// Create default logger so we don't have to check for NULL
		_log = new Zaxis::Logging::NullLogger();
		_graphics = new Zaxis::Graphics::NullGraphics();
		_sound = new Zaxis::Sound::NullSound();
		_gameController = new Zaxis::Controllers::NullController();
		for (int i = 0; i < PRIORITYLISTSIZE; i++)
		{
			updaterList[i].clear();
		}
		NextObjId = 0;
		oFront = oBack = 0;
		sFront = sBack = 0;
		for (int i = 0; i < MAX_OBJECTS; i++)
		{
			objectArray[i] = NULL;
			sleepArray[i] = NULL;
		}

		// Set the default pause state
		_pause = false;
	}

	GameEngine::~GameEngine()
	{
		if (_graphics != NULL)
		{
			delete _graphics;
			_graphics = NULL;
		}
		if (_sound != NULL)
		{
			delete _sound;
			_sound = NULL;
		}
		if (_gameController != NULL)
		{
			delete _gameController;
			_gameController = NULL;
		}

		// TODO: Perform cleanup on all updaters
		for (int i = 0; i < PRIORITYLISTSIZE; i++)
		{
			while (updaterList[i].size() != 0 && false)
			{

			}
		}

		for (int i = 0; i < MAX_OBJECTS; i++)
		{
			if (objectArray[i] != NULL)
			{
				delete objectArray[i];
				objectArray[i] = NULL;
			}
			if (sleepArray[i] != NULL)
			{
				delete sleepArray[i];
				sleepArray[i] = NULL;
			}
		}
	}

	bool GameEngine::IsRunning()
	{
		return _isRunning;
	}

	int GameEngine::RunEngine()
	{
		// Setup time tracking data
		using std::clock_t;
		using std::queue;

		// Set the render frame rate
		short fps = 0;
		short loopCnt = 0;
		double time;
		double elapsed = clock();
		// Current position in Array
		unsigned int pos = 0;

		// Calculate the time for each frame based on frame rate
		static int MS_PER_FRAME = CLOCKS_PER_SEC / FRAME_RATE;
		
		// Player the startup sound
		if (Sound() != NULL)
		{
			Sound()->PlaySound(1, 0.5f);
		}
		// Startup the graphics engine
		Graphics()->Init();
		// Track graphics being draw each frame
		bool bGfxDrawn = true;
		do 
		{
			// Set time to current clock
			time = clock();
			PreUpdate();
			// Update engine
			if (bGfxDrawn || _pause)
			{
				Update();
			}
			// Create a output string stream
			ostringstream out;
			// Update number of processed loops
			loopCnt = (loopCnt + 1) % 32000;
			// Check if the [ESC] is pressed
			if (GameController()->ChkInput(VK_ESCAPE))
			{
				// Quit game
				_isRunning = false;
				continue;
			}

			// Calculate sleep time
			int sleepTime = static_cast<int>(time + MS_PER_FRAME - clock());
			// Make sure we have a real time to sleep
			if ((sleepTime > 0 || !bGfxDrawn) && !_pause)
			{
				// Start the draw frame process
				pos = oFront;
				while (pos != oBack)
				{
					// Draw each active game object
					Graphics()->Draw(objectArray[pos]);
					pos = NextObjectPos(pos);
				}
				// Make sure the engine knows the drawing routine finished
				bGfxDrawn = true;

				// Draw sleeping objects
				pos = sFront;
				while (pos != sBack)
				{
					// Draw each sleeping object
					Graphics()->Draw(sleepArray[pos]);
					pos = NextObjectPos(pos);
				}

				// Increment the Frame Per Second calculation and make sure it doesn't go out of range for data type short
				fps = (fps + 1) % 32000;

				// Recalculate the sleep time
				sleepTime = static_cast<int>(time + MS_PER_FRAME - clock());

				// TODO: Move this to its own thread
				if (sleepTime > 0)
				{
					Sound()->Update();
				}

				sleepTime = static_cast<int>(time + MS_PER_FRAME - clock());
				// Finally we can sleep
				if (sleepTime > 0)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
				}
			}
			else
			{
				// Set this to false so we can see if gfx gets skipped
				bGfxDrawn = false;
			}
			// Perform state manager tasks
			for (list<LPSTATEMANAGER>::iterator it = stateList.begin(); it != stateList.end(); it++)
			{
				(*it)->PopState();
			}
#ifdef _DEBUG
			// Track FPS for debug builds
			if (clock() - elapsed > 1000)
			{
				ostringstream out;
				out << "FPS: " << fps << ":" << loopCnt << "   ";
				elapsed = clock();
				fps = 0;
				loopCnt = 0;
				//Graphics()->DrawText(out.str(), 5, 36);
			}
#endif

		} while (IsRunning());

		return 0;
	}

	unsigned int GameEngine::NextObjectPos(unsigned int pos)
	{
		// Return the next object position
		return (pos + 1) % MAX_OBJECTS;
	}

	unsigned int GameEngine::PrevObjectPos(unsigned int pos)
	{
		// Return the previous object position
		int ppos = (pos - 1) % MAX_OBJECTS;
		if (ppos < 0) ppos = MAX_OBJECTS;
		return ppos;
	}

	LPOBJECT GameEngine::AddObject(LPOBJECT obj, bool AddLogger)
	{
		// Check if there is a logger to add to object
		if (_log != NULL && AddLogger)
		{
			obj->SetLogger(_log);
		}// Endif log is valid and AddLogger is true

		// Set object id
		obj->SetId(GetObjectId());
		// Add object to active game object list
		if (NextObjectPos(oBack) != oFront)
		{
			objectArray[oBack] = obj;
			oBack = NextObjectPos(oBack);
		}
		//oList.push_back(obj);
		return obj;
	}

	LPENTITY GameEngine::AddEntity(LPENTITY obj, bool AddLogger)
	{
		// Check if there is a logger to add to entity
		if (_log != NULL && AddLogger)
		{
			obj->SetLogger(_log);
		}// Endif log is valid and AddLogger is true
		if (_sound != NULL)
		{
			//obj->SetSound(_sound);
		}

		// Set object id
		obj->SetId(GetObjectId());
		// Add object to active game list
		//*
		if (NextObjectPos(oBack) != oFront)
		{
			objectArray[oBack] = obj;
			oBack = NextObjectPos(oBack);
		}
		//*/
		//oList.push_back(obj);

		return obj;
	}

	bool GameEngine::RmEntity(LPENTITY entity)
	{
		bool bRetVal = false;
		int pos = oFront;
		while (pos != oBack)
		{
			if (objectArray[pos] != NULL)
			{
				if (objectArray[pos]->GetId() == entity->GetId())
				{
					//entity->ClearMesh(_graphics);
					objectArray[pos] = NULL;
					bRetVal = true;
				}
			}
			// Try and compact active objects
			if (objectArray[pos] == NULL)
			{
				objectArray[pos] = objectArray[NextObjectPos(pos)];
				oBack = PrevObjectPos(oBack);
			}
			else
			{
				pos = NextObjectPos(pos);
			}
		}

		return bRetVal;
	}

	void GameEngine::RmAll()
	{
		bool bRetVal = false;
		for (int i = 0; i < MAX_OBJECTS; i++)
		{
			objectArray[i] = NULL;
		}

		// Reset the front and back.
		oFront = oBack = 0;
	}

	LPGAME GameEngine::AddUpdater(LPUPDATER uper)
	{
		return AddUpdater(uper, 2);
	}

	LPGAME GameEngine::AddUpdater(LPUPDATER uper, int priority)
	{
		if (priority >= 0 && priority < PRIORITYLISTSIZE)
		{
			// Add updater to the list to process on my update loop
			updaterList[priority].push_back(uper);
		}

		// Return me
		return this;
	}

	LPGAME GameEngine::AddStater(LPSTATEMANAGER stater)
	{
		// Add state manager to the list
		stateList.push_back(stater);
		return this;
	}

	int GameEngine::GetObjectId()
	{
		// Calculate a safe number for our next ID
		NextObjId = (NextObjId + 1) % 2000000;
		return NextObjId;
	}

	LPGAME GameEngine::SetLog(LPLOGGER inLog)
	{
		// Set engine log system
		_log = inLog;
		return this;
	}

	LPLOGGER GameEngine::Log(std::string line)
	{
		// Write line to log engine
		_log->WriteLine(line);

		// Return my log engine
		return _log;
	}

	LPGAME GameEngine::SetGraphics(LPGRAPHICS inGraphics)
	{
		// Set the graphics engine
		_graphics = inGraphics;
		return this;
	}

	LPGRAPHICS GameEngine::Graphics()
	{
		// Return my graphics engine
		return _graphics;
	}

	LPGAME GameEngine::SetSound(LPENGSOUND inSound)
	{
		// Set my sound engine
		_sound = inSound;
		_sound->SetLog(_log);

		// Return me
		return this;
	}

	LPENGSOUND GameEngine::Sound()
	{
		// Get my sound engine
		return _sound;
	}

	void GameEngine::Update()
	{
		using std::queue;
		// Create transfer queue for game objects
		queue<LPOBJECT> tranObjects;
		if (!_pause)
		{
			// Update game objects
			unsigned int pos = oFront;
			while (pos != oBack)
			{
				if (objectArray[pos] == NULL)
				{
					break;
				}
				// Check if the object is sleeping
				if (objectArray[pos]->IsAsleep())
				{
					// Move to the sleep 
					tranObjects.push(objectArray[pos]);
					objectArray[pos] = new Zaxis::Core::NullObject();
				}
				else
				{
					// Update game object
					objectArray[pos]->Update();
				}
				// Change position index
				pos = (pos + 1) % MAX_OBJECTS;
			}

			// Transition active objects to sleeping objects
			while (tranObjects.size() > 0)
			{
				// Get front element of sleeping object
				LPOBJECT obj = tranObjects.front();
				tranObjects.pop();
				sleepArray[sBack] = obj;
				sBack = NextObjectPos(sBack);
				// Tell the object it is going to sleep
				obj->GoingToSleep();
			}
		}// Endif not _pause

		// Run each updater item
		for (list<LPUPDATER>::iterator up = updaterList[NORMALUPDATE].begin(); up != updaterList[NORMALUPDATE].end(); up++)
		{
			(*up)->Update();
			if ((*up)->Shutdown())
			{
				_isRunning = false;
				break;
			}
		}
	}

	void GameEngine::PreUpdate()
	{
		// Run each updater item
		for (list<LPUPDATER>::iterator up = updaterList[BEFOREUPDATE].begin(); up != updaterList[BEFOREUPDATE].end(); up++)
		{
			(*up)->Update();
			if ((*up)->Shutdown())
			{
				_isRunning = false;
				break;
			}
		}
	}

	LPGAME GameEngine::SetController(LPCONTROLLER ctrl)
	{
		if (_gameController != NULL)
		{
			delete _gameController;
			_gameController = NULL;
		}
		_gameController = ctrl;

		return this;
	}

	LPCONTROLLER GameEngine::GameController()
	{
		return _gameController;
	}

	void GameEngine::Pause(bool pause)
	{
		_pause = pause;
	}

} }// End namespace Zaxis::Engines