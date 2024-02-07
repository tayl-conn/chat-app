#include <iostream>
#include "NetCore.h"
#include "ChatServer.h"

using namespace NetCore;

int main() {

	if (!NetCore::Initialize()) {
		return 0;
	}

	ChatServer chatServer;

	if (!chatServer.Start(IPTarget("127.0.0.1", 50270))) {
		return 0;
	}

	while (true) {
		chatServer.tick();
	}

}