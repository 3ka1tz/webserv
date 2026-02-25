#include "../include/Delete.hpp"

#include <unistd.h>

#include <cstdio>
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

bool isDeletable(const std::string& path)
{
    std::string dir = getParentDirectory(path);

    return access(dir.c_str(), W_OK | X_OK) == 0;
}

void handleDELETE(const Request& req, Response& res)
{
    std::string path = req.uri;

    if (!fileExists(path))
    {
        res.status = 404;
        return;
    }

    if (!isDeletable(path))
    {
        res.status = 403;
        return;
    }

    std::remove(path.c_str());
    res.status = 204;
}
