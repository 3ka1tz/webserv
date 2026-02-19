#include "../include/ConnectionHandler.hpp"

#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

#include "../include/RequestLine.hpp"

/*
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
*/

void ConnectionHandler::handle(int client_fd)
{
    char buffer[4096];

    int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes <= 0)
    {
        close(client_fd);
        return;
    }

    buffer[bytes] = '\0';

    std::string request(buffer);

    std::string firstLine = request.substr(0, request.find("\r\n"));

    RequestLine req = parseRequestLine(firstLine);

    std::string path = req.uri;
    if (path == "/")
        path = "/index.html";

    std::cout << "Requested path: " << path << std::endl;

    std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: 2\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n"
        "OK";

    send(client_fd, response.c_str(), response.size(), 0);

    close(client_fd);
}
