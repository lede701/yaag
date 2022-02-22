#include "FileData.h"
#include "ConGraphics.h"
#include "PlayerData.h"
#include "FileIO.h"
#include "GetInput.h"

using namespace Game::Data;
using Zaxis::FileData;
using namespace std;
using Zaxis::Graphics::ConGraphics;

#ifndef H_PLAYERCREATOR
#define H_PLAYERCREATOR

int PlayerCreate(ConGraphics* gfx, PlayerData* data, std::string* passwd=NULL);
bool CreatePlayer(PlayerData* data);
bool CreatePlayer(const std::string& name, PlayerData* data);
bool CreatePlayer(const std::string& name, const std::string& pw, PlayerData* data);
bool CreateAdminPlayer(const std::string& name, const std::string& pw, PlayerData* data);

#endif