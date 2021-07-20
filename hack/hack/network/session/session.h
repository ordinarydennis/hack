#pragma once
//Group similar declarations together, placing public parts earlier.
//A class definition should usually start with a public: section, followed by protected:, 
//then private:.Omit sections that would be empty.
//Within each section, prefer grouping similar kinds of declarations together, and prefer the following order : 
//types(including typedef, using, and nested structsand classes), constants, factory functions, constructors and 
//assignment operators, destructor, all other methods, data members.
//Do not put large method definitions inline in the class definition. Usually, only trivial or performance - critical, 
//and very short, methods may be defined inline.See Inline Functions for more details.
//#include ""
#include "../../headers/common_headers.h"
#include "session_config.h"
//
//#include <>
//
//
namespace hack {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Packet;

class Session {
//types.. (typdef, using nest stucts and classes)
public:


//constants
public:


//factory functions, constructors and assignment operators, destructor
public:
	Session();
	~Session();


//all other methods
public:
	//basic methods(init, run, destroy..)
	//other methods
	void RecvData(char* buff, ssize_t data_size, Packet** packet);
	//getters
	const uint32_t FD() const { return fd_; };
	//setters
	void SetFD(uint32_t fd) { fd_ = fd; };
	

//private constants
private:

//private methods	
private:


//data members
private:
	char recv_buff_[kMaxSessionRecvBuffSize];
	uint32_t fd_ = 0;
	ssize_t cur_buff_idx_ = 0;
	ssize_t recv_packet_size_ = 0;

};
//class Session
}; //namespace hack