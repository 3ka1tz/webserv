#ifndef METHODS_HPP
# define METHODS_HPP

#include "Config.hpp"
#include "Request.hpp"
#include "Response.hpp"

class Methods
{
    public:
        Methods(const Config& conf);
        Methods(const Methods& other);
        Methods& operator=(const Methods& other);
        ~Methods();

        Response handleMethod(const Request& req);

    private:
        Config conf;

        Response handleGet(const Request& req);
        Response handlePost(const Request& req);
        Response handleDelete(const Request& req);

        std::string resolvePath(const std::string& uri) const;
        Response redirectTo(const std::string& newLocation);
};

bool exists(const std::string& path);
bool isDirectory(const std::string& path);
std::string fileToString(const std::string& path);
std::string getMimeType(const std::string& path);
std::string buildDirectoryListing(const std::string& dirPath);

#endif

// https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods
