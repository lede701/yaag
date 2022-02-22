#ifndef H_NULLCRYPTO
#define H_NULLCRYPTO

#include "INetCrypto.h"

namespace Zaxis{ namespace Network
{

	class NullCrypto : public INetCrypto
	{
	public:
		NullCrypto();
		virtual ~NullCrypto();

		virtual std::string Encrypt(const std::string &data);
		virtual std::string Decrypt(const std::string &data);

		virtual int GetErrNo();
		virtual std::string GetErrMsg();

		virtual std::string RandomKey();
	};

} }// End namespace Zaxis::Network

#endif