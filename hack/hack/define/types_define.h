#pragma once


namespace hack {

	//todo type name �빮�� ?

	using Fd = uint32_t;

	using Port = uint16_t;
	//todo �̰� enum���� ���ǵ� ���� �������
	using PacketId = uint16_t;

	using SendBufSize = uint16_t;

	//todo �̰� ��ġ ����??
	using SendHelperFp = std::function<void(const Fd fd, const char* buf, const SendBufSize size)>;

};
 