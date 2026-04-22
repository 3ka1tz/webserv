#include "../include/Config.hpp"

#include "../include/Utils.hpp"

size_t Config::getClientMaxBodySize() const { return clientMaxBodySize; }
std::string Config::getRoot() const { return root; }
std::string Config::getUploadPath() const { return uploadPath; }
std::string Config::getCgiExtension() const { return cgiExtension; }
bool Config::isAutoindex() const { return autoindex; }

bool Config::isCgi(const std::string& path) const
{
    if (cgiExtension.empty())
        return false;

    return (getExtension(path) == cgiExtension);
}
