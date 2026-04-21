#include "../include/Request.hpp"

/* Orthodox Canonical Class Form */

const std::string& Request::getMethod() const { return method; }
const std::string& Request::getUri() const { return uri; }
const std::string& Request::getPath() const { return path; }
const std::string& Request::getQuery() const { return query; }
const std::string& Request::getMessageBody() const { return messageBody; }

void Request::setMethod(const std::string& method) { this->method = method; }
void Request::setUri(const std::string& uri) { this->uri = uri; }
void Request::setPath(const std::string& path) { this->path = path; }
void Request::setQuery(const std::string& query) { this->query = query; }
void Request::setMessageBody(const std::string& messageBody) { this->messageBody = messageBody; }

bool Request::containsHeader(const std::string& name) const
{
    return httpHeaders.find(name) != httpHeaders.end();
}

std::string Request::getHttpHeader(const std::string& name) const
{
    std::map<std::string, std::string>::const_iterator it = headers.find(name);

    if (it != headers.end())
        return it->second;

    return "";
}

const std::map<std::string, std::string>& Request::getHeaders() const
{
    return httpHeaders;
}
