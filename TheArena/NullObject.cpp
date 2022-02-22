#include "NullObject.h"

namespace Zaxis{ namespace Core
{

	NullObject::NullObject()
	{
	}


	NullObject::~NullObject()
	{
	}

	LPOBJECT NullObject::Update()
	{
		return this;
	}

	LPOBJECT NullObject::SetSound(LPENGSOUND sound)
	{
		_snd = sound;
		return this;
	}

	LPENGSOUND NullObject::Sound()
	{
		return _snd;
	}

} }// End namespace Zaxis::Core


