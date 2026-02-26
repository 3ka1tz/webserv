#pragma once

#include <string>

struct Response
{
    std::string body;
    int status_code;
};

std::string buildHttpResponse(const Response& res);
void loadErrorPage(Response& res);
