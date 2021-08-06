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

//Related header(class.h, class.cpp)
//#include <>

//C system headers
//#include <>

//C++ standard library headers
#include <unordered_map>

//other libraries' headers
//#include <>

//your project's headers.
#include "../headers/common_headers.h"
#include "../utils/tsqueue/tsqueue.h"
#include "packet/packet.h"

struct epoll_event;
//
namespace hack {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SendHelper(const Fd fd, const char* buf, const SendBufSize size);

class Network {
//types(including typedef, using, and nested structsand classes)
public:
	//todo SendHelperFp 이거 이름 더 좋은걸로 바꾸자
	using PacketHandler = std::function<void(SendHelperFp, const Packet* p)>;
	using FdPacketPair = std::pair<Fd, Packet*>;

//constants
public:


//factory functions, constructors and assignment operators, destructor
public:
	explicit Network(uint32_t count_of_processor);

	~Network();


//all other methods
public:
	//basic methods(init, run, destroy..)
	bool Init(uint16_t port);

	void Run();

	//other methods
	void AddPacketHandler(PacketId packet_id, PacketHandler h);

	//getters
	
	//setters


//private types
private:

	
//private constants
private:


//private static methods
private:
	static void* ProcessPacket(void*);


//private static data members
private:



//private methods	
private:
	bool Bind(const int socket, const uint16_t port);

	void Accept();

	bool MakeSocketNonBlocking(const int socket);

	bool RegisterEpollEvnet(const int socket, const uint32_t event);

	bool CreateThread(const uint32_t count_of_processor);

	void DistroyThread(const uint32_t count_of_processor);

	void RecvPacket(const int& epoll, epoll_event* event);

	void EpollWait();


//private data members	
private:
	int listen_socket_ = INVALID_FD;

	int epoll_ = INVALID_FD;

	uint32_t count_of_processor_ = 0;

	epoll_event* event_ = nullptr;

	epoll_event* epoll_event_list_ = nullptr;

	pthread_t* thread_id_list_ = nullptr;

	TSQueue<FdPacketPair> packet_queue_;

	std::unordered_map<PacketId, PacketHandler>	packet_handler_map_;


};
//class Network
}; //namespace hack