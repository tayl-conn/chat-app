#include <iostream>
#include "NetCore.h"

using namespace NetCore;

int main() {

	if (!NetCore::Initialize()) {
		std::cerr << "Failed to initalize NetCore...\n";
		return 0;
	}

	Socket socket;
	socket.create();
	socket.connect(IPTarget("127.0.0.1", 50270));

	std::string message = "Hello!\0";
	int bytesSent = 0;
	socket.send(message.data(), message.size(), bytesSent);
	std::cout << "Sent " << bytesSent << " bytes!";

	socket.close();
	std::cin.get();
}