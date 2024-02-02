#include "tayllib.h"
#include <winsock2.h>
#include <iostream>

int TaylLib::WSAInit() {

	WSADATA wsaData;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != 0) {
		std::cout << "WSAStartup failed: " << iResult << std::endl;
		return 1;
	}

	return 0;
}



