#include "Object.h"

#include <stddef.h>
#include "NullLogger.h"

namespace Zaxis{ namespace Core
{

	Object::Object()
	{
		Init();
	}


	Object::~Object()
	{
		if (_pos2d != NULL)
		{
			delete _pos2d;
			_pos2d = NULL;
		}
	}

	void Object::Init()
	{
		_isAsleep = true;
		_log = new Zaxis::Logging::NullLogger();
		_pos2d = new Zaxis::Math::Vector2D(0,0);
	}

	LPOBJECT Object::SetId(int id)
	{
		Id = id;
		return this;
	}

	int Object::GetId()
	{
		return Id;
	}

	LPOBJECT Object::SetPosition2D(LPVECTOR2D pos)
	{
		if (_pos2d != NULL)
		{
			delete _pos2d;
			_pos2d = NULL;
		}
		_pos2d = pos;
		return this;
	}

	LPVECTOR2D Object::GetPosition2D()
	{
		return _pos2d;
	}

	LPOBJECT Object::SetX(int x)
	{
		if (_pos2d != NULL)
		{
			_pos2d->SetX(x);
		}

		return this;
	}

	LPOBJECT Object::SetY(int y)
	{
		if (_pos2d != NULL)
		{
			_pos2d->SetY(y);
		}

		return this;
	}

	LPOBJECT Object::SetXY(int x, int y)
	{
		return SetX(x)->SetY(y);
	}

	bool Object::IsAsleep()
	{
		return _isAsleep;
	}

	LPOBJECT Object::SetSleeping(bool bVal)
	{
		_isAsleep = bVal;
		return this;
	}

	LPOBJECT Object::GoingToSleep()
	{
		return this;
	}

	LPOBJECT Object::SetLogger(LPLOGGER log)
	{
		_log = log;
		Log("Object has been added to logger");
		return this;
	}

	LPLOGGER Object::Log()
	{
		return _log;
	}

	LPLOGGER Object::Log(std::string line)
	{
		_log->WriteLine(line);
		return _log;
	}

} }// End namespace Zaxis::Core