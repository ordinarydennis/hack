#include <cstdio>

#include "chat_server/chat_server.h"

int main() {

	ChatServer chatServer;

	chatServer.Init(11021);

	chatServer.Run();

	chatServer.Destory();

	return 0;
}
