#ifndef H_FILEUTILITIES
#define H_FILEUTILITIES

#include <string>

enum ValidateType
{
	VT_NONE,
	VT_PLAYER,
	VT_MONSTER,
	VT_WEAPONS,
	VT_ARMOR
};

void ValidateFile(std::string file, ValidateType type);
bool PlayerDbUpdate(std::string file, int ver);

#endif