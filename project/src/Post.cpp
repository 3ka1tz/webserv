#include "../include/Methods.hpp"
#include "../include/Utils.hpp"

#include <fstream>

void handlePOST(const Request& req, Response& res)
{
    std::string path = req.uri;

    if (fileExists(path))
    {
        res.status = 409;
        return;
    }

    if (!havePermissions(path))
    {
        res.status = 403;
        return;
    }

    std::ofstream out(path.c_str());
    if (!out)
    {
        res.status = 500;
        return;
    }

    out << req.body;
    out.close();

    res.status = 201;
}
