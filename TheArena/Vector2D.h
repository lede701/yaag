#ifndef H_VECTOR2D
#define H_VECTOR2D

#define LPVECTOR2D Zaxis::Math::Vector2D*
#include <sstream>

namespace Zaxis{ namespace Math
{
	using std::ostringstream;

	class Vector2D
	{
	public:
		int x;
		int y;

		Vector2D();
		Vector2D(int x, int y);

		LPVECTOR2D Clone();
		LPVECTOR2D Clone(Vector2D vec);
		LPVECTOR2D Clone(LPVECTOR2D vec);
		LPVECTOR2D Clone(bool invert);

		~Vector2D();

		LPVECTOR2D SetX(int ix);
		LPVECTOR2D SetY(int iy);
		LPVECTOR2D SetXY(int x, int y);

		std::string ToString();
	};

} }// End namespace Zaxis::Math

#endif