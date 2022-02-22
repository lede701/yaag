#ifndef H_RANDOM
#define H_RANDOM

#define LPRANDOM Zaxis::Math::Random*

namespace Zaxis{ namespace Math
{

	class Random
	{
	public:
		Random();
		~Random();

		int Next();
		int Next(int max);
		int Next(int min, int max);
	};

} }// End namespace Zaxis::Math

#endif