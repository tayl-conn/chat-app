#pragma once

#include "IPVersion.h"
#include <string>
#include <Ws2tcpip.h>
#include <vector>

namespace NetCore {

	class IPTarget {

	private:

		IPVersion ipVersion = IPVersion::Unassigned;
		std::string hostname = "";
		std::string ip = "";
		unsigned short port = 0;
		std::vector<uint8_t> ipBytes;

	public:

		IPTarget(const char* ip, unsigned short port);

		IPVersion getIPVersion();
		std::string getHostname();
		std::string getIPString();
		unsigned short getPort();
		std::vector<uint8_t> getIPBytes();

		sockaddr_in getSockAddrIPv4();

	};




}
