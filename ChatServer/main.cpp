#include <iostream>
#include <string>

#include "ChatServer.h"
#include "Define.h"

int main()
{
	ChatServer server;
	server.Init(MAX_IO_WORKER_THREAD);

	server.BindandListen(SERVER_PORT);
	server.Run(MAX_USER_COUNT);

	std::cout << "press any key to exit...";
	while (true)
	{
		std::string cmd;
		std::getline(std::cin, cmd);

		if (cmd == "quit")
		{
			break;
		}
	}

	server.End();
	return 0;
}