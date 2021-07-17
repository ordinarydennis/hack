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
void Session::RecvData(char* buff, ssize_t data_size) {

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

	//��� ũ�� �̻� ���� �޾Ҵٸ� ����� Ȯ���Ѵ�.
	Header header;
	memcpy(&header, cur_recv_buff_pos - recv_packet_size_, header_size);

	//�ٵ� ������ Ȯ��
	ssize_t body_size = recv_packet_size_ - header_size;
	if (body_size < header.size_) {
		return;
	}

	//��Ŷ�� ��� �޾Ҵٸ� ��� �����͸� ť�� �ִ´�. 
	//Packet* packet = reinterpret_cast<Packet*>(cur_recv_buff_pos - recv_packet_size_);

	//��Ŷ �ڵ鷯�� �ѱ�� 

	recv_packet_size_ = 0;

	//��� ������ �ܷ��� �� ���� �ʾҴٸ� write ��ġ�� �ʱ�ȭ �Ѵ�.
	//1024 �� ��Ŷ�� �ִ� ũ��
	//todo ����� �� �𸣰ڴ� �ٽ� ����
	//todo ���� ť�� �������
	if (kMaxSessionRecvBuffSize <= cur_buff_idx_ + 1024)
	{
		cur_buff_idx_ = 0;
	}
}
}; //namespace hack