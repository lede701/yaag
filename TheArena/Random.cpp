#include "Random.h"

#include <stdlib.h>
#include <time.h>

namespace Zaxis{ namespace Math
{

	Random::Random()
	{
		// Set random seed
		srand(static_cast<int>(time(0)));
	}


	Random::~Random()
	{
	}

	int Random::Next()
	{
		// Return a raw random number
		return rand();
	}

	int Random::Next(int max)
	{
		// Return a random number between 0 and max
		return Next(0, max);
	}

	int Random::Next(int min, int max)
	{
		int val = 0;
		// Calculate random number based on min and max values
		if ((max - min) > 0)
		{
			val = min + (Next() % abs(max - min));
		}
		else
		{
			// Need to log this error
		}

		// Return my random number
		return val;
	}

} }// End namespace Zaxis::Math

