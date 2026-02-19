#include "../include/ConnectionHandler.hpp"

#include <sys/socket.h>
#include <unistd.h>

#include <string>

void ConnectionHandler::handle(int client_fd)
{
    std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 13\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n"
        "Hello, World!";

    send(client_fd, response.c_str(), response.size(), 0);

    close(client_fd);
}
