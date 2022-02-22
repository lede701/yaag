#include "NetSocket.h"

#include <iostream>
#include <sstream>
#include <exception>
#include <thread>
#include <chrono>

// Encryption headers
//#include <aes.h>
//#include <modes.h>
//#include <filters.h>

#include "NullCrypto.h"
#include "NetCrypt.h"

namespace Zaxis{ namespace Network
{

	NetSocket::NetSocket(std::string server, u_short port/* = NETPORTDEF*/)
	{
		_serverName = server;
		_port = port;
		cSock = INVALID_SOCKET;

		crypto = NULL;
		_errno = 0;
		_errmsg = "";
	}
	
	NetSocket::~NetSocket()
	{
		Close();
	}

	bool NetSocket::Startup()
	{
		using std::ostringstream;

		bool bRetVal = false;
		//*
		WSADATA wsa;
		WORD wVerReq = MAKEWORD(2, 2);
		// Startup win sockets
		int err = WSAStartup(wVerReq, &wsa);
		if (err == 0)
		{
			// Check for proper winsock version
			if (LOBYTE(wsa.wVersion) == 2 && HIBYTE(wsa.wVersion) == 2)
			{
				// Create a hint for getaddrinfo
				struct addrinfo hints;
				ZeroMemory(&hints, sizeof(hints));
				hints.ai_family = AF_UNSPEC;
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_protocol = IPPROTO_TCP;

				// Convert server name to PCSTR
				const char *sName = _serverName.c_str();
				std::ostringstream out;
				out.str(""); out.clear();
				// Convert port to PCSTR
				// TODO: Remove test port information and user server port
				out << _port;

				std::string strPort = out.str();
				const char *sPort = strPort.c_str();

				struct addrinfo *addr;
				struct addrinfo *ptr;

				// Get Address Information
				_errno = getaddrinfo(sName, sPort, &hints, &addr);
				if (_errno == 0)
				{
					// Get the address of server to use for connection
					for (ptr = addr; ptr != NULL; ptr = ptr->ai_next)
					{
						// Find an acceptable ip address
						switch (ptr->ai_family)
						{
						case AF_INET:
							// Found a connection
							serverAddress = (struct sockaddr_in *) ptr->ai_addr;
							server = ptr;
							bRetVal = true;
							break;
						}// End switch for ai_family
					}// End for each address in linked list

					// Check if a IP address was found
					if (bRetVal)
					{
						bRetVal = false;
						cSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
						if (cSock != INVALID_SOCKET)
						{
							serverTarget.sin_family = serverAddress->sin_family;
							serverTarget.sin_port = serverAddress->sin_port;
							serverTarget.sin_addr = serverAddress->sin_addr;
							bRetVal = Connect(cSock, serverTarget);
						}
						else
						{
							// Report a socket connection error
							_errno = 902;
							_errmsg = "Error creating socket!";
						}// Endif cSock is not INVALID_SOCKET
					}// Endif valid IP address was found

				}
				else
				{
					_errmsg = "Failed to get server address!";
				}// Endif getaddrinfo failure check
			}
			else
			{
				_errno = 901;
				_errmsg = "Error WinSock library is no v2.2";
			}// Endif wVersion is 2.2
		}
		else
		{
			_errno = 900;
			_errmsg = "Error WinSock didn't startup properly";
		}
		//*/

		return bRetVal;
	}

	bool NetSocket::InitCrypto(std::string preshare)
	{
		bool bRetVal = false;
		std::string delim = "\r\n";
		LPNETCRYPTO orgCrypto = crypto;

		// Switch to initial handshake
		crypto = NetCrypt::Hello();

		Sleep(500);

		// Say encrypted hello to server
		std::string clientResp = "SHELL SERVER";
		SendLine(clientResp);

		std::string key;
		std::string iv;
		if (Recv() > 0)
		{
			int pos = sBuff.find_first_of(delim);
			// Check if server sent both keys
			if (pos != std::string::npos)
			{
				// Assign encryption keys to local strings
				key = trim(sBuff.substr(0, pos));
				iv = trim(sBuff.substr(pos + 2, sBuff.length()));
			}

			// Validate we have proper keys
			if (key.length() == 16 && iv.length() == 16)
			{
				// Delete hello crypto
				delete crypto;
				// Create new crypto object for session
				crypto = new NetCrypt(key, iv);
				Send("S_OK");
				Recv();
				pos = sBuff.find_first_of(delim);
				if (trim(sBuff.substr(0, pos)) == "S_OK")
				{
					// Server and I are connected
					std::cout << "Server and I are connected!" << std::endl;
					delete orgCrypto;
					orgCrypto = NULL;
					bRetVal = true;
				}// Check if server response was decryptable
			}// Endif check for valid encryption keys
		}
		else
		{
			_errno = 1000 + crypto->GetErrNo();
			_errmsg = crypto->GetErrMsg();
			delete crypto;
			crypto = orgCrypto;
		}// Endif Recv return data

		return bRetVal;
	}

	bool NetSocket::Connect(SOCKET sock, const sockaddr_in &addr)
	{
		bool bRetVal = false;
		cSock = sock;
		// Make sure we are using non encrypted handshake
		if (crypto != NULL)
		{
			delete crypto;
		}
		crypto = new NullCrypto();

		if (connect(sock, (SOCKADDR *)&addr, sizeof(addr)) != SOCKET_ERROR)
		{
			std::string msg;
			// Check if server has said hello
			if (Recv() > 0)
			{
				msg = trim(sBuff);
				if (msg == "HELLO")
				{
					ClearSock(cSock);
					// Tell server we want to use encryption
					Send("SHELL");
					bRetVal = InitCrypto("YAAG2015Secret21");
				}
			}
		}

		return bRetVal;
	}

