#include "../include/Response.hpp"

#include <sstream>

Response::Response() : httpVersion("HTTP/1.1"), statusCode(200)
{
    headers["Content-Type"] = "text/html";
    headers["Connection"] = "close";
}

Response::Response(const Response& other) : httpVersion(other.httpVersion), statusCode(other.statusCode), headers(other.headers), body(other.body) {}

Response& Response::operator=(const Response& other)
{
    if (this != &other)
    {
        statusCode = other.statusCode;
        headers = other.headers;
        body = other.body;
    }
    return *this;
}

Response::~Response() {}

int Response::getStatusCode() const
{
    return statusCode;
}

const std::string Response::getHeaderValue(const std::string& key) const
{
    std::map<std::string, std::string>::const_iterator it = headers.find(key);

    if (it != headers.end())
        return it->second;

    return "";
}

const std::string& Response::getbody() const
{
    return body;
}

void Response::setStatusCode(int statusCode)
{
    this->statusCode = statusCode;
}

void Response::setHeader(const std::string& key, const std::string& value)
{
    headers[key] = value;
}

void Response::setBody(const std::string& body)
{
    this->body = body;

    std::ostringstream contentLength;
    contentLength << body.size();
    setHeader("Content-Length", contentLength.str());
}

std::string Response::serialize() const
{
    std::ostringstream responseStream;
    responseStream << httpVersion << " " << statusCode << " " << getReasonPhrase(statusCode) << "\r\n";

    std::map<std::string, std::string>::const_iterator it;
    for (it = headers.begin(); it != headers.end(); ++it)
        responseStream << it->first << ": " << it->second << "\r\n";

    responseStream << "\r\n" << body;
    return responseStream.str();
}

Response Response::buildErrorPage(int statusCode)
{
    Response res;
    res.setStatusCode(statusCode);

    std::ostringstream errorPage;
    errorPage << "<html><body><h1>" << statusCode << " " << getReasonPhrase(statusCode) << "</h1></body></html>";
    res.setBody(errorPage.str());

    return res;
}

const char* Response::getReasonPhrase(int statusCode)
{
    switch (statusCode)
    {
        case 200: return "OK";
        case 201: return "Created";
        case 202: return "Accepted";
        case 203: return "Non-Authoritative Information";
        case 204: return "No Content";
        case 205: return "Reset Content";
        case 300: return "Multiple Choices";
        case 301: return "Moved Permanently";
        case 302: return "Found";
        case 303: return "See Other";
        case 304: return "Not Modified";
        case 305: return "Use Proxy";
        case 400: return "Bad Request";
        case 401: return "Unauthorized";
        case 402: return "Payment Required";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 405: return "Method Not Allowed";
        case 413: return "Content Too Large";
        case 500: return "Internal Server Error";
        case 501: return "Not Implemented";
        case 502: return "Bad Gateway";
        case 503: return "Service Unavailable";
        case 504: return "Gateway Timeout";
        case 505: return "HTTP Version Not Supported";
        default: return "";
    }
}
