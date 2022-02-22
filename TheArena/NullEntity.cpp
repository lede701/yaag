#include "NullEntity.h"

namespace Zaxis{ namespace Entity
{
	NullEntity::NullEntity()
	{
		SetSleeping(true);
	}

	NullEntity::~NullEntity()
	{

	}

	void NullEntity::Init()
	{

	}

	LPOBJECT NullEntity::Update()
	{

		return this;
	}

	LPOBJECT NullEntity::SetUpdate(unsigned int interval)
	{
		return this;
	}

	unsigned int NullEntity::GetSpeed()
	{
		return 30;
	}

	bool NullEntity::IsAlive()
	{
		return false;
	}

	LPOBJECT NullEntity::SetSound(LPENGSOUND sound)
	{
		snd = sound;
		return this;
	}

	LPENGSOUND NullEntity::Sound()
	{
		return snd;
	}

} }
