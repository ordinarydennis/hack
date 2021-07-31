#pragma once

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
#include "../define/types_define.h"

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

public:
	//getters

	//setters

	//data members

protected:
	void AddHandler();


private:
	uint32_t		count_of_processor_ = 0;
	hack::Network*	network_ = nullptr;
	//std::unordered_map<>

};

};
