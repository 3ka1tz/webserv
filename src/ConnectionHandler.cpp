#include "../include/ConnectionHandler.hpp"

#include <sys/socket.h>
#include <unistd.h>

#include "../include/Methods.hpp"
#include "../include/Request.hpp"
#include "../include/Response.hpp"

/*void handleRequest(const Request& req, Response& res)
{
    if (req.method == "GET")
        handleGET(req, res);
    else if (req.method == "POST")
        handlePOST(req, res);
    else if (req.method == "DELETE")
        handleDELETE(req, res);
    else
        res.status_code = 405;
}

void ConnectionHandler::handle(int client_fd)
{
    char buf[4096];
    ssize_t bytes = recv(client_fd, buf, sizeof(buf) - 1, 0);
    if (bytes <= 0)
    {
        close(client_fd);
        return;
    }
    buf[bytes] = '\0';

    std::string raw(buf);
    Request req = parseRequestLine(raw);

    Response res;

    handleRequest(req, res);
    if (res.status_code >= 400)
        loadErrorPage(res);

    std::string http = buildHttpResponse(res);

    send(client_fd, http.c_str(), http.size(), 0);

    close(client_fd);
}*/

// Esto de momento funciona, pero entiendo que sería mejor y más limpio hacerlo como el de arriba.
#include <fstream>
#include <iostream>
#include <sstream>
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

    Request req = parseRequestLine(firstLine);

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
