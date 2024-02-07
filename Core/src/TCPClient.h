#pragma once

#include "Socket.h"

namespace NetCore {

	class TCPClient {

	public:

		TCPClient(NetCore::Socket socket);

		NetCore::Socket socket;
		char buffer[1024];

	};

}
