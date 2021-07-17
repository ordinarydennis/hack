//Related header
#include "server_app.h"
#include "../network/network.h"
//C system headers
//#include <>
//C++ standard library headers
//#include <>
//other libraries' headers
//#include <>

namespace hack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ServerApp::ServerApp() {

	//네트워크 초기화 
	network = new hack::Network;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ServerApp::~ServerApp() {

	if (nullptr != network) {
		delete network;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServerApp::Init(Port port) {

	network->Init(port);

}

void ServerApp::AddHandler()
{
	//네트워크에 등록
	//network
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServerApp::Run() {

	network->Run();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServerApp::Destory() {

}

};
