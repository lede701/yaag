#ifndef H_NULLGRAPHICS
#define H_NULLGRAPHICS

#include "IGraphics.h"

namespace Zaxis{ namespace Graphics
{

	class NullGraphics :
		public IGraphics
	{
		int color;
	public:
		NullGraphics();
		virtual ~NullGraphics();

		virtual void Init();
		virtual void Dispose();
		virtual void Update();

		virtual void Draw(LPOBJECT obj);
		virtual void Draw(LPENTITY entity);
		virtual void DrawRect(LPRECT2D rect, void* ch);
		virtual void DrawRect(LPRECT2D rect, void* ch, void* bkg);

		virtual void DrawText(const std::string& line, LPVECTOR2D pos);
		virtual void DrawText(const std::string& line, int x, int y);

		virtual void SetTextColor(int color);
		virtual int GetTextColor();

		virtual void Flush();

	};

} }// End namespace Zaixs::Graphics

#endif