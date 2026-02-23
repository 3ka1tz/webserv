#include "../include/ConnectionHandler.hpp"

#include <sys/socket.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "../include/RequestLine.hpp"

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
        path = "./www/index.html";

    std::ifstream file(path.c_str());
    bool notFound = !file.is_open();

    if (notFound)
    {
        file.close();
        file.open("./www/error_pages/404.html");
    }

    std::string body((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    std::ostringstream response;
    if (notFound)
        response << "HTTP/1.1 404 Not Found\r\n";
    else
        response << "HTTP/1.1 200 OK\r\n";

    response << "Content-Length: " << body.size() << "\r\n"
                << "Content-Type: text/html\r\n"
                << "\r\n"
                << body;

    std::string respStr = response.str();

    send(client_fd, respStr.c_str(), respStr.size(), 0);

    close(client_fd);
}
