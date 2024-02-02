#include <iostream>
#include "tayllib.h"

int main() {

	TaylLib::WSAInit();

	TaylLib::TaylSocket clientSocket = TaylLib::TaylSocket();
	std::cout << clientSocket.connect_to();

	std::cin.get();
}