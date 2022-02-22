#include "stdlib.h"
#include "../TheArena/MonsterEnum.h"
#include "../TheArena/MovementData.h"
#include "../TheArena/MonsterData.h"
#include "../TheArena/ConColor.h"
#include "../TheArena/PlayerEntity.h"
#include "../TheArena/WeaponData.h"
#include "../TheArena/PlayerHelper.h"
#include "../TheArena/PlayerHelper.cpp"
#include "../TheArena/ArmorData.h"
#include "../TheArena/FileData.h"
#include "../TheArena/FileIO.h"
#include "../TheArena/FileIO.cpp"

#include <iostream>
#include <sstream>

#pragma comment(lib, "../x64/Debug/TheArena.lib")

#ifndef UINT
#define UINT unsigned int
#endif
#ifndef UCHAR
#define UCHAR unsigned char
#endif

#define THEADMIN "Admin"
#define THEPASSWD "@Dm!n2015"

#define DEV_USER "zaxisstudios"
#define DEV_PW "pooky5today"


using namespace Game::Monsters::Entities;
using Zaxis::Graphics::ConGraphicsData::ConColor;
using namespace Game::Data;
using Zaxis::FileData;
using Game::Data::ArmorData;
using Game::Entity::Monsters::AI::AI_Type;

void StringToChar(int maxsize, unsigned char *c_str, const std::string& str);
void StringToChar(int maxsize, char *c_str, const std::string& str);

/// Converters
MonsterType StrToMonType(const std::string& type);
AI_Type StrToAI(const std::string& type);
ItemList StrToItem(const std::string& type);
ItemMaterial StrToMaterial(const std::string& type);
ConColor StrToColor(const std::string& clr);

// Monster overloads
void WriteData(UINT id, MonsterType type, AI_Type AI, const std::string& name, UINT speed, UINT damage, UINT minDamage, UINT health, UINT attackSpeed, UINT defense, UINT level, UINT weaponId, WORD color, WORD hitColor, UCHAR mesh);
void ReadData(MonsterData* m);

// Weapon Overloads
void WriteData(UINT id, ItemList type, ItemMaterial materail, UINT damage, UINT plus, UINT range, UINT price, UINT sellPrice, const std::string& name);
void ReadData(WeaponData* w);
void ReadData(int idx, WeaponData* w);

// Armor overloads
void WriteData(int id, ItemList type, ItemMaterial mat, UINT def, int plus, UINT price, UINT sellPrice, const std::string& name);

void CreateMonsters(const std::string& file, const std::string& srcFile);
void CreateWeapons(const std::string& file, const std::string& srcFile);
void CreateArmor(const std::string& file, const std::string& srcFile);
void CreateAdminPlayer(const std::string& file);

// Define file version
#define VER 3

// File data structures
FileData<MonsterData> mData(VER);
FileData<PlayerData> plData(VER);
FileData<WeaponData> wData(VER);
FileData<ArmorData> arData(VER);

int main(int argv, char *argc[])
{
	std::string wFile = GetAppPath() + "\\weapons.dat";
	std::string mFile = GetAppPath() + "\\monster.dat";
	std::string aFile = GetAppPath() + "\\armor.dat";
	std::string plFile = GetAppPath() + "\\players.dat";

	std::string wSrcFile = GetAppPath() + "\\WeaponsDataSheet.csv";
	std::string mSrcFile = GetAppPath() + "\\MonstersDataSheet.csv";
	std::string aSrcFile = GetAppPath() + "\\ArmorDataSheet.csv";

	CreateMonsters(mFile, mSrcFile);
	CreateWeapons(wFile, wSrcFile);
	CreateArmor(aFile, aSrcFile);

	mData.Load(mFile);
	cout << "Monsters in Database: " << mData.Count() << endl;
	wData.Load(wFile);
	cout << "Weapons in Database: " << wData.Count() << endl;
	arData.Load(aFile);
	cout << "Armor in database: " << arData.Count() << endl;

	system("PAUSE");
	return 0;
}

