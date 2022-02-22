#include "Vector2D.h"

namespace Zaxis{ namespace Math
{

	Vector2D::Vector2D()
	{
		x = 0;
		y = 0;
	}

	Vector2D::Vector2D(int ix, int iy)
	{
		x = ix;
		y = iy;
	}

	LPVECTOR2D Vector2D::Clone()
	{
		return new Vector2D(x, y);
	}

	LPVECTOR2D Vector2D::Clone(Vector2D vec)
	{
		return new Vector2D(vec.x, vec.y);
	}

	LPVECTOR2D Vector2D::Clone(LPVECTOR2D vec)
	{
		return new Vector2D(vec->x, vec->y);
	}

	LPVECTOR2D Vector2D::Clone(bool invert)
	{
		if (invert)
		{
			return new Vector2D(x * -1, y * -1);
		}
		else
		{
			return Clone();
		}
	}

	Vector2D::~Vector2D()
	{
	}

	LPVECTOR2D Vector2D::SetX(int ix)
	{
		x = ix;
		return this;
	}

	LPVECTOR2D Vector2D::SetY(int iy)
	{
		y = iy;
		return this;
	}

	LPVECTOR2D Vector2D::SetXY(int ix, int iy)
	{
		return SetX(ix)->SetY(iy);
	}

	std::string Vector2D::ToString()
	{
		ostringstream out;
		out << "[" << x << ", " << y << "]";
		return out.str();
	}

} }// End namespace Zaxis::Math