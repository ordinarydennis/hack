//Related header
#include "network.h"

//C system headers
#include <sys/socket.h>		//socket
#include <netinet/in.h>		//sockaddr_in
#include <fcntl.h>			//non blocking
#include <sys/epoll.h>		//epoll
#include <unistd.h>			// close build error solution
#include <errno.h>			//errno
#include <pthread.h>
//C++ standard library headers
//#include <>
//other libraries' headers
//#include <>

//your project's headers.
#include "session/session.h"
#include "network_config.h"

namespace hack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//todo 적절한 위치로 이동
void SendHelper(const Fd fd, const char* buf, const uint16_t size) {

	Log("SendHelper fd {}", fd);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Network::Network(uint32_t count_of_processor) 
	:count_of_processor_(count_of_processor) {

	event_ = new epoll_event;
	epoll_event_list_ = new epoll_event[kMaxEvents];
	thread_id_list_ = new pthread_t[count_of_processor];
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Network::~Network() {

	if (nullptr != event_) {
		delete event_;
	}

	if (nullptr != epoll_event_list_) {
		delete[] epoll_event_list_;
	}

	if (nullptr != thread_id_list_) {
		delete[] thread_id_list_;
	}

	DistroyThread(count_of_processor_);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Network::Init(uint16_t port) {

	listen_socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_socket_ == -1) {
		//ShowLog("Could not create socket");
		//todo 에러 번호로 반환 하도록 수정
		return false;
	}

	if (false == Bind(listen_socket_, port))
		return false;

	if (false == MakeSocketNonBlocking(listen_socket_))
		return false;

	if (-1 == listen(listen_socket_, kListenSize))
		return false;

	epoll_ = epoll_create1(0);
	if (epoll_ == -1) {
		return false;
	}

	RegisterEpollEvnet(listen_socket_, EPOLLIN | EPOLLET);

	CreateThread(count_of_processor_);

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Network::Run() {

	EpollWait();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Network::AddPacketHandler(PacketId packet_id, PacketHandler h)
{
	//네트워크에 등록
	packet_handler_map_.emplace(packet_id, h);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Network::Bind(const int socket, uint16_t port) {

	sockaddr_in sock_addr_in;
	sock_addr_in.sin_family = AF_INET;
	sock_addr_in.sin_addr.s_addr = INADDR_ANY;
	sock_addr_in.sin_port = htons(port);
	if (0 > bind(listen_socket_, (struct sockaddr*)&sock_addr_in, sizeof(sock_addr_in))) {
		//ShowLog("bind failed");
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Network::Accept() {

	do {
		struct sockaddr in_addr;
		socklen_t in_len = sizeof(in_addr);

		int client_socket = accept(listen_socket_, &in_addr, &in_len);
		if (client_socket == -1) {
			if (errno == EAGAIN || errno == EWOULDBLOCK) { // Done processing incoming connections
				break;
			}
			else {
				//ShowLog("[E] accept failed");
				break;
			}
		}
			
		if (!MakeSocketNonBlocking(client_socket)) {
			//ShowLog("[E]  MakeSocketNonBlocking failed");
			break;
		}

		auto session = new Session;
		session->SetFD(client_socket);
		event_->data.ptr = session;
		event_->events = EPOLLIN | EPOLLET;
		if (epoll_ctl(epoll_, EPOLL_CTL_ADD, client_socket, event_) == -1) {
			//std::cerr << "[E] epoll_ctl failed\n";
			break;
		}
	} while (true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Network::MakeSocketNonBlocking(int socket) {
	
	int flags = fcntl(socket, F_GETFL, 0);
	if (flags == -1) {
		//std::cerr << "[E] fcntl failed (F_GETFL)\n";
		return false;
	}

	flags |= O_NONBLOCK;
	int s = fcntl(socket, F_SETFL, flags);
	if (s == -1) {
		//std::cerr << "[E] fcntl failed (F_SETFL)\n";
		return false;
	}

	return true;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Network::RegisterEpollEvnet(const int socket, const uint32_t event) {

	event_->data.fd = socket;
	event_->events = event;

	if (epoll_ctl(epoll_, EPOLL_CTL_ADD, socket, event_) == -1) {
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Network::CreateThread(const uint32_t count_of_processor) {

	bool isSuccess = true;

	for (uint32_t i = 0; i < count_of_processor; i++) {
		int err = pthread_create(&thread_id_list_[i], NULL, ProcessPacket, this);
		// Check if thread is created sucessfuly
		if (err)
		{
			//std::cout << "Thread creation failed : " << strerror(err);
			//return err;
			isSuccess = false;
			break;
		}
	}

	return isSuccess;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Network::DistroyThread(const uint32_t count_of_processor) {

	for (uint32_t i = 0; i < count_of_processor; i++) {
		pthread_join(thread_id_list_[i], NULL);
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Network::RecvPacket(const int& epoll, epoll_event* event) {

	//todo 여기도 다시 분석
	auto session = static_cast<Session*>(event->data.ptr);
	auto socket = session->FD();

	ssize_t read_size = 0;

	do {

		char buf[kMaxNetworkRecvBuffSize] = { 0, };
		read_size = read(socket, buf, kMaxNetworkRecvBuffSize);
		if (-1 == read_size) {

			//todo print errno 
			if (errno == EAGAIN) {
				// if errno == EAGAIN, read all data
				break;
			} else {
				// this is other error, so Exit the loop
				break;
			}

		} else if (0 == read_size) { // EOF - remote closed connection

			epoll_ctl(epoll, EPOLL_CTL_DEL, socket, NULL);
			close(socket);

			if (nullptr != session) {
				delete session;
			}

			break;
		}
		
		//Packet* p = nullptr;
		Packet p;
		p.fd_ = socket;
		session->RecvData(buf, read_size, &p);

		if (nullptr != p.body_){
			packet_queue_.Push(p);
		}

	} while (true);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Network::SendPacket(const Fd fd, const char* buf, const uint16_t size) {

	auto send_size = write(fd, buf, size);

	if (-1 == send_size)
	{
		//todo log
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Network::EpollWait() {
	
	do{

		auto n = epoll_wait(epoll_, epoll_event_list_, kMaxEvents, -1);

		for (int i = 0; i < n; ++i) {

			auto epoll_event = epoll_event_list_[i];

			if (epoll_event.events & EPOLLERR ||
				epoll_event.events & EPOLLHUP ||
				!(epoll_event.events & EPOLLIN)) { // error

				close(epoll_event_list_[i].data.fd);
			}
			else if (listen_socket_ == epoll_event_list_[i].data.fd) { // new connection
				Accept();
			}
			else { // data to read
				RecvPacket(epoll_, &epoll_event);
			}
		}

	} while (true);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void* Network::ProcessPacket(void* args) {
	
	Network* net = reinterpret_cast<Network*>(args);

	do {

		auto p = net->packet_queue_.Pop();
		if (std::nullopt == p) {
			continue;
		}

		auto packet = p.value();

		auto it = net->packet_handler_map_.find(packet.header_.packet_id_);
		if (net->packet_handler_map_.end() != it) {

			it->second(SendHelper, packet);

		}

		//Sleep?

	} while (true);

	return nullptr;
}
//
}; // namespace hack