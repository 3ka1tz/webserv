#pragma once

#include <string>

struct Request
{
    std::string method;
    std::string uri;
    std::string version;

    std::string body;
};

Request parseRequestLine(const std::string& requestLine);
