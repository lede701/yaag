#include "FieldBrick.h"

namespace Game{ namespace  Field
{ 
	FieldBrick::FieldBrick()
	{
		life = 100000000;
	}


	FieldBrick::~FieldBrick()
	{
	}

	bool FieldBrick::IsAlive()
	{
		return life > 0;
	}

	bool FieldBrick::IsFriendly(LPENTITY entity)
	{
		return true;
	}

} }// End namespace Game::Field

