#include "../include/Response.hpp"

#include <sstream>

Response::Response() : httpVersion("HTTP/1.1"), statusCode(200), reasonPhrase("OK") {}

Response::~Response() {}

// =================================================================================================

int Response::getStatusCode() const { return (statusCode); }

void Response::setStatusCode(int statusCode) { this->statusCode = statusCode; }

const std::string& Response::getReasonPhrase(int statusCode) const
{
    static std::map<int, std::string> reasonPhrases;

    if (reasonPhrases.empty())
    {
        reasonPhrases[200] = "OK";
        reasonPhrases[201] = "Created";
        reasonPhrases[204] = "No Content";
        reasonPhrases[301] = "Moved Permanently";
        reasonPhrases[400] = "Bad Request";
        reasonPhrases[403] = "Forbidden";
        reasonPhrases[404] = "Not Found";
        reasonPhrases[405] = "Method Not Allowed";
        reasonPhrases[413] = "Content Too Large";
        reasonPhrases[500] = "Internal Server Error";
        reasonPhrases[501] = "Not Implemented";
        reasonPhrases[505] = "HTTP Version Not Supported";
    }

    std::map<int, std::string>::const_iterator it = reasonPhrases.find(statusCode);
    if (it != reasonPhrases.end())
        return (it->second);

    static const std::string unknownStatus = "Unknown Status";
    return (unknownStatus);
}

void Response::setReasonPhrase(int statusCode) { this->reasonPhrase = getReasonPhrase(statusCode); }

const std::string& Response::getHeaderValue(const std::string& key) const
{
    std::map<std::string, std::string>::const_iterator it = headers.find(key);

    if (it != headers.end())
        return it->second;

    static const std::string emptyString = "";
    return emptyString;
}

void Response::setHeaderValue(const std::string& key, const std::string& value) { headers[key] = value; }

const std::string& Response::getBody() const { return (body); }

void Response::setBody(const std::string& body)
{
    this->body = body;

    std::ostringstream contentLength;
    contentLength << body.size();
    setHeaderValue("Content-Length", contentLength.str());
}

// =================================================================================================

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
    errorPage << "<html><body><h1>" << statusCode << " " << res.getReasonPhrase(statusCode) << "</h1></body></html>";
    res.setBody(errorPage.str());

    return res;
}
