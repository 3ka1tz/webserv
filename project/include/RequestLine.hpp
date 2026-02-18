#pragma once

#include <string>

struct RequestLine
{
    std::string method;
    std::string uri;
    std::string version;
};

RequestLine parseRequestLine(const std::string& line);
