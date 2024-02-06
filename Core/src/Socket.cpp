#include "Socket.h"
#include <iostream>

namespace NetCore {

	Socket::Socket(IPVersion ipVersion, SocketHandle handle)
		: ipVersion(ipVersion), handle(handle)
	{

	}

	NetResult Socket::create()
	{
		handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (handle == INVALID_SOCKET) {
			return NetResult::NotImplemented;
		}

		return NetResult::Success;
	}

	NetResult Socket::close() {

		if (handle == INVALID_SOCKET) {
			return NetResult::NotImplemented;
		}

		int result = closesocket(handle);

		if (result != 0) {
			int error = WSAGetLastError();
			return NetResult::NotImplemented;
		}

		handle = INVALID_SOCKET;

		return NetResult::Success;
	}

	NetResult Socket::bind(IPTarget target)
	{
		sockaddr_in addr_in = target.getSockAddrIPv4();

		int result = ::bind(handle, (sockaddr*)(&addr_in), sizeof(sockaddr_in));

		if (result != 0) {
			int error = WSAGetLastError();
			std::cout << error;
			return NetResult::NotImplemented;
		}

		return NetResult::Success;
	}

	NetResult Socket::listen(IPTarget target, int backlog)
	{

		if (bind(target) != NetResult::Success) {
			return NetResult::NotImplemented;
		}

		int result = ::listen(handle, backlog);

		if (result != 0) {
			int error = WSAGetLastError();
			return NetResult::NotImplemented;
		}

		return NetResult::Success;
	}

	NetResult Socket::accept(Socket& out)
	{

		SocketHandle acceptedSocketHandle = ::accept(handle, nullptr, nullptr);

		if (acceptedSocketHandle == INVALID_SOCKET) {
			int error = WSAGetLastError();
			return NetResult::NotImplemented;
		}

		out = Socket(IPVersion::IPv4, acceptedSocketHandle);
		return NetResult::Success;
	}

	NetResult Socket::connect(IPTarget target)
	{

		sockaddr_in addr_in = target.getSockAddrIPv4();
		int result = ::connect(handle, (sockaddr*)&addr_in, sizeof(sockaddr_in));

		if (result != 0) {
			int error = WSAGetLastError();
			return NetResult::NotImplemented;
		}

		return NetResult::Success;
	}

	NetResult Socket::send(const void* buffer, int numberOfBytesToSend, int& outBytesSent)
	{
		int numberOfBytesSent = ::send(handle, (const char*)buffer, numberOfBytesToSend, NULL);

		if (numberOfBytesSent == SOCKET_ERROR) {
			int error = WSAGetLastError();
			outBytesSent = 0;
			return NetResult::NotImplemented;
		}

		outBytesSent = numberOfBytesSent;

		return NetResult::Success;
	}

	NetResult Socket::recieve(const void* buffer, int numberOfBytesToRead, int& outBytesRecieved)
	{
		int numberOfBytesRecieved = recv(handle, (char*)buffer, numberOfBytesToRead, NULL);

		if (numberOfBytesRecieved == SOCKET_ERROR) {
			int error = WSAGetLastError();
			outBytesRecieved = 0;
			return NetResult::NotImplemented;
		}

		outBytesRecieved = numberOfBytesRecieved;
		return NetResult::Success;
	}

}