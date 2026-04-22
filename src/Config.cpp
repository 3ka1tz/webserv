#include "../include/Config.hpp"

#include "../include/Utils.hpp"

size_t Config::getClientMaxBodySize() const { return clientMaxBodySize; }
std::string Config::getRoot() const { return root; }
std::string Config::getUploadPath() const { return uploadPath; }
std::string Config::getCgiExtension() const { return cgiExtension; }
bool Config::isAutoindex() const { return autoindex; }

void Config::setRoot(const std::string& root) { this->root = root; }
void Config::setCgiExtension(const std::string& cgiExtension) { this->cgiExtension = cgiExtension; }

bool Config::isCgi(const std::string& path) const
{
    if (cgiExtension.empty())
        return false;

    return (getExtension(path) == cgiExtension);
}
