#ifndef H_NULLCOMMAND
#define H_NULLCOMMAND

#include "ICommand.h"

namespace Zaxis{ namespace Commands
{

	class NullCommand :
		public ICommand
	{
	public:
		NullCommand();
		virtual ~NullCommand();

		virtual void Execute();
	};

} }// End namespace Zaxis::Commands

#endif