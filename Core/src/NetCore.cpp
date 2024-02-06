#include <winsock2.h>
#include <iostream>
#include "NetCore.h"

bool NetCore::Initialize()
{
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

	return result == 0;
}

void NetCore::Shutdown()
{
	WSACleanup();
}
