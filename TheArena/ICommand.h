#ifndef H_ICOMMAND
#define H_ICOMMAND

#define LPCOMMAND Zaxis::Commands::ICommand*

namespace Zaxis{ namespace Commands
{

	class ICommand
	{
	public:
		ICommand();
		virtual ~ICommand();

		virtual void Execute() = 0;
	};

} }// End namepsace Zaxis::Commands

#endif