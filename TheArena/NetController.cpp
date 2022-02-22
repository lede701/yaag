#include "NetController.h"
#include <iostream>
#include <sstream>
#include "SocketException.h"
#include "NetSocket.h"

namespace Zaxis{ namespace Controllers
{
	using Zaxis::Network::NetworkException;

	NetController::NetController(std::string server, int portNum/* = NETPORTDEF */)
	{
		Init();
		ConnectToHost(server, portNum);
	}

	NetController::NetController()
	{
		Init();
	}

	NetController::~NetController()
	{
		Disconnect();
	}

	void NetController::Init()
	{
		server = NULL;
		serverAddress = NULL;
	}

	bool NetController::ChkInput(int vk)
	{
		bool bRetVal = false;
		socket->Send(vk);
		if (socket->Recv() > 0)
		{
			int rVk = atoi(socket->GetStr().c_str());
			bRetVal = rVk == vk;
		}
		return bRetVal;
	}

	char NetController::GetInput()
	{
		// TODO: Pull input from the network
		return false;
	}

	// Updater methods
	void NetController::Update()
	{

	}

	bool NetController::Shutdown()
	{
		return false;
	}

	// Connect to host method that tries the localhost name
	bool NetController::ConnectToHost()
	{
		return ConnectToHost("localhost", NETPORTDEF);
	}

	// Connect to host method
	bool NetController::ConnectToHost(const std::string &server, int portNum/* = NETPORTDEF */)
	{
		bool bRetVal = false;
		port = portNum;
		svrName = server;

		socket = new Zaxis::Network::NetSocket(svrName, port);
		bRetVal = socket->Startup();

		return bRetVal;
	}

	// Close down connection
	void NetController::Disconnect()
	{
		socket->Close();
		delete socket;
		socket = NULL;
	}
} }// End namespace Zaxis::Controllers
