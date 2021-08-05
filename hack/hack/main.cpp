#include "chat_server/chat_server.h"

int main() {

	hack::Log("Start main()");

	ChatServer chatServer;

	chatServer.Init(11021);

	chatServer.Run();

	chatServer.Destory();

	return 0;
}
