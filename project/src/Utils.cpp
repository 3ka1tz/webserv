#include "../include/Utils.hpp"

#include <fstream>

bool fileExists(const std::string& path)
{
    std::ifstream file(path.c_str());

    return file.good();
}

std::string getParentDirectory(const std::string& path)
{
    std::string::size_type pos = path.find_last_of('/');

    if (pos == std::string::npos)
        return ".";

    if (pos == 0)
        return "/";

    return path.substr(0, pos);
}
