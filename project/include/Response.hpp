#pragma once

#include <string>

struct Response
{
    std::string body;
    int status_code;
};

void loadErrorPage(Response& res);
