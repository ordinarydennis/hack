#pragma once


namespace hack {

	//todo type name 대문자 ?

	using Fd = uint32_t;

	using Port = uint16_t;
	//todo 이거 enum으로 쓸건데 뺄지 고민하자
	using PacketId = uint16_t;

	using SendBufSize = uint16_t;

	//todo 이거 위치 어디로??
	using SendHelperFp = std::function<void(const Fd fd, const char* buf, const SendBufSize size)>;

};
 