void WriteData(MonsterData* m)
{
	mData.Add(*m);
}

void ReadData(MonsterData* m)
{
	m = &mData.GetAt(mData.NextPos());
}

//////////////////////////////////////////////////////////////////////////
// Write monster data
//////////////////////////////////////////////////////////////////////////
void WriteData(UINT id, MonsterType type, AI_Type AI, const std::string& name, UINT speed, UINT damage, UINT minDamage, UINT health, UINT attackSpeed, UINT defense, UINT level, UINT weaponId, UINT armorId, WORD color, WORD hitColor, UCHAR mesh)
{
	MonsterData data;
	data.id = id;
	data.type = type;
	data.AI = AI;
	for (unsigned int i = 0; i <= name.length(); i++){ data.name[i] = name[i]; }
	data.character.Speed = speed;
	data.character.Move = data.character.NextMove = 0;
	data.level = level;
	data.weaponId = weaponId;
	data.armorId = armorId;
	data.color = color;
	data.hitColor = hitColor;
	data.mesh = mesh;

	data.character.AttackDamage = damage;
	data.character.AttackMinDamage = minDamage;
	data.character.AttackSpeed = attackSpeed;
	data.character.NextAttack = 0;

	data.character.Speed = speed;

	data.character.DefenseRating = defense;
	data.character.Health = health;
	data.character.MaxHealth = health;

	mData.Add(data);
}

void ReadData(WeaponData* w)
{
	w = &wData.GetAt(wData.NextPos());
}

void ReadData(int idx, WeaponData* w)
{
	w = &wData.GetAt(idx-1);
}

//////////////////////////////////////////////////////////////////////////
// Write weapon data
//////////////////////////////////////////////////////////////////////////
void WriteData(UINT Id, ItemList type, ItemMaterial materail, UINT damage, UINT plus, UINT range, UINT price, UINT sellPrice, const std::string& name)
{
	// Create new weapon object
	WeaponData data;
	data.Id = Id;
	data.type = type;
	data.material = materail;
	data.damage = damage;
	data.plus = plus;
	data.range = range;
	data.price = price;
	data.sellPrice = sellPrice;
	StringToChar(38, data.name, name);

	data.character.AttackDamage = damage;
	data.character.AttackBonus = plus;
	
	// Write object to data file
	wData.Add(data);
}

void CreateMonsters(const std::string& file, const std::string& srcFile)
{
	// http://en.wikipedia.org/wiki/List_of_legendary_creatures_%28E%29
	//***  MONSTER Data
	//WriteData(UINT id, MonsterType type, AI_Type AI, std::string name, UINT speed, UINT damage, UINT minDamage, UINT health, UINT attackSpeed, UINT defense, UINT level, UINT weaponId, WORD color, WORD hitColor, UCHAR mesh);
	MonsterType type = MonsterType::MT_BASIC;
	AI_Type ai = AI_Type::AI_BASIC;
	int idx = 1;
	std::ifstream fin;
	fin.open(srcFile, std::ios::beg);
	if (fin.good())
	{
		char buff[256];
		while (!fin.eof())
		{
			fin.getline(buff, 256, '\n');
			std::string line(buff);
			if (line.length() < 5) continue;
			std::istringstream sin(line);
			sin.getline(buff, 256, ',');
			std::string mType(buff);
			sin.getline(buff, 256, ',');
			std::string sAi(buff);
			sin.getline(buff, 256, ',');
			std::string mName(buff);
			sin.getline(buff, 256, ',');
			int speed = std::stoi(buff);
			sin.getline(buff, 256, ',');
			int damage = std::stoi(buff);
			sin.getline(buff, 256, ',');
			int minDmg = std::stoi(buff);
			sin.getline(buff, 256, ',');
			int health = std::stoi(buff);
			sin.getline(buff, 256, ',');
			int atkSpeed = std::stoi(buff);
			sin.getline(buff, 256, ',');
			int defense = std::stoi(buff);
			sin.getline(buff, 256, ',');
			int level = std::stoi(buff);
			sin.getline(buff, 256, ',');
			int wId = std::stoi(buff);
			sin.getline(buff, 256, ',');
			int aId = std::stoi(buff);
			sin.getline(buff, 256, ',');
			int heal = std::stoi(buff);
			sin.getline(buff, 256, ',');
			std::string color(buff);
			sin.getline(buff, 256, ',');
			std::string hitClr(buff);
			sin.getline(buff, 256, ',');
			unsigned char mesh = std::stoi(buff);

			WriteData(idx++, StrToMonType(mType), StrToAI(sAi), mName, speed, damage, 
				minDmg, health, atkSpeed, defense, level, wId, aId, StrToColor(color), StrToColor(hitClr), mesh);
		}
	}

	fin.close();

	mData.Save(file);
}

