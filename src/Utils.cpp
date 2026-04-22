#include "../include/Utils.hpp"

#include <cctype>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>

std::string getExtension(const std::string& path)
{
    std::string filename = getFilename(path);

    size_t dot_pos = filename.rfind('.');
    if (dot_pos == std::string::npos || dot_pos == 0)
        return "";

    std::string ext = filename.substr(dot_pos);
    for (size_t i = 0; i < ext.size(); ++i)
        ext[i] = std::tolower(static_cast<unsigned char>(ext[i]));

    return ext;
}

std::string getFilename(const std::string& path)
{
    std::string cleanPath = path;
    if (cleanPath.length() > 1 && cleanPath[cleanPath.length() - 1] == '/')
        cleanPath.erase(cleanPath.length() - 1);

    size_t lastSlash = cleanPath.find_last_of('/');
    if (lastSlash == std::string::npos)
        return cleanPath.empty() ? "default_upload" : cleanPath;

    std::string filename = cleanPath.substr(lastSlash + 1);
    if (filename.empty())
        return "default_upload";

    return filename;
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
