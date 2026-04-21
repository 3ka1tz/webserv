#include "../include/Config.hpp"

size_t Config::getClientMaxBodySize() const { return clientMaxBodySize; }
std::string Config::getRoot() const { return root; }
std::string Config::getUploadPath() const { return uploadPath; }
std::string Config::getCgiExtension() const { return cgiExtension; }
bool Config::isAutoindex() const { return autoindex; }
