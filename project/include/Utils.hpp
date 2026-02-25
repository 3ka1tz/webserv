#pragma once

#include <string>

bool fileExists(const std::string& path);
std::string getParentDirectory(const std::string& path);
bool havePermissions(const std::string& path);
