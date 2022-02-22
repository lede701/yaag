#ifndef H_NULLOBJECT
#define H_NULLOBJECT

#include "Object.h"

namespace Zaxis{ namespace Core
{

	class NullObject :
		 public Object
	{
		LPENGSOUND _snd;
	public:
		NullObject();
		~NullObject();

		virtual LPOBJECT Update();

		virtual LPOBJECT SetSound(LPENGSOUND sound);
		virtual LPENGSOUND Sound();

	};

} }// End namespace Zaxis::Core


#endif