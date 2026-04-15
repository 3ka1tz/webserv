#ifndef METHOD_HANDLER_HPP
# define METHOD_HANDLER_HPP

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "ServerConfig.hpp"

class MethodHandler
{
    public:
        MethodHandler(const HttpRequest& req, const LocationConfig& loc);
        MethodHandler(const MethodHandler& other);
        MethodHandler& operator=(const MethodHandler& other);
        ~MethodHandler();

        HttpResponse handleMethod();

    private:
        HttpRequest req;
        LocationConfig loc;

        HttpResponse handleGet();
        HttpResponse handlePost();
        HttpResponse handleDelete();

        std::string resolvePath(const std::string& uri) const;
        HttpResponse redirectTo(const std::string& newLocation);
};

bool exists(const std::string& path);
bool isDirectory(const std::string& path);
std::string fileToString(const std::string& path);
std::string getMimeType(const std::string& path);
std::string buildDirectoryListing(const std::string& dirPath);

#endif

// https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods
