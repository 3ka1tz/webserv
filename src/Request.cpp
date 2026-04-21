#include "../include/Request.hpp"

Request::Request() {}
Request::~Request() {}

const std::string& Request::getMethod() const { return method; }
const std::string& Request::getUri() const { return uri; }
const std::string& Request::getPath() const { return path; }
const std::string& Request::getQuery() const { return query; }
const std::string& Request::getBody() const { return body; }

void Request::setMethod(const std::string& method) { this->method = method; }
void Request::setUri(const std::string& uri) { this->uri = uri; }
void Request::setPath(const std::string& path) { this->path = path; }
void Request::setQuery(const std::string& query) { this->query = query; }
void Request::setBody(const std::string& body) { this->body = body; }

bool Request::containsHeader(const std::string& key) const
{
    return headers.find(key) != headers.end();
}

std::string Request::getHeader(const std::string& key) const
{
    std::map<std::string, std::string>::const_iterator it = headers.find(key);

    if (it != headers.end())
        return it->second;

    return "";
}

const std::map<std::string, std::string>& Request::getHeaders() const
{
    return headers;
}

void Request::setHeader(const std::string& key, const std::string& value)
{
    headers[key] = value;
}
