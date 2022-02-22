#ifndef H_DIRECTION
#define H_DIRECTION

#define LPDIRECTION Game::Entity::IDirection*

namespace Game{ namespace Entity
{

	class IDirection
	{
	public:
		IDirection();
		virtual ~IDirection();

		virtual bool MoveUp() = 0;
		virtual bool MoveDown() = 0;
		virtual bool MoveLeft() = 0;
		virtual bool MoveRight() = 0;

	};

} }// End namespace Game::Entity

#endif