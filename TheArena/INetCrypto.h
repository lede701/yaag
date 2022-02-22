#ifndef H_INETCRYPTO
#define H_INETCRYPTO

#include <string>

#define LPNETCRYPTO Zaxis::Network::INetCrypto*

namespace Zaxis{ namespace Network{

	class INetCrypto
	{
	public:
		INetCrypto();
		virtual ~INetCrypto();

		virtual std::string Encrypt(const std::string &data) = 0;
		virtual std::string Decrypt(const std::string &data) = 0;

		virtual int GetErrNo() = 0;
		virtual std::string GetErrMsg() = 0;

		virtual std::string RandomKey() = 0;

	};

} }// End namespace Zaxis::Network


#endif