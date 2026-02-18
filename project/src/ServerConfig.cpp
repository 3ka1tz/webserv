#include "../include/ServerConfig.hpp"

ServerConfig::ServerConfig()
{
    errorPages[400] = "/error_pages/400.html";
    errorPages[403] = "/error_pages/403.html";
    errorPages[404] = "/error_pages/404.html";
    errorPages[405] = "/error_pages/405.html";
    errorPages[500] = "/error_pages/500.html";
    errorPages[505] = "/error_pages/505.html";
}

std::string ServerConfig::getErrorPage(int code) const
{
    std::map<int, std::string>::const_iterator it = errorPages.find(code);

    if (it == errorPages.end())
        return "";

    return it->second;
}
