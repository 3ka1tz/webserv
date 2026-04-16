#ifndef METHODS_HPP
# define METHODS_HPP

#include "Config.hpp"
#include "Request.hpp"
#include "Response.hpp"

class Methods
{
    public:
        Methods(const Request& req, const LocationConfig& loc);
        Methods(const Methods& other);
        Methods& operator=(const Methods& other);
        ~Methods();

        Response handleMethod();

    private:
        Request req;
        LocationConfig loc;

        Response handleGet();
        Response handlePost();
        Response handleDelete();

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
