#ifndef H_NETSOCKET
#define H_NETSOCKET

// include network library
#pragma comment(lib, "Ws2_32.lib")

#define WIN32_MEAN_AND_LEAN
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <windows.h>

#include "ISocket.h"
#include "IError.h"
#include "INetCrypto.h"

#define NETPORTDEF 13579
#define MAX_BUFFER 256

namespace Zaxis{ namespace Network
{

	class NetSocket : public ISocket, public Zaxis::Error::IError
	{
	private: 
		u_short _port;
		std::string _serverName;
		struct addrinfo *server;
		struct sockaddr_in *serverAddress;
		SOCKADDR_IN serverTarget;
		SOCKET serverSock;
		SOCKET cSock;

		int _revcDataSize;
		char gBuff[MAX_BUFFER];
		std::string sBuff;

		LPNETCRYPTO crypto;

		int _errno;
		std::string _errmsg;

	public:
		NetSocket(std::string serverName, u_short port = NETPORTDEF);
		virtual ~NetSocket();

		virtual bool InitCrypto(std::string preshare);

		bool Startup();
		void Listen();
		bool Connect(SOCKET sock, const sockaddr_in &addr);

		virtual bool Send(const std::string &data);
		virtual bool Send(const char *buff, int size);
		virtual bool Send(const int num);
		virtual bool Send(const char c);
		virtual bool SendLine(const std::string &data);

		virtual int Recv();

		virtual void ClearSock(SOCKET sock);
		virtual void ClearSock();

		virtual int GetErrNo();
		virtual std::string GetErrMsg();

		virtual void GetData(char *buff);
		virtual void GetData(char *buff, int size);
		virtual void GetData(char *buff, int start, int size);
		virtual void GetData(std::string *data);
		
		virtual std::string GetStr();
		virtual std::string trim(const std::string &s);
				
		virtual void Close();

		void Sleep(int millisec);
	};

} }// End of namespace Zaxis::Network

#endif