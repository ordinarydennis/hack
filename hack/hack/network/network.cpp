//Related header
#include "network.h"
#include "session/session.h"
#include "network_config.h"
//C system headers
#include <sys/socket.h>		//socket
#include <netinet/in.h>		//sockaddr_in
#include <fcntl.h>			//non blocking
#include <sys/epoll.h>		//epoll
#include <unistd.h>			// close build error solution
#include <errno.h>			//errno
//C++ standard library headers
//#include <>
//other libraries' headers
//#include <>


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
			else if (listen_socket_ == epoll_event_list_[i].data.fd) { // new connection
				Accept();
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
void Network::RecvPacket(epoll_event* event) {

	//여기도 다시 분석
	auto session = static_cast<Session*>(event->data.ptr);
	auto socket = session->FD();

	ssize_t read_size = 0;

	do {
		char buf[kMaxNetworkRecvBuffSize] = { 0, };
		read_size = read(socket, buf, kMaxNetworkRecvBuffSize);
		if (-1 == read_size) {

			if (errno == EAGAIN) {
				// if errno == EAGAIN, read all data
			} else {
				// this is other error, so Exit the loop
				break;
			}

		} else if (0== read_size) { // EOF - remote closed connection

			if (nullptr != session) {
				delete session;
			}
			close(socket);
			break;
		}
		
		session->RecvData(buf, read_size);

	} while (true);

}
//
}; // namespace hack