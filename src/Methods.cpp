#include "../include/Methods.hpp"

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

bool havePermissions(const std::string& path)
{
    std::string dir = getParentDirectory(path);

    return access(dir.c_str(), W_OK | X_OK) == 0;
}

void handleGET(const Request& req, Response& res)
{
    std::string path = req.uri;

    if (path == "/")
        path = "./www/index.html";

    std::ifstream file(path.c_str());
    if (!file.is_open())
    {
        res.status_code = 404;
        //res.body = loadFile("./www/error_pages/404.html");
        return;
    }

    res.status_code = 200;
    //res.body = loadFile(path);
}

void handlePOST(const Request& req, Response& res)
{
    std::string path = req.uri;

    if (fileExists(path))
    {
        res.status_code = 409;
        return;
    }

    if (!havePermissions(path))
    {
        res.status_code = 403;
        return;
    }

    std::ofstream out(path.c_str());
    if (!out)
    {
        res.status_code = 500;
        return;
    }

    out << req.body;
    out.close();

    res.status_code = 201;
}

void handleDELETE(const Request& req, Response& res)
{
    std::string path = req.uri;

    if (!fileExists(path))
    {
        res.status_code = 404;
        return;
    }

    if (!havePermissions(path))
    {
        res.status_code = 403;
        return;
    }

    std::remove(path.c_str());
    res.status_code = 204;
}
