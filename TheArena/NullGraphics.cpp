#include "NullGraphics.h"

namespace Zaxis{ namespace Graphics
{

	NullGraphics::NullGraphics()
	{
		color = 0;
	}


	NullGraphics::~NullGraphics()
	{
	}

	void NullGraphics::Draw(LPOBJECT obj)
	{
		
	}

	void NullGraphics::Draw(LPENTITY entity)
	{
	}

	void NullGraphics::DrawRect(LPRECT2D rect, void* ch)
	{

	}

	void NullGraphics::DrawRect(LPRECT2D rect, void* ch, void* bkg)
	{

	}

	void NullGraphics::DrawText(const std::string& line, LPVECTOR2D pos)
	{
	}

	void NullGraphics::DrawText(const std::string& line, int x, int y)
	{
	}


	void NullGraphics::Init()
	{
	}

	void NullGraphics::Dispose()
	{

	}

	void NullGraphics::Update()
	{
	}

	void NullGraphics::SetTextColor(int color)
	{
		color = color;
	}

	int NullGraphics::GetTextColor()
	{
		return color;
	}

	void NullGraphics::Flush()
	{

	}

} }// End namespace Zaixs::Graphics
