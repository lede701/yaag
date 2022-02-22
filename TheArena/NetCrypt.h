#ifndef H_NETCRYPTO
#define H_NETCRYPTO

#include "INetCrypto.h"
#include "NetCrypt.h"
#include "IError.h"

namespace Zaxis{ namespace Network
{

	class NetCrypt : public INetCrypto, public Zaxis::Error::IError
	{
	private:
		std::string key;
		std::string iv;

		int _errno;
		std::string _errmsg;

	public:
		NetCrypt(std::string key, std::string iv);
		~NetCrypt();

		virtual std::string Encrypt(const std::string &data);
		virtual std::string Decrypt(const std::string &data);

		virtual int GetErrNo();
		virtual std::string GetErrMsg();

		virtual std::string RandomKey();

		std::string trim(const std::string s);

		static NetCrypt* Hello();
	};

} }// End namespace Zaxis::Network

#endif