void CreateWeapons(const std::string& file, const std::string& srcFile)
{
	/***  WEAPONS Data*/
	std::ifstream fin;
	fin.open(srcFile, std::ios::beg);

	int idx = 1;
	if (fin.good())
	{
		char buff[256];
		while (!fin.eof())
		{
			fin.getline(buff, 256, '\n');
			std::string line(buff);
			if (line.length() > 5)
			{
				std::istringstream sin(line);
				sin.getline(buff, 256, ',');
				int cellId = std::stoi(buff);
				sin.getline(buff, 256, ',');
				std::string wName(buff);
				sin.getline(buff, 256, ',');
				ItemList type = StrToItem(std::string(buff));
				sin.getline(buff, 256, ',');
				ItemMaterial mat = StrToMaterial(std::string(buff));
				sin.getline(buff, 256, ',');
				int matCost = std::stoi(buff);
				sin.getline(buff, 256, ',');
				int plusCost = std::stoi(buff);
				sin.getline(buff, 256, ',');
				int damage = std::stoi(buff);
				sin.getline(buff, 256, ',');
				int plus = std::stoi(buff);
				sin.getline(buff, 256, ',');
				int range = std::stoi(buff);
				sin.getline(buff, 256, ',');
				int price = std::stoi(buff);
				sin.getline(buff, 256, ',');
				int sell = std::stoi(buff);
				// UINT Id, ItemList type, ItemMaterial materail, UINT damage, UINT plus, UINT range, UINT price, UINT sellPrice, std::string name
				WriteData(idx++, type, mat, damage, plus, range, price, sell, wName);
			}

		}
	}

	fin.close();
	wData.Save(file);
}

void CreateAdminPlayer(const std::string& file) {
	PlayerData plData;
	plData.armorId = 5;
	plData.weaponId = 5;
	plData.id = 1;
	plData.level.Level = 1;
	plData.level.Experience = 0;
	plData.level.NextLevelExp = 0;
	//plData.name = THEADMIN;

}

void StringToChar(int maxsize, unsigned char *c_str, const std::string& str)
{
	int size = str.size();

	if (size > maxsize - 1)
	{
		size = maxsize - 1;
	}

	for (int i = 0; i < size; i++)
	{
		c_str[i] = str[i];
	}
	if (maxsize > size)
	{
		for (int i = size; i < maxsize; i++)
		{
			c_str[i] = '\0';
		}
	}
}

void StringToChar(int maxsize, char *c_str, const std::string& str)
{
	int size = str.size();

	if (size > maxsize - 1)
	{
		size = maxsize - 1;
	}

	for (int i = 0; i < size; i++)
	{
		c_str[i] = str[i];
	}
	if (maxsize > size)
	{
		for (int i = size; i < maxsize; i++)
		{
			c_str[i] = '\0';
		}
	}
}



