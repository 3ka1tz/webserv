#include "../include/HttpResponse.hpp"

#include <sstream>

HttpResponse::HttpResponse() : httpVersion("HTTP/1.1"), statusCode(200)
{
    httpHeaders["Content-Type"] = "text/html";
    httpHeaders["Connection"] = "close";
}

HttpResponse::HttpResponse(const HttpResponse& other) : httpVersion(other.httpVersion), statusCode(other.statusCode), httpHeaders(other.httpHeaders), messageBody(other.messageBody) {}

HttpResponse& HttpResponse::operator=(const HttpResponse& other)
{
    if (this != &other)
    {
        statusCode = other.statusCode;
        httpHeaders = other.httpHeaders;
        messageBody = other.messageBody;
    }
    return *this;
}

HttpResponse::~HttpResponse() {}

void HttpResponse::setStatusCode(int statusCode)
{
    this->statusCode = statusCode;
}

void HttpResponse::setHttpHeader(const std::string& key, const std::string& value)
{
    httpHeaders[key] = value;
}

void HttpResponse::setMessageBody(const std::string& messageBody)
{
    this->messageBody = messageBody;

    std::ostringstream contentLength;
    contentLength << messageBody.size();
    setHttpHeader("Content-Length", contentLength.str());
}

std::string HttpResponse::serialize() const
{
    std::ostringstream responseStream;
    responseStream << httpVersion << " " << statusCode << " " << getReasonPhrase(statusCode) << "\r\n";

    std::map<std::string, std::string>::const_iterator it;
    for (it = httpHeaders.begin(); it != httpHeaders.end(); ++it)
        responseStream << it->first << ": " << it->second << "\r\n";

    responseStream << "\r\n" << messageBody;
    return responseStream.str();
}

HttpResponse HttpResponse::buildErrorPage(int statusCode)
{
    HttpResponse res;
    res.setStatusCode(statusCode);

    std::ostringstream errorPage;
    errorPage << "<html><body><h1>" << statusCode << " " << getReasonPhrase(statusCode) << "</h1></body></html>";
    res.setMessageBody(errorPage.str());

    return res;
}

const char* HttpResponse::getReasonPhrase(int statusCode)
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
