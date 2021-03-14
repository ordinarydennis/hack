#pragma once
//
#include "../headers/common_headers.h"
#include "../define/common_define.h"
//
//#include <>
//
//
struct epoll_event;
//
namespace hack {
//
class Network {
	//types.. (typdef, using nest stucts and classes)
public:


	//constants
public:


	//factory functions, constructors and assignment operators, destructor
public:
	Network();
	~Network();


	//all other methods
	bool Init(uint16_t port);
	void Run();


public:
	//getters

	//setters

	//other methods

	//data members


private:
	//private methods
	bool Bind(const int socket, const uint16_t port);
	bool MakeSocketNonBlocking(const int socket);
	bool RegisterEpollEvnet(const int socket, const uint32_t event);
	void RecvPacket(epoll_event* event);


private:
	//private types


private:
	//private constants
	uint16_t kListenSize = 5;
	uint16_t kMaxEvents = 1000;


private:
	//private data members
	int socket_ = INVALID_FD;
	int epoll_ = INVALID_FD;
	epoll_event* event_ = nullptr;
	epoll_event* epoll_event_list_ = nullptr;


};
//class Network
}; //namespace hack