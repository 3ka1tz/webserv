#pragma once

#include <map>
#include <string>

struct ServerConfig
{
    std::map<int, std::string> errorPages;

    ServerConfig();

    std::string getErrorPage(int code) const;
};
