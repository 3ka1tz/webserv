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

std::string decodeUrl(const std::string& url)
{
    size_t urlSize = url.size();
    std::string result;
    result.reserve(urlSize);

    for (size_t i = 0; i < urlSize; ++i)
    {
        if (url[i] == '%' && (i + 2) < urlSize && 
            std::isxdigit(static_cast<unsigned char>(url[i + 1])) && 
            std::isxdigit(static_cast<unsigned char>(url[i + 2])))
        {
            std::string hex = url.substr(i + 1, 2);
            char c = static_cast<char>(std::strtol(hex.c_str(), NULL, 16));
            result += c;
            i += 2;
        }
        else
        {
            result += url[i];
        }
    }
    return (result);
}
