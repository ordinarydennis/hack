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

	//받은 데이터 수신 버퍼에 복사
	char* cur_recv_buff_pos = recv_buff_ + cur_buff_idx_;
	memcpy(cur_recv_buff_pos, buff, data_size);
	
	//다음 위치 세팅
	cur_buff_idx_ += data_size;

	//현재까지 수신 받은 패킷 크기 
	recv_packet_size_ += data_size;

	ssize_t header_size = sizeof(Header);

	if (header_size > recv_packet_size_) {
		return; 
	}

	//수신 패킷의 시작 위치
	char* recv_packet_start_pos = recv_buff_ + cur_buff_idx_ - recv_packet_size_;

	//헤더 크기 이상 수신 받았다면 헤더를 확인한다.
	Header header;
	memcpy(&header, recv_packet_start_pos, header_size);

	if (recv_packet_size_ < header.size_) {
		return;
	}

	packet->header_ = header;

	char* recv_packet_body_start_pos = recv_packet_start_pos + header_size;

	//패킷을 모두 받았다면 헤더 포인터를 큐에 넣는다. 
	//*packet = reinterpret_cast<Packet*>(recv_packet_start_pos);
	packet->body_ = reinterpret_cast<char*>(recv_packet_body_start_pos);

	recv_packet_size_ = 0;

	//사용 버퍼의 잔량이 얼마 남지 않았다면 write 위치를 초기화 한다.
	//1024 한 패킷의 최대 크기
	//todo 여기는 잘 모르겠다 다시 보자
	if (kMaxSessionRecvBuffSize <= cur_buff_idx_ + 1024)
	{
		cur_buff_idx_ = 0;
	}
}
}; //namespace hack