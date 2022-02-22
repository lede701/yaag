#ifndef H_ISOCKET
#define H_ISOCKET

#define LPSOCKET Zaxis::Network::ISocket*

#include <string>

namespace Zaxis{ namespace Network
{

	class ISocket
	{
	public:
		ISocket();
		virtual ~ISocket();

		virtual bool Startup() = 0;
		virtual bool InitCrypto(std::string preshare) = 0;

		virtual bool Send(const std::string &data) = 0;
		virtual bool Send(const char *buff, int size) = 0;
		virtual bool Send(const int num) = 0;
		virtual bool Send(const char c) = 0;
		virtual bool SendLine(const std::string &data) = 0;

		virtual int Recv() = 0;

		virtual void ClearSock() = 0;

		virtual void GetData(char *buff) = 0;
		virtual void GetData(char *buff, int size) = 0;
		virtual void GetData(char *buff, int start, int size) = 0;
		virtual void GetData(std::string *data) = 0;

		virtual std::string GetStr() = 0;
		virtual std::string trim(const std::string &s) = 0;

		virtual void Close() = 0;
	};

} }// End of namespace Zaxis::Network

#endif