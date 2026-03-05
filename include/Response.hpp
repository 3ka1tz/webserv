#pragma once

#include <string>

struct Response
{
    std::string body;
    int status_code;
};

std::string getMimeType(const std::string& path);
std::string buildHttpResponse(const Response& res);
void loadErrorPage(Response& res);
