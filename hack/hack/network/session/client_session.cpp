#include "client_session.h"

//#include "packets.h"

#include <cstring>		//memcpy

namespace hack {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClientSession::ClientSession() {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ClientSession::~ClientSession() {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClientSession::RecvData(char* buff, ssize_t data_size) {

	memcpy(recv_buff_ + cur_buff_position_, buff, data_size);
	
	//���� ��ġ ����
	cur_buff_position_ += data_size;

	//������� ���� ���� ��Ŷ ũ�� 
	//recv_packet_size_ += data_size;

	//ssize_t header_size = sizeof(Header);
	//if (header_size > recv_packet_size_) {
	//	return; 
	//}

	////��� ũ�� �̻� ���� �޾Ҵٸ� ����� Ȯ���Ѵ�.
	//Header header;
	//memcpy(&header, recv_buff_ - recv_packet_size_, header_size);

	////�ٵ� ������ Ȯ��
	//ssize_t body_size = recv_packet_size_ - header_size;
	//if (body_size < header.body_size) {
	//	return;
	//}

	////��Ŷ�� ��� �޾Ҵٸ� ��� �����͸� ť�� �ִ´�. 
	////Packet* packet = reinterpret_cast<Packet*>(recv_buff_ - recv_packet_size_);
	//

	//recv_packet_size_ = 0;

	////��� ������ �ܷ��� �� ���� �ʾҴٸ� write ��ġ�� �ʱ�ȭ �Ѵ�.
	////1024 �� ��Ŷ�� �ִ� ũ��
	//if (kMaxSessionRecvBuffSize <= cur_buff_position_ + 1024)
	//{
	//	cur_buff_position_ = 0;
	//}
}
}; //namespace hack