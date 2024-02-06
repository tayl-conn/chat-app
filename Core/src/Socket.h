#pragma once

#include "SocketHandle.h"
#include "NetResult.h"
#include "IPVersion.h"
#include "IPTarget.h"

namespace NetCore {

	class Socket {

	private:

		SocketHandle handle = INVALID_SOCKET;
		IPVersion ipVersion = IPVersion::IPv4;

	public:

		Socket(IPVersion ipVersion = IPVersion::IPv4, SocketHandle handle = INVALID_SOCKET);

		NetResult create();
		NetResult close();
		NetResult bind(IPTarget target);
		NetResult listen(IPTarget target, int backlog);
		NetResult accept(Socket& out);
		NetResult connect(IPTarget target);
		NetResult send(const void* buffer, int numberOfBytesToSend, int& outBytesSent);
		NetResult recieve(const void* buffer, int numberOfBytesToRead, int& outBytesRecieved);

	};

}