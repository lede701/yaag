#ifndef H_PROJECTILE
#define H_PROJECTILE

#include "IAttacker.h"
#include "IEntity.h"
#include "IEntityManager.h"
#include "IGraphics.h"
#include "ConObject.h"

#define LPPROJECTILE Game::Items::Projectile::Projectile*

namespace Game{ namespace Items{ namespace Projectile
{ 
	using Zaxis::Entity::IEntity;
	using Zaxis::Graphics::ConGraphicsData::ConObject;
	using Game::Data::CharacterData;

	class Projectile :
		public IEntity, public Game::IAttacker
	{
	private:
		LPVECTOR2D _velocity;
		ConObject _myMesh;
		Game::IEntityManager* _manager;
		LPATTACKER _owner;
		unsigned int _distance;
		unsigned int _currDistance;
		LPENGSOUND _sound;

		LPCHARACTER character;

	public:
		Projectile(LPVECTOR2D velocity, unsigned int distance, LPATTACKER owner);
		virtual ~Projectile();

		// Update method for game engine to move me
		virtual LPOBJECT Update();
		virtual void Draw(LPGRAPHICS gfx);

		// IAttacker Interface methods
		virtual void Attack(LPATTACKER who);
		virtual void Defend(int attackRoll, unsigned int damage);
		virtual int GetDefense();
		virtual bool IsDead();
		virtual LPLOOT GetLoot();
		virtual int iGetLevel();

		virtual void SetManager(Game::IEntityManager* manager);

		virtual void* GetMesh();

		virtual LPCHARACTER GetCharacter();

		// ISound Interface methods
		virtual LPOBJECT SetSound(LPENGSOUND sound);
		virtual LPENGSOUND Sound();

		virtual bool IsAttackReady();
	};

} } }// End namespace Game::Items::Projectile

#endif