#ifndef H_IFIELDEXIT
#define H_IFIELDEXIT

#include "Vector2D.h"

#define LPFIELDEXIT Game::Data::IFieldExit*

namespace Game{ namespace Data
{

	class IFieldExit
	{
	public:
		IFieldExit();
		virtual ~IFieldExit();

		virtual LPVECTOR2D GetExit() = 0;
		virtual void SetExit(LPVECTOR2D exit) = 0;
	};

} }// End namespace Game::Data

#endif