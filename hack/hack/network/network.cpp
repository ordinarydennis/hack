#include "network.h"

#include <sys/socket.h>		//socket
#include <netinet/in.h>		//sockaddr_in
#include <fcntl.h>			//non blocking
#include <sys/epoll.h>		//epoll
#include <unistd.h>			// close build error solution

namespace hack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Network::Network() {

	event_ = new epoll_event;
	epoll_event_list_ = new epoll_event[kMaxEvents];
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Network::~Network() {

	if (nullptr == event_) {
		delete event_;
		event_ = nullptr;
	}

	if (nullptr == epoll_event_list_) {
		delete[] epoll_event_list_;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Network::Init(uint16_t port) {

	socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_ == -1) {
		//ShowLog("Could not create socket");
		//todo 에러 번호로 반환 하도록 수정
		return false;
	}

	if (false == Bind(socket_, port))
		return false;

	if (false == MakeSocketNonBlocking(socket_))
		return false;

	if (-1 == listen(socket_, kListenSize))
		return false;

	epoll_ = epoll_create1(0);
	if (epoll_ == -1) {
		return false;
	}

	RegisterEpollEvnet(socket_, EPOLLIN | EPOLLET);

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Network::Run() {

	while (true) {
		
		auto n = epoll_wait(epoll_, epoll_event_list_, kMaxEvents, -1);

		for (int i = 0; i < n; ++i) {

			auto epoll_event = epoll_event_list_[i];

			if (epoll_event.events & EPOLLERR ||
				epoll_event.events & EPOLLHUP ||
				!(epoll_event.events & EPOLLIN)) { // error

				close(epoll_event_list_[i].data.fd);
			}
			else if (socket_ == epoll_event_list_[i].data.fd) { // new connection
				//while (Accept(socket_, event_, epoll_fd_)) {}
			}
			else { // data to read
				RecvPacket(&epoll_event);
			}
		}

	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Network::Bind(const int socket, uint16_t port) {

	sockaddr_in sock_addr_in;
	sock_addr_in.sin_family = AF_INET;
	sock_addr_in.sin_addr.s_addr = INADDR_ANY;
	sock_addr_in.sin_port = htons(port);
	if (0 > bind(socket_, (struct sockaddr*)&sock_addr_in, sizeof(sock_addr_in))) {
		//ShowLog("bind failed");
		return false;
	}

	return true;
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
void Network::RecvPacket(epoll_event* event) {

	//auto session = static_cast<ClientSession*>(event.data.ptr);
	//auto socket = session->FD();

	//ssize_t read_size = 0;

	//while (1) {

	//	char buf[kMaxReadSize] = { 0, };
	//	read_size = read(socket, buf, kMaxReadSize);

	//	if (read_size == -1) {

	//		if (errno == EAGAIN) {
	//			// if errno == EAGAIN, read all data
	//		}
	//		else {
	//			// this is other error, so Exit the loop
	//			break;
	//		}

	//	}
	//	else if (read_size == 0) { // EOF - remote closed connection

	//		if (nullptr != session) {
	//			delete session;
	//		}

	//		close(socket);

	//		break;
	//	}

	//	session->RecvData(buf, read_size);

	//}

}
//
}; // namespace hack