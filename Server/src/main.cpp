#include <iostream>
#include "NetCore.h"

using namespace NetCore;

int main() {

	if (!NetCore::Initialize()) {
		return 0;
	}

	Socket socket;
	socket.create();

	socket.listen(IPTarget("127.0.0.1", 50270), 1);

	std::cout << "Server listening on port 50270\n";

	Socket acceptSocket;
	socket.accept(acceptSocket);

	std::cout << "Accepted new connection\n";

	char buffer[128];
	int bytesRecieved = 0;

	acceptSocket.recieve(buffer, 128, bytesRecieved);

	std::cout << buffer << '\n';

	acceptSocket.close();
	socket.close();

	std::cin.get();
}