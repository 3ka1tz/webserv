#include "../include/Response.hpp"

#include <fstream>
#include <sstream>
#include <string>

bool endsWith(const std::string& str, const std::string& suffix)
{
    if (str.length() < suffix.length())
        return false;

    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

std::string getMimeType(const std::string& path)
{
    if (endsWith(path, ".html"))
        return "text/html";

    if (endsWith(path, ".ico"))
        return "image/x-icon";

    return "application/octet-stream";
}

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

    std::stringstream ss;
    ss << file.rdbuf();
    res.body = ss.str();
}
