#pragma once
//#include 

#include "../../headers/common_headers.h"

namespace hack {

	using PacketId = uint16_t;

#pragma pack(push, 1)

struct Header {
	uint16_t size_ = 0;
	PacketId packet_id_ = 0;
};

struct Packet {
	Header		header_;
	
	//char body_[MAX_SOCKBUF] = { 0, };

	//stPacket(UINT32 ClientFrom, UINT32 ClientTo, stPacketHeader Header, const char* Body, size_t size)
	//{
	//	mClientFrom = ClientFrom;
	//	mClientTo = ClientTo;
	//	mHeader = Header;
	//	memcpy_s(mBody, size, Body, size);
	//}

	//size_t GetBodySize() const
	//{
	//	return mHeader.mSize - PACKET_HEADER_SIZE;
	//}
};

#pragma pack(pop)
}