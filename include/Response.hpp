#pragma once

#include <string>

struct Response
{
    int status_code;
    std::string body;
    std::string path;
};

std::string getMimeType(const std::string& path);
std::string buildHttpResponse(const Response& res);
void loadErrorPage(Response& res);
