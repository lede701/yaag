#ifndef H_GAMEENGINE
#define H_GAMEENGINE

#include <iostream>
#include <sstream>
#include <list>
#include <queue>
#include <string>

#include "NullDevices.h"
#include "Object.h"
#include "IEntity.h"
#include "IEngine.h"
#include "ILogger.h"
#include "IGraphics.h"
#include "ISound.h"
#include "IUpdater.h"
#include "IEntityToEngine.h"
#include "IStateManager.h"


// Other engines to help manage the game

#define LPGAME Zaxis::Engines::GameEngine*
#define MAX_OBJECTS 16
#define PRIORITYLISTSIZE 3
#define NORMALUPDATE 2
#define BEFOREUPDATE 0

#ifndef FRAME_RATE
#define FRAME_RATE 25
#endif

namespace Zaxis{ namespace Engines
{
	using std::list;
	using std::ostringstream;

	class GameEngine :
		 public Zaxis::Engine::IEngine, public IEntityToEngine
	{
	private:
		bool _isRunning;
		bool _pause;

		LPOBJECT objectArray[MAX_OBJECTS];
		unsigned int oFront;
		unsigned int oBack;

		LPOBJECT sleepArray[MAX_OBJECTS];
		unsigned int sFront;
		unsigned int sBack;

		list<LPUPDATER> updaterList[PRIORITYLISTSIZE];
		list<LPSTATEMANAGER> stateList;


		LPLOGGER _log;
		int NextObjId;
		LPGRAPHICS _graphics;
		LPENGSOUND _sound;

		LPCONTROLLER _gameController;

		void Init();
		int GetObjectId();
		unsigned int NextObjectPos(unsigned int pos);
		unsigned int PrevObjectPos(unsigned int pos);

	public:
		GameEngine();
		GameEngine(LPLOGGER log);
		~GameEngine();

		bool IsRunning();

		int RunEngine(void);
		LPOBJECT AddObject(LPOBJECT obj, bool AddLogger = true);
		virtual LPENTITY AddEntity(LPENTITY obj, bool AddLogger = true);
		virtual bool RmEntity(LPENTITY obj);
		virtual void RmAll();

		LPGAME AddUpdater(LPUPDATER updater);
		LPGAME AddUpdater(LPUPDATER updater, int priority);
		LPGAME AddStater(LPSTATEMANAGER stater);

		LPGAME SetGraphics(LPGRAPHICS inGraphics);
		LPGRAPHICS Graphics();

		LPGAME SetSound(LPENGSOUND inSound);
		LPENGSOUND Sound();

		LPGAME SetLog(LPLOGGER inLog);
		LPLOGGER Log(std::string line);

		LPGAME SetController(LPCONTROLLER ctrl);
		LPCONTROLLER GameController();

		virtual void PreUpdate();
		virtual void Update();
		virtual void Pause(bool pause);
	};

} }// End namespace Zaxis::Engines

#endif