	bool NetSocket::Send(const std::string &data)
	{
		return Send(data.c_str(), data.length());
	}

	bool NetSocket::Send(const char *buff, int size)
	{
		std::ostringstream out;
		out << buff;
		std::string encData = trim(crypto->Encrypt(out.str()));
		size = encData.length();

		int sent = send(cSock, encData.c_str(), size, 0);
		bool bRetVal = sent > 0;

		return bRetVal;
	}

	bool NetSocket::Send(const char c)
	{
		std::ostringstream out;
		out << c;
		return Send(out.str());
	}

	bool NetSocket::Send(const int num)
	{
		std::ostringstream out;
		out << num;
		return Send(out.str());
	}

	bool NetSocket::SendLine(const std::string &data)
	{
		bool bRetVal = Send(data);
		if (bRetVal)
		{
			std::string endline = "\r\n";
			bRetVal = send(cSock, endline.c_str(), endline.length(), 0) > 0;
		}

		return bRetVal;
	}

	int NetSocket::Recv()
	{
		int size = 0;
		int totalSize = -1;
		std::ostringstream out;
		// Set socket to not block
		u_long iMode = 1;
		ioctlsocket(cSock, FIONBIO, &iMode);

		// Setup structure to mimick blocking so we retrieve full socket data
		bool isInRecv = true;
		bool isWaiting = true;
		int waitCount = 0;
		do
		{
			// Clear buffer
			size = recv(cSock, gBuff, MAX_BUFFER, 0);
			if (size > 0)
			{
				out << gBuff;
				memset(gBuff, 0, sizeof(gBuff));
			}

			if (size > 0 && isWaiting)
			{
				isWaiting = false;
			}
			if (size < 0 && !isWaiting)
			{
				isInRecv = false;
			}
			if (isWaiting && waitCount++ > 20000)
			{
				break;
			}
			Sleep(2);
		} while (isInRecv);

		// Clean buffer from stream
		sBuff = trim(out.str());
		// Decrypt buffer
		sBuff = crypto->Decrypt(sBuff);

		if (crypto->GetErrNo() == 0)
		{
			std::istringstream in(sBuff);
			in.getline(gBuff, MAX_BUFFER, '\n');
			iMode = 0;
			ioctlsocket(cSock, FIONBIO, &iMode);
			totalSize = sBuff.length();
		}// Endif check for error in crypto


		return totalSize;
	}

	void NetSocket::ClearSock(SOCKET sock)
	{
		// Set socket to non-blocking
		u_long iMode = 1;
		ioctlsocket(sock, FIONBIO, &iMode);
		memset(&gBuff, 0, sizeof(gBuff));
		while (recv(sock, gBuff, MAX_BUFFER, 0) >= 0);
		memset(&gBuff, 0, sizeof(gBuff));
		sBuff = "";
		// Reset socket to blocking
		iMode = 0;
		ioctlsocket(sock, FIONBIO, &iMode);
	}

	void NetSocket::ClearSock()
	{
		ClearSock(cSock);
	}

	void NetSocket::GetData(char *buff)
	{

	}

	void NetSocket::GetData(char *buff, int size)
	{

	}

	void NetSocket::GetData(char *buff, int start, int size)
	{

	}

	void NetSocket::GetData(std::string *data)
	{
		std::string line(gBuff);
		(*data) = gBuff;
	}

	std::string NetSocket::GetStr()
	{
		return sBuff;
	}

	void NetSocket::Close()
	{
		if (cSock != INVALID_SOCKET)
		{
			Send("CLOSE");
			// Give socket time to send close command
			Sleep(100);
			closesocket(cSock);
			cSock = INVALID_SOCKET;
		}
		if (crypto != NULL)
		{
			delete crypto;
			crypto = NULL;
		}

		WSACleanup();
	}


	std::string NetSocket::trim(const std::string &s)
	{
		int st = 0;
		int en = s.length() - 1;
		std::string retVal = s;
		if (en > 0)
		{
			bool btrim = true;
			do
			{
				btrim = false;
				if (s[st] == 9 || s[st] == 32 || s[st] == 10 || s[st] == 13)
				{
					st++;
					btrim = true;
				}
				if (st >= s.length())
				{
					break;
				}
			} while (btrim);

			do
			{
				btrim = false;
				if (s[en] == 9 || s[en] == 32 || s[en] == 10 || s[en] == 13 || s[en] == '\0')
				{
					btrim = true;
					en--;
				}
				if (en < 0)
				{
					break;
				}
			} while (btrim);
			en++;
			// Check to see if we have something to trim
			if (st < en)
			{
				retVal = s.substr(st, en - st);
			}
			else
			{
				retVal = "";
			}
		}// Endif valid string size check
		return retVal;
	}

	int NetSocket::GetErrNo()
	{
		return _errno;
	}

	std::string NetSocket::GetErrMsg()
	{
		return _errmsg;
	}

	void NetSocket::Sleep(int millisec)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(millisec));
	}

} }// end namespace Zaxis::Network