#include <string>
#include <sstream>

struct RequestLine
{
    std::string method;
    std::string uri;
    std::string version;
};

RequestLine parseRequestLine(const std::string& line)
{
    std::istringstream iss(line);
    RequestLine req;

    iss >> req.method >> req.uri >> req.version;
    return req;
}
