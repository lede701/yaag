#ifndef H_NETCONTROLLER
#define H_NETCONTROLLER

// include network library
#pragma comment(lib, "Ws2_32.lib")

#include "IController.h"
#include "IStateManager.h"
#include "IUpdater.h"
#include "ISocket.h"
#include <string>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <windows.h>

#define NETPORTDEF 13579
#define MAX_BUFFER_SIZE 256

// Network tutorial: http://www.madwizard.org/programming/tutorials/netcpp/5

namespace Zaxis{ namespace Controllers
{
	class NetController :
		public IController, public Zaxis::Engine::IUpdater
	{
	private:
		std::string svrName;
		int port;

		struct addrinfo *server;
		struct sockaddr_in *serverAddress;
		SOCKADDR_IN serverTarget;

		char buff[MAX_BUFFER_SIZE];

		LPSOCKET socket;

	public:
		NetController(std::string server, int portNum = NETPORTDEF);
		NetController();
		virtual ~NetController();

		void Init();

		// Controller methods
		virtual bool ChkInput(int vk);
		virtual char GetInput();

		// Updater methods
		virtual void Update();
		virtual bool Shutdown();

		// NetController methods
		virtual bool ConnectToHost();
		virtual bool ConnectToHost(const std::string &server, int portNum = NETPORTDEF);
		// Close down connection
		virtual void Disconnect();

	};

	const char HEAD_REQUEST_1[] = {
		"SHELL\r\n"
	};

	const char HEAD_REQUEST_2[] = {
		"\r\n"
		"User-agent: ZaxisEngine 1.0\r\n"
		"Connection: close\r\n"
		"\r\n\r\n"
	};
} }// End namespace Zaxis::Controllers

#endif