void CreateArmor(const std::string& file, const std::string& srcFile)
{
	int id = 1;

	std::ifstream fin;
	fin.open(srcFile, std::ios::beg);

	if (fin.good())
	{
		char buff[256];
		while (!fin.eof())
		{
			fin.getline(buff, 256, '\n');
			std::string line(buff);
			if (line.length() > 5)
			{
				std::istringstream sin(line);
				sin.getline(buff, 256, ',');
				int cellId = std::stoi(buff);
				sin.getline(buff, 256, ',');
				std::string aName(buff);
				sin.getline(buff, 256, ',');
				ItemList type = StrToItem(std::string(buff));
				sin.getline(buff, 256, ',');
				ItemMaterial mat = StrToMaterial(std::string(buff));
				sin.getline(buff, 256, ',');
				int matCost = std::stoi(buff);
				sin.getline(buff, 256, ',');
				int plusCost = std::stoi(buff);
				sin.getline(buff, 256, ',');
				int ac = std::stoi(buff);
				sin.getline(buff, 256, ',');
				int plus = std::stoi(buff);
				sin.getline(buff, 256, ',');
				int price = std::stoi(buff);
				sin.getline(buff, 256, ',');
				int sell = std::stoi(buff);
				//ItemList type, ItemMaterial mat, UINT def, int plus, UINT price, UINT sellPrice, std::string name
				WriteData(id++, type, mat, ac, plus, price, sell, aName);
			}
		}
	}

	fin.close();

	/*
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_CLOTH,    1,  0,     25,    10, "Cloth Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_CLOTH,    2,  1,    150,    65, "Cloth Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_CLOTH,    3,  2,    275,   122, "Cloth Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_CLOTH,    1, -2,      5,     1, "Cloth Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_LEATHER,  7,  0,    350,   156, "Leather Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_LEATHER,  8,  1,    600,   265, "Leather Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_LEATHER,  9,  2,    850,   378, "Leather Armor");// 7
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_IRON,    12,  0,    960,   427, "Iron Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_IRON,    13,  2,   1760,   782, "Iron Armor");// 9
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_IRON,    16,  4,   2560,  1138, "Iron Armor");

	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_STEAL,   21,  0,   2100,   933, "Steal Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_STEAL,   24,  3,   3600,  1600, "Steal Armor");// 12
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_STEAL,   27,  6,   5100,  2267, "Steal Armor");

	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_MITHRIL, 12,  0,   2400,  1065, "Mithril Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_MITHRIL, 13,  3,   5000,  2200, "Mithril Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_MITHRIL, 14,  6,   7600,  3375, "Mithril Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_MITHRIL, 16, 12,  12800,  5690, "Mithril Armor");// 17

	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_MITHRIL, 19,  5,  19500,  8665, "Rune Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_MITHRIL, 20, 10,  30000, 13300, "Rune Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_MITHRIL, 22, 15,  41000, 18220, "Rune Armor");// 20

	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_BONE,	   24,  2,  25600, 11375, "Bone Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_BONE,    28,  8,  48000, 21330, "Bone Armor");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_BONE,    32, 14,  70400, 31290, "Bone Armor");// 23

	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_SCALE,   35,  2,  64500, 28665, "Dragon Scale");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_SCALE,   38,  6,  81000, 36000, "Dragon Scale");
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_SCALE,   41, 10, 109500, 48665, "Dragon Scale");// 26
	WriteData(id++, ItemList::IL_BREAST, ItemMaterial::IM_SCALE,   44, 16, 162000, 72000, "Dragon Scale");
	*/

	arData.Save(file);
}

void WriteData(int id, ItemList type, ItemMaterial mat, UINT def, int plus, UINT price, UINT sellPrice, const std::string& name)
{
	static int size = sizeof(ArmorData);
	ArmorData armor;
	armor.id = id;
	armor.defense = def;
	armor.plus = plus;
	armor.material = mat;
	armor.type = type;
	armor.price = price;
	armor.sellPrice = sellPrice;
	StringToChar(30, armor.name, name);

	armor.character.DefenseRating = def;
	armor.character.DefenseBonus = plus;
	
	arData.Add(armor);
}

