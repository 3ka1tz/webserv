#include "../include/Request.hpp"

bool Request::containsHeader(const std::string& name) const
{
    return httpHeaders.find(name) != httpHeaders.end();
}

std::string Request::getHeaderValue(const std::string& name) const
{
    std::map<std::string, std::string>::const_iterator it = headers.find(name);

    if (it != headers.end())
        return it->second;

    return "";
}

const std::map<std::string, std::string>& Request::getHeaders() const
{
    return httpHeaders;
}
