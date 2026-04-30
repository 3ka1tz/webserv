#include "../include/Utils.hpp"

#include <cctype>
#include <cstddef>
#include <fstream>
#include <sstream>

std::string fileToString(const std::string& path)
{
    std::ifstream file(path.c_str());
    if (!file)
        return ("");

    std::ostringstream oss;
    oss << file.rdbuf();
    return (oss.str());
}

std::string getFilename(const std::string& path)
{
    if (path.empty() || (path.length() - 1) == '/')
        return ("");

    size_t lastSlash = path.find_last_of('/');
    if (lastSlash == std::string::npos)
        return (path);

    return (path.substr(lastSlash + 1));
}

std::string getExtension(const std::string& path)
{
    std::string filename = getFilename(path);

    size_t dot_pos = filename.rfind('.');
    if (dot_pos == std::string::npos || dot_pos == 0)
        return ("");

    std::string ext = filename.substr(dot_pos);
    for (size_t i = 0; i < ext.size(); ++i)
        ext[i] = std::tolower(ext[i]);

    return (ext);
}