MonsterType StrToMonType(const std::string& type)
{
	MonsterType mType = MT_BASIC;
	std::string myType(type);
	transform(myType.begin(), myType.end(), myType.begin(), ::toupper);

	if (myType == "MT_CAT" || myType == "CAT")
	{
		mType = MonsterType::MT_CAT;
	}
	else if (myType == "MT_DOG" || myType == "DOG")
	{
		mType = MonsterType::MT_DOG;
	}
	else if (myType == "MT_HUMAN" || myType == "HUMAN")
	{
		mType = MonsterType::MT_HUMAN;
	}
	else if (myType == "MT_ELF" || myType == "ELF")
	{
		mType = MonsterType::MT_ELF;
	}
	else if (myType == "MT_ORC" || myType == "ORC")
	{
		mType = MonsterType::MT_ORC;
	}
	else if (myType == "MT_DWARF" || myType == "DWARF")
	{
		mType = MonsterType::MT_DWARF;
	}
	else if (myType == "MT_ORGE" || myType == "ORGE")
	{
		mType = MonsterType::MT_OGRE;
	}
	else if (myType == "MT_GIANT" || myType == "GIANT")
	{
		mType = MonsterType::MT_GIANT;
	}
	else if (myType == "MT_SNAKE" || myType == "SNAKE")
	{
		mType = MonsterType::MT_SNAKE;
	}
	else if (myType == "MT_LIZARD" || myType == "LIZARD")
	{
		mType = MonsterType::MT_LIZARD;
	}
	else if (myType == "MT_LION" || myType == "LION")
	{
		mType = MonsterType::MT_LION;
	}

	if (mType == MonsterType::MT_BASIC)
	{
		// See if there is a slash in the monster type

	}

	return mType;
}

AI_Type StrToAI(const std::string& type)
{
	AI_Type aiType = AI_Type::AI_BASIC;
	std::string myType(type);

	transform(myType.begin(), myType.end(), myType.begin(), ::toupper);
	if (myType == "AI_BLIND")
	{
		aiType = AI_Type::AI_BLIND;
	}
	else if (myType == "AI_ASLEEP")
	{
		aiType = AI_Type::AI_ASLEEP;
	}
	else if (myType == "AI_PATROL")
	{
		aiType = AI_Type::AI_PATROL;
	}
	else if (myType == "AI_RANGED")
	{
		aiType = AI_Type::AI_RANGED;
	}

	return aiType;
}

ItemList StrToItem(const std::string& type)
{
	ItemList iType = ItemList::IL_NONE;
	std::string myType(type);
	transform(myType.begin(), myType.end(), myType.begin(), ::toupper);
	if (myType == "IL_STICK")
	{
		iType = ItemList::IL_STICK;
	}
	else if (myType == "IL_SWORD")
	{
		iType = ItemList::IL_SWORD;
	}
	else if (myType == "IL_DAGGER")
	{
		iType = ItemList::IL_DAGGER;
	}
	else if (myType == "IL_SLING")
	{
		iType = ItemList::IL_SLING;
	}
	else if (myType == "IL_BOW")
	{
		iType = ItemList::IL_BOW;
	}
	else if (myType == "IL_MACE")
	{
		iType = ItemList::IL_MACE;
	}
	else if (myType == "IL_LONGBOW")
	{
		iType = ItemList::IL_LONGBOW;
	}
	else if (myType == "IL_COMPOUNDBOW")
	{
		iType = ItemList::IL_COMPOUNDBOW;
	}
	else if (myType == "IL_BROADSWORD")
	{
		iType = ItemList::IL_BROADSWORD;
	}
	else if (myType == "IL_LONGSWORD")
	{
		iType = ItemList::IL_LONGSWORD;
	}
	else if (myType == "IL_BREAST")
	{
		iType = ItemList::IL_BREAST;
	}
	else if (myType == "IL_HELM")
	{
		iType = ItemList::IL_HELM;
	}
	else if (myType == "IL_GLOVES")
	{
		iType = ItemList::IL_GLOVES;
	}
	else if (myType == "IL_WAND")
	{
		iType = ItemList::IL_WAND;
	}
	/*
	else if (type == "")
	{
		iType = ItemList::;
	}
	*/

	return iType;
}

