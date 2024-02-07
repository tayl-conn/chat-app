#include "ChatServer.h"
#include <iostream>

using NetCore::NetResult;

bool ChatServer::Start(NetCore::IPTarget target)
{
	listenSocket = NetCore::Socket(target.getIPVersion());

	if (listenSocket.create() != NetResult::Success) {
		std::cerr << "Failed to create the listening socket.\n";
		shutdown();
		return false;
	}

	if (listenSocket.listen(NetCore::IPTarget("127.0.0.1", 50270), 5) != NetResult::Success) {
		std::cerr << "Failed to start listening on port 50270.\n";
		shutdown();
		return false;
	}

	std::cout << "Server listening on port 50270.\n";

	WSAPOLLFD listeningSocketFD = {};
	listeningSocketFD.fd = listenSocket.getHandle();
	listeningSocketFD.events = POLLRDNORM;
	listeningSocketFD.revents = 0;
	fd_set.emplace_back(listeningSocketFD);

	return true;
}

void ChatServer::shutdown()
{
	NetCore::Shutdown();
	std::cout << "Shutting down...\n";
}

void ChatServer::tick()
{
	if (WSAPoll(fd_set.data(), fd_set.size(), 1) > 0) {

		if (fd_set[0].revents & POLLRDNORM) {
			NetCore::Socket newConnection;

			if (listenSocket.accept(newConnection) == NetResult::Success) {
				std::cout << "New connection accepted!\n";

				WSAPOLLFD fd = {};
				fd.fd = newConnection.getHandle();
				fd.events = POLLRDNORM;
				fd.revents = 0;
				fd_set.emplace_back(fd);
				connections.emplace_back(NetCore::TCPClient(newConnection));
			}
		}

		for (int i = 1; i < fd_set.size(); i++) {

			WSAPOLLFD fd = fd_set[i];

			if ((fd.revents & POLLERR) || (fd.revents & POLLHUP) || (fd.revents & POLLNVAL)) {
				closeConnection(i);
				i--;
				std::cout << "Lost connection to client.\n";
				continue;
			}

		}

	}

}

void ChatServer::closeConnection(int fileDescriptorIndex) {
	NetCore::TCPClient tcpClient = connections[fileDescriptorIndex - 1];
	connections.erase(connections.begin() + fileDescriptorIndex - 1);
	fd_set.erase(fd_set.begin() + fileDescriptorIndex);
	tcpClient.socket.close();
}
