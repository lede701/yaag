#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

#include "StrToHash.h"
#include "PlayerCreator.h"
#include "StringToChar.h"
#include "GameMessages.h"
#include "languagepack.h"

using namespace Game::Data;
using Zaxis::FileData;
using namespace std;

int PlayerCreate(ConGraphics* gfx, PlayerData* data, std::string* passwd)
{
	int retVal = 0;
	int y = 0;;
	std::string input;
	std::string name;
	std::string pw;
	FileData<PlayerData> plData(PLDBVER);
	std::string file = GetAppPath() + "\\players.dat";
	plData.Load(file);
	std::string msg;
	while (1)
	{
		// Show create message
		system("cls");
		y = ShowMessage(gfx, MessageType::MT_CREATEACCOUNT);
		if (msg.length() > 0)
		{
			gfx->DrawText(msg, 0, y++, ConColor::LtRed);
		}

		gfx->DrawText(PLAYERNAMEPROMPT, 0, y, ConColor::LtYellow);
		gfx->SetCursorPos(19, y++);
		input = GetInput(false);
		bool InUse = false;
		// Check if name is already being used
		plData.Front();
		name = input;
		transform(input.begin(), input.end(), input.begin(), ::toupper);
		int pos = plData.CurrentPos();
		do
		{
			std::string plName = plData.GetAt(pos).name;
			transform(plName.begin(), plName.end(), plName.begin(), ::toupper);
			if (input == plName)
			{
				InUse = true;
				msg =  ERROR_ACCOUNTEXISTS;
				break;
			}
			pos = plData.NextPos(pos);
		} while (pos != plData.Back().id);

		if (!InUse && input != GAMEQUIT)
		{
			// Store name in data structure
			std::string cpw;
			do
			{
				if (pw != cpw && pw.length() > 0)
				{
					gfx->DrawText(ERROR_CONFIRM, 5, y++, ConColor::LtRed);
				}
				gfx->DrawText(PASSWORDPROMPT, 0, y, ConColor::LtYellow);
				gfx->SetCursorPos(16, y++);
				pw = GetInput(true);
				if (pw == "QUIT" || pw == "quit")
				{
					return 0;
				}
				gfx->DrawText(CONFIRMPROMPT, 0, y, ConColor::LtYellow);
				gfx->SetCursorPos(18, y++);
				cpw = GetInput(true);
			} while (pw != cpw && pw.length() == 0);
			retVal = 1;
			break;
		}
		if (name == GAMEQUIT)
		{
			return 0;
		}
	}

	// Check if we need to pass the password back to calling routine.
	if (passwd != NULL)
	{
		(*passwd) = pw;
	}

	// Save player data
	pw = StrToHash(pw);
	CreatePlayer(name, pw, data);
	gfx->DrawText(CREATEDSUCCESS, 0, y++, ConColor::LtYellow);

	return retVal;
}

bool CreatePlayer(PlayerData* data)
{
	data->id = 0;
	data->armorId = 1;
	data->weaponId = 1;

	data->level.Level = 1;
	data->level.Experience = 0;
	data->level.NextLevelExp = 500;
	data->level.PrevLevelExp = 0;
	data->level.Gold = 15;
	data->level.AssignedPoints = 0;

	data->character.Speed = 4;
	data->character.Move = 0;
	data->character.NextMove = 0;

	data->character.Str = 2;
	data->character.Dex = 2;
	data->character.Con = 5;
	data->character.Int = 1;
	data->character.Health = 10;
	data->character.MaxHealth = 10;
	data->character.Mana = 5;
	data->character.MaxMana = 5;
	data->character.ManaRegen = 1;
	data->character.ManaRegenSpeed = 25;
	data->character.NextMana = 0;
	data->character.HealingAmount = 0;
	data->character.HealingSpeed = 1;
	data->character.NextHealing = 0;
	data->character.AttackDamage = 1;
	data->character.AttackRating = 1;
	data->character.AttackSpeed = 15;
	data->character.NextAttack = 0;
	data->character.DefenseRating = 1;
	data->Wins = 0;
	data->Losses = 0;
	data->Deaths = 0;
	return true;
}

bool CreatePlayer(const std::string& name, PlayerData* data)
{
	PlayerData pl;
	bool bRetVal = CreatePlayer(&pl);
	StringToChar(30, pl.name, name);
	// Store data in player object
	(*data) = pl;
	return bRetVal;
}

bool CreatePlayer(const std::string& name, const std::string& pw, PlayerData* data)
{
	bool bRetVal = false;

	FileData<PlayerData> plData(PLDBVER);
	std::string file = GetAppPath() + "\\players.dat";
	if (FileExists(file))
	{
		plData.Load(file);
	}

	PlayerData pl;
	CreatePlayer(&pl);
	StringToChar(30, pl.name, name);
	StringToChar(65, pl.passwd, pw);

	pl.id = plData.GetNextId();;
	plData.Load(file);
	plData.Add(pl);
	bRetVal = plData.Save(file);

	// Set data to player object provided
	(*data) = pl;

	return bRetVal;
}

bool CreateAdminPlayer(const std::string& name, const std::string& pw, PlayerData* data)
{
	bool bRetVal = true;

	PlayerData pl;
	StringToChar(30, pl.name, name);
	StringToChar(65, pl.passwd, pw);
	pl.id = 0;
	pl.armorId = 23;
	pl.weaponId = 52;

	pl.level.Level = 1;
	pl.level.Experience = 0;
	pl.level.NextLevelExp = 500;
	pl.level.PrevLevelExp = 0;
	pl.level.Gold = 15;
	pl.level.AssignedPoints = 0;

	pl.character.Speed = 100;
	pl.character.Move = 0;
	pl.character.NextMove = 0;

	pl.character.Str = 5;
	pl.character.Dex = 5;
	pl.character.Con = 5;
	pl.character.Int = 5;
	pl.character.Health = 500;
	pl.character.MaxHealth = 500;
	pl.character.Mana = 5;
	pl.character.MaxMana = 5;
	pl.character.ManaRegen = 1;
	pl.character.ManaRegenSpeed = 25;
	pl.character.NextMana = 0;
	pl.character.HealingAmount = 0;
	pl.character.HealingSpeed = 30;
	pl.character.NextHealing = 0;
	pl.character.AttackDamage = 1;
	pl.character.AttackRating = 1;
	pl.character.AttackSpeed = 15;
	pl.character.NextAttack = 0;
	pl.character.DefenseRating = 100;
	pl.Wins = 0;
	pl.Losses = 0;
	pl.Deaths = 0;

	// Set data to player object provided
	(*data) = pl;

	return bRetVal;
}