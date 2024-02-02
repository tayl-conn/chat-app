#include <iostream>
#include "tayllib.h"

#define Socket TaylLib::TaylSocket

int main() {

	TaylLib::WSAInit();

	Socket serverSocket = Socket::TaylSocket();
	serverSocket.bind_to();
	serverSocket.listen_to();

	Socket acceptSocket = Socket::TaylSocket();

	std::cout << "Waiting for connection...\n";

	do {
		acceptSocket.accept_to(serverSocket);
	} while (acceptSocket == INVALID_SOCKET);

	std::cout << "Got a connection!\n";

	serverSocket.close();
	WSACleanup();

	std::cin.get();
}