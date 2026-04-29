#include "../include/Methods.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../include/Cgi.hpp"
#include "../include/Utils.hpp"

Methods::Methods(const Config& conf) : conf(conf) {}

Methods::Methods(const Methods& other) : conf(other.conf) {}

Methods& Methods::operator=(const Methods& other)
{
    if (this != &other)
        conf = other.conf;
    return *this;
}

Methods::~Methods() {}

Response Methods::handleMethod(const Request& req)
{
    if (req.getMethod() == "GET")
        return handleGet(req);

    if (req.getMethod() == "POST")
        return handlePost(req);

    if (req.getMethod() == "DELETE")
        return handleDelete(req);

    return Response::buildErrorPage(405);
}

Response Methods::handleGet(const Request& req)
{
    std::string path = resolvePath(req.getUri());

    if (!exists(path))
        return Response::buildErrorPage(404);

    if (isDirectory(path))
    {
        std::string uri = req.getUri();
        if (!uri.empty() && uri[uri.length() - 1] != '/')
            return redirectTo(req.getUri() + "/");

        std::string index = path + "index.html";

        if (exists(index))
        {
            Response res;
            res.setStatusCode(200);
            res.setHeader("Content-Type", getMimeType(index));

            std::string content = fileToString(index);
            res.setBody(content);

            return res;
        }

        if (conf.isAutoindex())
        {
            Response res;
            res.setStatusCode(200);
            res.setHeader("Content-Type", "text/html");

            std::string listing = buildDirectoryListing(path);
            res.setBody(listing);

            return res;
        }

        return Response::buildErrorPage(403);
    }

    if (conf.isCgi(path))
        return Cgi::handleCgi(req, path);

    if (!Cgi::getInterpreter(path).empty())
        return Response::buildErrorPage(403);

    Response res;
    res.setStatusCode(200);
    res.setHeader("Content-Type", getMimeType(path));

    std::string content = fileToString(path);
    res.setBody(content);

    return res;
}

Response Methods::handlePost(const Request& req)
{
    if (req.getBody().size() > conf.getClientMaxBodySize())
        return Response::buildErrorPage(413);

    std::string path = resolvePath(req.getUri());

    if (!exists(path) && conf.getUploadPath().empty())
        return Response::buildErrorPage(404);

    if (conf.isCgi(path))
        return Cgi::handleCgi(req, path);

    if (!conf.getUploadPath().empty())
    {
        std::string uploadDir = conf.getUploadPath();
        if (!uploadDir.empty() && uploadDir[uploadDir.size() - 1] != '/')
            uploadDir += '/';

        std::string fullPath = uploadDir + getFilename(path);

        std::ofstream out(fullPath.c_str(), std::ios::binary);
        if (!out)
            return Response::buildErrorPage(500);

        out.write(req.getBody().data(), req.getBody().size());
        out.close();

        Response res;
        res.setStatusCode(201);
        res.setBody("<html><body><h1>File uploaded</h1></body></html>");

        return res;
    }

    return Response::buildErrorPage(405);
}

Response Methods::handleDelete(const Request& req)
{
    std::string path = resolvePath(req.getUri());

    if (!exists(path))
        return Response::buildErrorPage(404);

    if (isDirectory(path))
        return Response::buildErrorPage(403);

    if (std::remove(path.c_str()) != 0)
        return Response::buildErrorPage(500);

    Response res;
    res.setStatusCode(204);
    res.setBody("");

    return res;
}

std::string Methods::resolvePath(const std::string& uri) const
{
    std::string path = conf.getRoot();

    if (!path.empty() && path[path.size() - 1] == '/')
        path.erase(path.size() - 1);

    if (!uri.empty() && uri[0] == '/')
        path += uri;
    else
        path += '/' + uri;

    std::vector<std::string> parts;
    std::stringstream ss(path);
    std::string item;

    while (std::getline(ss, item, '/'))
    {
        if (item == "" || item == ".")
            continue;

        if (item == "..")
        {
            if (!parts.empty())
                parts.pop_back();

            continue;
        }

        parts.push_back(item);
    }

    std::string clean = "";

    for (size_t i = 0; i < parts.size(); ++i)
    {
        clean += parts[i];

        if (i + 1 < parts.size())
            clean += '/';
    }

    return clean;
}

Response Methods::redirectTo(const std::string& newLocation)
{
    Response res;
    res.setStatusCode(301);
    res.setHeader("Location", newLocation);

    std::string body = "<html><body><h1>301 Moved Permanently</h1></body></html>";
    res.setBody(body);

    return res;
}

bool exists(const std::string& path)
{
    struct stat s;
    return stat(path.c_str(), &s) == 0;
}

bool isDirectory(const std::string& path)
{
    struct stat s;
    return stat(path.c_str(), &s) == 0 && S_ISDIR(s.st_mode);
}

std::string getMimeType(const std::string& path)
{
    static std::map<std::string, std::string> mime_types;

    if (mime_types.empty())
    {
        mime_types[".css"]  = "text/css";
        mime_types[".html"] = "text/html";
        mime_types[".txt"]  = "text/plain";

        mime_types[".js"]   = "application/javascript";
        mime_types[".json"] = "application/json";
        mime_types[".pdf"]  = "application/pdf";
        mime_types[".xml"]  = "application/xml";
        mime_types[".zip"]  = "application/zip";

        mime_types[".gif"]  = "image/gif";
        mime_types[".ico"]  = "image/x-icon";
        mime_types[".jpg"]  = "image/jpeg";
        mime_types[".jpeg"] = "image/jpeg";
        mime_types[".png"]  = "image/png";
        mime_types[".svg"]  = "image/svg+xml";

        mime_types[".mp3"]  = "audio/mpeg";
        mime_types[".mp4"]  = "video/mp4";

        mime_types[".woff"]  = "font/woff";
        mime_types[".woff2"] = "font/woff2";
        mime_types[".otf"]   = "font/otf";
        mime_types[".ttf"]   = "font/ttf";
    }

    std::string ext = getExtension(path);

    if (mime_types.count(ext))
        return mime_types[ext];

    return "application/octet-stream";
}

std::vector<std::string> listDirectories(const std::string& dirPath)
{
    std::vector<std::string> entries;

    DIR* dir = opendir(dirPath.c_str());
    if (!dir)
        return entries;

    struct dirent* entry;
    while ((entry = readdir(dir)))
    {
        std::string name = entry->d_name;

        if (name == "." || name == "..")
            continue;

        entries.push_back(name);
    }

    closedir(dir);

    std::sort(entries.begin(), entries.end());

    return entries;
}

std::string buildDirectoryListing(const std::string& dirPath)
{
    std::vector<std::string> entries = listDirectories(dirPath);

    std::string dirList = "<html><body><h1>Index of " + dirPath + "</h1><ul>";

    for (std::vector<std::string>::const_iterator it = entries.begin(); it != entries.end(); ++it)
    {
        const std::string& entry = *it;

        dirList += "<li><a href=\"" + entry + "\">" + entry + "</a></li>";
    }

    dirList += "</ul></body></html>";

    return dirList;
}
