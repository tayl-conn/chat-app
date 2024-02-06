#include "IPTarget.h"

namespace NetCore {
	IPTarget::IPTarget(const char* ip, unsigned short port)
		: port(port)
	{

		in_addr addr;
		int result = inet_pton(AF_INET, ip, &addr);

		if (result == 0) { //Invalid decimal-dotted ipv4 address
			return;
		}

		if (result == -1) { // WSA Error
			return;
		}

		this->ip = ip;
		hostname = ip;
		ipVersion = IPVersion::IPv4;

		ipBytes.resize(sizeof(unsigned long));
		memcpy(&ipBytes[0], &addr.S_un.S_addr, sizeof(unsigned long));

	}

	IPVersion IPTarget::getIPVersion()
	{
		return ipVersion;
	}

	std::string IPTarget::getHostname()
	{
		return hostname;
	}

	std::string IPTarget::getIPString()
	{
		return ip;
	}

	unsigned short IPTarget::getPort()
	{
		return port;
	}

	std::vector<uint8_t> IPTarget::getIPBytes()
	{
		return ipBytes;
	}

	sockaddr_in NetCore::IPTarget::getSockAddrIPv4()
	{
		sockaddr_in addrInfo = {};
		memcpy(&addrInfo.sin_addr, &ipBytes[0], sizeof(unsigned long));
		addrInfo.sin_family = AF_INET;
		addrInfo.sin_port = htons(port);

		return addrInfo;
	}
}
