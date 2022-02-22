#ifndef H_LEVELDATA
#define H_LEVELDATA

namespace Game{ namespace Data
{

	struct LevelDataV3
	{

	public:
		unsigned int Level;
		unsigned long long int Experience;
		unsigned long long int NextLevelExp;
		unsigned long int Gold;

	};

	struct LevelDataV4 : LevelDataV3
	{

	public:
		unsigned long long int PrevLevelExp;

	};

	struct LevelData : LevelDataV4
	{
	public:
		unsigned int AssignedPoints;
	};


} }// End namespace Game::Data

#endif