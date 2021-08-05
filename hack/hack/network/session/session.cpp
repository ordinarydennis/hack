#include "session.h"

#include "../packet/packet.h"

#include <cstring>		//memcpy

namespace hack {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Session::Session() {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Session::~Session() {

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Session::RecvData(char* buff, ssize_t data_size, Packet* packet) {

	//���� ������ ���� ���ۿ� ����
	char* cur_recv_buff_pos = recv_buff_ + cur_buff_idx_;
	memcpy(cur_recv_buff_pos, buff, data_size);
	
	//���� ��ġ ����
	cur_buff_idx_ += data_size;

	//������� ���� ���� ��Ŷ ũ�� 
	recv_packet_size_ += data_size;

	ssize_t header_size = sizeof(Header);

	if (header_size > recv_packet_size_) {
		return; 
	}

	//���� ��Ŷ�� ���� ��ġ
	char* recv_packet_start_pos = recv_buff_ + cur_buff_idx_ - recv_packet_size_;

	//��� ũ�� �̻� ���� �޾Ҵٸ� ����� Ȯ���Ѵ�.
	Header header;
	memcpy(&header, recv_packet_start_pos, header_size);

	if (recv_packet_size_ < header.size_) {
		return;
	}

	packet->header_ = header;

	char* recv_packet_body_start_pos = recv_packet_start_pos + header_size;

	//��Ŷ�� ��� �޾Ҵٸ� ��� �����͸� ť�� �ִ´�. 
	//*packet = reinterpret_cast<Packet*>(recv_packet_start_pos);
	packet->body_ = reinterpret_cast<char*>(recv_packet_body_start_pos);

	recv_packet_size_ = 0;

	//��� ������ �ܷ��� �� ���� �ʾҴٸ� write ��ġ�� �ʱ�ȭ �Ѵ�.
	//1024 �� ��Ŷ�� �ִ� ũ��
	//todo ����� �� �𸣰ڴ� �ٽ� ����
	if (kMaxSessionRecvBuffSize <= cur_buff_idx_ + 1024)
	{
		cur_buff_idx_ = 0;
	}
}
}; //namespace hack