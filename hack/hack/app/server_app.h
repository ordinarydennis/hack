#pragma once

//Related header(class.h, class.cpp)
//#include <>

//C system headers
//#include <>

//C++ standard library headers
//#include <>
//other libraries' headers
//#include <>

//your project's headers.
#include "../headers/common_headers.h"
#include "../define/types_define.h"
#include "../network/network.h"

namespace hack {

class Network;

class ServerApp {
	//types.. (typdef, using nest stucts and classes)
public:
	

	//constants
public:


	//factory functions, constructors and assignment operators, destructor
public:
	//constructors/destructor
	ServerApp();

	~ServerApp();


	//all other methods
	void Init(Port port);

	void Run();

	void Destory();

	void AddHandler(PacketId packet_id, Network::handler h);


public:
	//getters

	//setters

	//data members



private:
	uint32_t		count_of_processor_ = 0;

	hack::Network*	network_ = nullptr;


};

};
