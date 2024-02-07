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

	while (true) {

		char buffer[128];
		int bytesRecieved = 0;
		acceptSocket.recieve(buffer, 128, bytesRecieved);

		if (bytesRecieved == 0 || bytesRecieved == SOCKET_ERROR)
			break;

		printf("%s\n", buffer);
	}

	acceptSocket.close();
	socket.close();

	std::cin.get();
}