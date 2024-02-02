#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <tchar.h>

namespace TaylLib {

	enum SocketError {
		VALID
	};

	class TaylSocket {

	private:
		SOCKET wsaSocket;

	public:

		TaylSocket();

		TaylLib::SocketError bind_to();

		TaylLib::SocketError listen_to();

		TaylLib::SocketError accept_to(TaylSocket otherSocket);

		TaylLib::SocketError connect_to();

		bool operator==(SOCKET otherSocket);

		void close();


	private:

		bool isInvalidSocket();

	};

}