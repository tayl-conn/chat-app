#pragma once

#include "NetCore.h"
#include <vector>
#include "TCPClient.h"

class ChatServer {

private:
	NetCore::Socket listenSocket;
	std::vector<WSAPOLLFD> fd_set;
	std::vector<NetCore::TCPClient> connections;

public:
	bool Start(NetCore::IPTarget target);
	void shutdown();
	void tick();

private:
	void closeConnection(int fileDescriptorIndex);

};
