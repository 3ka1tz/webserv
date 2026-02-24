#pragma once

#include <string>

struct Request
{
    std::string method;
    std::string uri;
    std::string version;
};

Request parseRequestLine(const std::string& line);
