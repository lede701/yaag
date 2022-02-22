#include "NullCrypto.h"

namespace Zaxis{ namespace Network
{

	NullCrypto::NullCrypto()
	{
	}


	NullCrypto::~NullCrypto()
	{
	}

	std::string NullCrypto::Encrypt(const std::string &data)
	{
		return data;
	}

	std::string NullCrypto::Decrypt(const std::string &data)
	{
		return data;
	}

	int NullCrypto::GetErrNo()
	{
		return 0;
	}

	std::string NullCrypto::GetErrMsg()
	{
		return "";
	}

	std::string NullCrypto::RandomKey()
	{
		return "";
	}

} }// End namespace Zaxis::Network


