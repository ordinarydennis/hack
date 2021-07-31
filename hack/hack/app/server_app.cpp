//Related header
#include "server_app.h"
#include "../network/network.h"
//C system headers
#include <thread>
//C++ standard library headers
//#include <>
//other libraries' headers
//#include <>

namespace hack {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ServerApp::ServerApp() {

	//쓰레드 수 얻기
	count_of_processor_ = std::thread::hardware_concurrency();

	//네트워크 초기화 
	network_ = new hack::Network(count_of_processor_);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ServerApp::~ServerApp() {

	if (nullptr != network_) {
		delete network_;
	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServerApp::Init(Port port) {

	network_->Init(port);


}

void ServerApp::AddHandler()
{
	//네트워크에 등록
	//network_
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServerApp::Run() {

	network_->Run();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServerApp::Destory() {

}

};
