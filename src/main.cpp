#include "../include/ConnectionHandler.hpp"
#include "../include/Server.hpp"

#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>
#include <string>

int main(int argc, char ** argv)
{
     if (argc > 2)
    {
        std::cerr << "Usage: " << argv[0] << " [configuration file]\n"
                  << "If no file is provided, ../conf/default.conf is used.\n";
        return 1;
    }

    std::string conf = argc == 1 ? "../conf/default.conf" : argv[1];
    /*if (!isConfValid(conf))
    {
        std::cerr << "Error: Configuration file \"" << conf << "\" is not valid.\n";
        return 1;
    }*/

    int server_fd = createServerSocket(8080);
    ConnectionHandler handler;
    // aquí deberíamos implementar poll/epoll..., para poder gestionar múltiples solicitudes
    // estaría más limpio si sacamos este loop del main y lo convertimos en una función
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
