#pragma once 

#include "PacketType.h"
#include <vector>

namespace NetCore {

	class Packet {

	private:

		PacketType packetType;
		std::vector<uint8_t> buffer;
		uint32_t extractionCursor;

	public:

		Packet(PacketType packetType = PacketType::NC_None);

		Packet& operator<<(uint32_t data);
		Packet& operator>>(uint32_t& dataToWriteTo);

	private:

		void Append(const void* data, uint32_t sizeOfDataInBytes);

	};

}
