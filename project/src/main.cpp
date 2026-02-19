#include "../include/ConnectionHandler.hpp"
#include "../include/ServerSocket.hpp"

#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        std::cerr << "Usage 1: " << argv[0] << '\n';
        std::cerr << "Usage 2: " << argv[0] << " [configuration file]\n";
        return 1;
    }

    std::string conf = (argc == 1) ? "../conf/default.conf" : argv[1];
    std::cout << "Using " << conf << " as configuration file.\n";

    //if (!isConfValid(conf))
        //return 1;

    int server_fd = createServerSocket(8080);
    ConnectionHandler handler;

    while (true)
    {
        int client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0)
        {
            perror("accept");
            continue;
        }

        handler.handle(client_fd);
    }

    close(server_fd);
}
