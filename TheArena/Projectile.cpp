#include "Projectile.h"
#include "ConColor.h"
#include "ConGraphics.h"

using Zaxis::Graphics::ConGraphicsData::ConColor;
using Zaxis::Graphics::ConGraphics;

namespace Game{ namespace Items{ namespace Projectile
{ 

	Projectile::Projectile(LPVECTOR2D velocity, unsigned int distance, LPATTACKER owner)
	{
		_velocity = velocity;
		_owner = owner;
		_distance = distance;
		_currDistance = 0;
		// Figure out which direction the projectile is going
		if ((velocity->x > 0 || velocity->x < 0) && velocity->y == 0)
		{
			_myMesh.c = 45;
		}
		else if ((velocity->y > 0 || velocity->y < 0) && velocity->x == 0)
		{
			_myMesh.c = 124;
		}
		else if ((velocity->x > 0 && velocity->y < 0) || (velocity->x < 0 && velocity->y > 0))
		{
			_myMesh.c = 47;
		}
		else if ((velocity->x < 0 && velocity->y > 0) || (velocity->x > 0 && velocity->y < 0))
		{
			_myMesh.c = 92;
		}

		character = owner->GetCharacter();

		_myMesh.color = ConColor::Grey;
	}


	Projectile::~Projectile()
	{
	}

	LPOBJECT Projectile::Update()
	{
		// Get current position of projectile
		LPVECTOR2D move = GetPosition2D();
		// Check current position to see if we are occupying a square with a target
		LPENTITY entity = _manager->GetEntity(move);
		if (entity != NULL)
		{
			Attack(dynamic_cast<LPATTACKER>(entity));
			_manager->RmEntity(this, false);
		}
		else
		{
			// Record its old location
			SetOldPosition2D(move);
			// Move projectile
			move->x += _velocity->x;
			move->y += _velocity->y;
			// See if projectile hit something
			LPENTITY entity = _manager->GetEntity(move);
			if (entity != NULL)
			{
				// Process attack
				Attack(dynamic_cast<LPATTACKER>(entity));
				// Remove projectile from world
				_manager->RmEntity(this, false);
				return NULL;
			}
		}
		// See if projectile distance has been reached
		if (++_currDistance >= _distance)
		{
			// I've lived passed my distance
			_manager->RmEntity(this, false);
			return NULL;
		}
		return this;
	}

	void Projectile::Draw(LPGRAPHICS gfx)
	{
		ConGraphics* cGfx = dynamic_cast<ConGraphics*>(gfx);
		if (cGfx != NULL)
		{
			// Draw projectile
		}
	}

	void Projectile::Attack(LPATTACKER who)
	{
		_owner->Attack(who);
	}

	void Projectile::Defend(int attackRoll, unsigned int damage)
	{

	}

	int Projectile::GetDefense()
	{
		return _owner->GetDefense();
	}

	LPLOOT Projectile::GetLoot()
	{
		return _owner->GetLoot();
	}

	bool Projectile::IsDead()
	{
		return false;
	}

	void* Projectile::GetMesh()
	{
		return &_myMesh;
	}

	void Projectile::SetManager(Game::IEntityManager* manager)
	{
		_manager = manager;
	}

	LPOBJECT Projectile::SetSound(LPENGSOUND snd)
	{
		_sound = snd;
		return this;
	}

	LPENGSOUND Projectile::Sound()
	{
		return _sound;
	}

	bool Projectile::IsAttackReady()
	{
		return true;
	}

	int Projectile::iGetLevel()
	{
		return _owner->iGetLevel();
	}

	LPCHARACTER Projectile::GetCharacter()
	{
		return character;
	}

} } }// End namespace Game::Items::Projectile
