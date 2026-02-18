#include "../include/RequestLine.hpp"

#include <sstream>
#include <stdexcept>

RequestLine parseRequestLine(const std::string& line)
{
    std::istringstream iss(line);
    RequestLine req;

    if(!(iss >> req.method >> req.uri >> req.version))
        throw std::runtime_error("400");

    if (req.method != "GET" && req.method != "POST" && req.method != "DELETE")
        throw std::runtime_error("405");

    if (req.uri.empty() || req.uri[0] != '/')
        throw std::runtime_error("400");

    if (req.version != "HTTP/1.1")
        throw std::runtime_error("505");

    return req;
}
