#include "SocketException.h"

namespace Zaxis{ namespace Network
{

	NetworkException::NetworkException() : m_pMessage("")
	{
	}

	NetworkException::NetworkException(const char* pMessage) : m_pMessage(pMessage)
	{
	}

	NetworkException::~NetworkException()
	{
	}

	const char * NetworkException::what() { 
		return m_pMessage; 
	}
	
}}// End namespace Zaxis::Network
