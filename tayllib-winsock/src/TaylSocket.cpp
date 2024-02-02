#include "tayllib.h"

TaylLib::TaylSocket::TaylSocket() {
	wsaSocket = INVALID_SOCKET;
	wsaSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (isInvalidSocket()) {
		std::cout << "Error creating socket: " << WSAGetLastError() << "\n";
		return;
	}
}

TaylLib::SocketError TaylLib::TaylSocket::bind_to() {

	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(50127);

	//127.0.0.1
	int result = bind(wsaSocket, (SOCKADDR*)&service, sizeof(service));

	if (result == SOCKET_ERROR) {
		std::cout << "Couldn't bind socket to address.";

		closesocket(wsaSocket);
		WSACleanup();

		return (TaylLib::SocketError)WSAGetLastError();
	}

	return SocketError::VALID;
}

TaylLib::SocketError TaylLib::TaylSocket::listen_to() {
	if (listen(wsaSocket, 1) == SOCKET_ERROR)
		return (SocketError)WSAGetLastError();

	return SocketError::VALID;
}

TaylLib::SocketError TaylLib::TaylSocket::accept_to(TaylSocket otherSocket) {

	accept(otherSocket.wsaSocket, NULL, NULL);

	if (wsaSocket == INVALID_SOCKET)
		return (SocketError)WSAGetLastError();

	return SocketError::VALID;
}

TaylLib::SocketError TaylLib::TaylSocket::connect_to() {

	sockaddr_in service;
	service.sin_family = AF_INET;
	InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
	service.sin_port = htons(50127);

	int result = connect(wsaSocket, (SOCKADDR*)&service, sizeof(service));

	if (result == SOCKET_ERROR)
		return (SocketError)WSAGetLastError();

	return SocketError::VALID;
}

bool TaylLib::TaylSocket::operator==(SOCKET otherSocket) {
	return wsaSocket == otherSocket;
}

void TaylLib::TaylSocket::close() {
	closesocket(wsaSocket);
}

bool TaylLib::TaylSocket::isInvalidSocket() {
	return wsaSocket == INVALID_SOCKET;
}