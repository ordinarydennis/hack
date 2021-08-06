#include "chat_server.h"
#include <iostream>

#include "handlers.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChatServer::ChatServer() {


}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ChatServer::~ChatServer() {
	
}

void ChatServer::Init(hack::Port port)
{
	hack::Log("ChatServer::Init()");

	ServerApp::Init(port);

	AddHandler(21, HandlerReqLogin);

}





