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

	//헤더 크기 이상 수신 받았다면 헤더를 확인한다.
	Header header;
	memcpy(&header, cur_recv_buff_pos - recv_packet_size_, header_size);

	//바디 사이즈 확인
	ssize_t body_size = recv_packet_size_ - header_size;
	if (body_size < header.size_) {
		return;
	}

	//패킷을 모두 받았다면 헤더 포인터를 큐에 넣는다. 
	//Packet* packet = reinterpret_cast<Packet*>(cur_recv_buff_pos - recv_packet_size_);

	//패킷 핸들러에 넘기기 

	recv_packet_size_ = 0;

	//사용 버퍼의 잔량이 얼마 남지 않았다면 write 위치를 초기화 한다.
	//1024 한 패킷의 최대 크기
	//todo 여기는 잘 모르겠다 다시 보자
	//todo 원형 큐를 사용하자
	if (kMaxSessionRecvBuffSize <= cur_buff_idx_ + 1024)
	{
		cur_buff_idx_ = 0;
	}
}
}; //namespace hack