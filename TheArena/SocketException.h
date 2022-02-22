#ifndef H_SOCKETEXCEPTION
#define H_SOCKETEXCEPTION

namespace Zaxis{ namespace Network
{

	class NetworkException
	{
	public:
		NetworkException();
		NetworkException(const char* pMessage);
		virtual ~NetworkException();
		const char * what();
	private:
		const char *m_pMessage;
	};

}}// End namespace Zaxis::Network

#endif