#include "../include/Request.hpp"
#include "../include/Response.hpp"
#include "../include/Utils.hpp"

#include <unistd.h>

#include <cstdio>

bool isDeletable(const std::string& path)
{
    std::string dir = getParentDirectory(path);

    return access(dir.c_str(), W_OK | X_OK) == 0;
}

void DELETE(const Request& req, Response& res)
{
    std::string path = resolvePath(req.uri);

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

    remove(path.c_str());
    res.status = 204;
}
