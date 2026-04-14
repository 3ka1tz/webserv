#include "../include/Utils.hpp"

#include <cctype>
#include <cstddef>
#include <fstream>
#include <sstream>

std::string getExtension(const std::string& path)
{
    size_t dot_pos = path.rfind('.');
    if (dot_pos == std::string::npos)
        return "";

    std::string ext = path.substr(dot_pos);

    for (size_t i = 0; i < ext.size(); ++i)
        ext[i] = std::tolower(ext[i]);

    return ext;
}

std::string fileToString(const std::string& path)
{
    std::ifstream file(path.c_str());
    if (!file.is_open())
        throw std::runtime_error("Failed to open file");

    std::ostringstream oss;
    oss << file.rdbuf();
    return oss.str();
}
