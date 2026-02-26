#include "../include/Response.hpp"

#include <fstream>
#include <sstream>
#include <string>

std::string buildHttpResponse(const Response& res)
{
    std::ostringstream oss;

    oss << "HTTP/1.1 " << res.status_code << "\r\n"
        << "Content-Length: " << res.body.size() << "\r\n"
        << "Content-Type: text/html\r\n" 
        << "\r\n"
        << res.body;

    return oss.str();
}

std::string intToString(const int status_code)
{
    std::ostringstream oss;
    oss << status_code;
    return oss.str();
}

void loadErrorPage(Response& res)
{
    std::string path = "./www/error_pages/" + intToString(res.status_code) + ".html";

    std::ifstream file(path.c_str());
    if (!file)
    {
        res.body = "<h1>Error " + intToString(res.status_code) + "</h1>";
        return;
    }

    std::stringstream buf;
    buf << file.rdbuf();
    res.body = buf.str();
}
