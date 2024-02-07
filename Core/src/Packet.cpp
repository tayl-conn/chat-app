#include "Packet.h"

#define W32_LEAN_AND_MEAN
#include <Winsock2.h>

namespace NetCore {

	Packet::Packet(PacketType packetType)
		: packetType(packetType), extractionCursor(0)
	{

	}

	Packet& Packet::operator<<(uint32_t data) {
		data = htonl(data);
		Append(&data, sizeof(uint32_t));
		return *this;
	}

	Packet& Packet::operator>>(uint32_t& dataToWriteTo)
	{
		dataToWriteTo = ntohl(*reinterpret_cast<uint32_t*>(&buffer[extractionCursor]));
		extractionCursor += sizeof(uint32_t);
		return *this;
	}

	void Packet::Append(const void* data, uint32_t sizeOfDataInBytes)
	{
		buffer.insert(buffer.end(), (char*)data, (char*)data + sizeOfDataInBytes);
	}

}
