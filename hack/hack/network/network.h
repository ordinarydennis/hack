#pragma once
//Group similar declarations together, placing public parts earlier.
//A class definition should usually start with a public: section, followed by protected:, 
//then private:.Omit sections that would be empty.
//Within each section, prefer grouping similar kinds of declarations together, and prefer the following order : 
//types(including typedef, using, and nested structsand classes), constants, factory functions, constructors and 
//assignment operators, destructor, all other methods, data members.
//Do not put large method definitions inline in the class definition. Usually, only trivial or performance - critical, 
//and very short, methods may be defined inline.See Inline Functions for more details.

//Include headers in the following order : Related header, C system headers, C++ standard library headers, 
//other libraries' headers, your project's headers.

//Related header,
#include "../headers/common_headers.h"
#include "../define/common_define.h"
//C system headers
//#include <>
//C++ standard library headers
//#include <>
//other libraries' headers
//#include "../define/common_define.h"

struct epoll_event;
//
namespace hack {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Network {
//types(including typedef, using, and nested structsand classes)
public:


//constants
public:


//factory functions, constructors and assignment operators, destructor
public:
	Network();
	~Network();


//all other methods
public:
	//basic methods(init, run, destroy..)
	bool Init(uint16_t port);
	void Run();
	//other methods
	//getters
	//setters


//private types
private:

	
//private constants
private:
	uint16_t kListenSize = 5;
	uint16_t kMaxEvents = 1000;


//private methods	
private:
	bool Bind(const int socket, const uint16_t port);
	void Accept();
	bool MakeSocketNonBlocking(const int socket);
	bool RegisterEpollEvnet(const int socket, const uint32_t event);
	void RecvPacket(epoll_event* event);


//data members	
private:
	int listen_socket_ = INVALID_FD;
	int epoll_ = INVALID_FD;
	epoll_event* event_ = nullptr;
	epoll_event* epoll_event_list_ = nullptr;


};
//class Network
}; //namespace hack