ItemMaterial StrToMaterial(const std::string& type)
{
	ItemMaterial iType = ItemMaterial::IM_NONE;
	std::string myType(type);
	transform(myType.begin(), myType.end(), myType.begin(), ::toupper);
	if (myType == "IM_HANDS")
	{
		iType = ItemMaterial::IM_HANDS;
	}
	else if (myType == "IM_WOOD ")
	{
		iType = ItemMaterial::IM_WOOD;
	}
	else if (myType == "IM_CLOTH")
	{
		iType = ItemMaterial::IM_CLOTH;
	}
	else if (myType == "IM_LEATHER")
	{
		iType = ItemMaterial::IM_LEATHER;
	}
	else if (myType == "IM_RUSTED")
	{
		iType = ItemMaterial::IM_RUSTED;
	}
	else if (myType == "IM_IRON")
	{
		iType = ItemMaterial::IM_IRON;
	}
	else if (myType == "IM_HARDWOOD")
	{
		iType = ItemMaterial::IM_HARDWOOD;
	}
	else if (myType == "IM_STEAL")
	{
		iType = ItemMaterial::IM_STEAL;
	}
	else if (myType == "IM_MITHRIL")
	{
		iType = ItemMaterial::IM_MITHRIL;
	}
	else if (myType == "IM_DIAMOND")
	{
		iType = ItemMaterial::IM_DIAMOND;
	}
	else if (myType == "IM_GOLD")
	{
		iType = ItemMaterial::IM_GOLD;
	}
	else if (myType == "IM_BONE")
	{
		iType = ItemMaterial::IM_BONE;
	}
	else if (myType == "IM_SCALE")
	{
		iType = ItemMaterial::IM_SCALE;
	}
	/*
	else if (type == "")
	{
	iType = ItemMaterial::;
	}

	*/

	return iType;
}

ConColor StrToColor(const std::string& clr)
{
	ConColor c = ConColor::Black;
	std::string myClr(clr);
	transform(myClr.begin(), myClr.end(), myClr.begin(), ::toupper);
	if (myClr == "BLUE")
	{
		c = ConColor::Blue;
	}
	else if (myClr == "GREEN")
	{
		c = ConColor::Green;
	}
	else if (myClr == "RED")
	{
		c = ConColor::Red;
	}
	else if (myClr == "LTBLUE")
	{
		c = ConColor::LtBlue;
	}
	else if (myClr == "LTGREEN")
	{
		c = ConColor::LtGreen;
	}
	else if (myClr == "LTRED")
	{
		c = ConColor::LtRed;
	}
	else if (myClr == "TORQUOISE")
	{
		c = ConColor::Torquoise;
	}
	else if (myClr == "LTTORQUOISE")
	{
		c = ConColor::LtTorquoise;
	}
	else if (myClr == "PURPLE")
	{
		c = ConColor::Purple;
	}
	else if (myClr == "LTPURPLE")
	{
		c = ConColor::LtPurple;
	}
	else if (myClr == "YELLOW")
	{
		c = ConColor::Yellow;
	}
	else if (myClr == "LTYELLOW")
	{
		c = ConColor::LtYellow;
	}
	else if (myClr == "GREY")
	{
		c = ConColor::Grey;
	}
	else if (myClr == "WHITE")
	{
		c = ConColor::White;
	}

	return c;
}