#ifndef H_IERROR
#define H_IERROR

#include <string>

namespace Zaxis{ namespace Error{

	class IError
	{
	public:
		IError();
		virtual ~IError();

		virtual int GetErrNo() = 0;
		virtual std::string GetErrMsg() = 0;
	};

} }// End namespace Zaxis::Error

#endif