#include "IEntity.h"

namespace Zaxis{ namespace Entity
{

	IEntity::IEntity()
	{
		Init();
	}

	IEntity::IEntity(EntityType inType)
	{
		Init();
		Type = inType;
	}

	void IEntity::Init()
	{
		_mesh = NULL;
		_mover = NULL;
		Type = ET_OBJECT;
		Object::Init();
		_oldPos = GetPosition2D()->Clone();
	}

	IEntity::~IEntity()
	{
		if (_oldPos != NULL)
		{
			delete _oldPos;
			_oldPos = NULL;
		}
		if (_mover != NULL)
		{
			delete _mover;
			_mover = NULL;
		}
		if (_mesh != NULL)
		{
			delete _mesh;
			_mesh = NULL;
		}
	}

	LPENTITY IEntity::SetMover(LPMOVER mover)
	{
		_mover = mover;
		if (Log() != NULL)
		{
			_mover->SetLogger(Log());
		}
		return this;
	}

	LPMOVER IEntity::GetMover()
	{
		return _mover;
	}

	LPOBJECT IEntity::Update()
	{
		if (GetMover() != NULL)
		{
			// Save old position
			SetOldPosition2D(GetPosition2D());
			GetMover()->Move2D(GetPosition2D());
		}

		return this;
	}

	LPOBJECT IEntity::SetPosition2D(LPVECTOR2D pos)
	{
		Object::SetPosition2D(pos);
		// Make sure to update the old position
		SetOldPosition2D(pos);

		return this;
	}

	LPENTITY IEntity::SetOldPosition2D(LPVECTOR2D pos)
	{
		if (_oldPos == NULL)
		{
			_oldPos = pos->Clone();
		}
		else
		{
			_oldPos->x = pos->x;
			_oldPos->y = pos->y;
		}

		return this;
	}

	LPVECTOR2D IEntity::GetOldPosition2D()
	{
		return _oldPos;
	}

	LPENTITY IEntity::SetMesh(void* mesh)
	{
		if (_mesh != NULL)
		{
			delete _mesh;
			_mesh = NULL;
		}
		_mesh = mesh;

		return this;
	}

	void* IEntity::GetMesh()
	{
		return _mesh;
	}

} }// End namespace Zaxis::Entity	class Entity

