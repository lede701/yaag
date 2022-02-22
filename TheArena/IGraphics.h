#ifndef H_IGRAPHICS
#define H_IGRAPHICS

#define LPGRAPHICS Zaxis::Graphics::IGraphics*

#include "IEntity.h"
#include "Object.h"
#include "zmath.h"

namespace Zaxis{ namespace Graphics
{ 

	class IGraphics
	{
	public:
		IGraphics();
		virtual ~IGraphics();

		virtual void Update() = 0;
		virtual void Init() = 0;
		virtual void Dispose() = 0;

		virtual void Draw(LPOBJECT obj) = 0;
		virtual void Draw(LPENTITY entity) = 0;

		virtual void DrawRect(LPRECT2D rect, void* ch, void* bkg) = 0;
		virtual void DrawRect(LPRECT2D rect, void* ch) = 0;

		virtual void DrawText(const std::string& line, LPVECTOR2D pos) = 0;
		virtual void DrawText(const std::string& line, int x, int y) = 0;

		virtual void SetTextColor(int color) = 0;
		virtual int GetTextColor() = 0;

		virtual void Flush() = 0;
	};

} }// End namespace Zaxis::Graphics

#endif