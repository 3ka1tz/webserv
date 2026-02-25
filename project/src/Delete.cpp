#include "../include/Methods.hpp"
#include "../include/Utils.hpp"

#include <cstdio>

void handleDELETE(const Request& req, Response& res)
{
    std::string path = req.uri;

    if (!fileExists(path))
    {
        res.status = 404;
        return;
    }

    if (!havePermissions(path))
    {
        res.status = 403;
        return;
    }

    std::remove(path.c_str());
    res.status = 204;
}
