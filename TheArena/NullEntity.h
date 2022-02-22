#ifndef H_NULLENTITY
#define H_NULLENTITY

#include "IEntity.h"

namespace Zaxis{ namespace Entity
{
	class NullEntity
		: public IEntity
	{
	private:
		char _myMesh;

		LPENGSOUND snd;

	public:
		NullEntity();
		~NullEntity();

		virtual void Init(void);

		virtual LPOBJECT Update();
		virtual LPOBJECT SetUpdate(unsigned int interval);
		virtual unsigned int GetSpeed();

		virtual LPOBJECT SetSound(LPENGSOUND sound);
		virtual LPENGSOUND Sound();

		virtual bool IsAlive();

	};
} }

#endif