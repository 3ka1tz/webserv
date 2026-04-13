#ifndef HTTP_RESPONSE_HPP
# define HTTP_RESPONSE_HPP

#include <map>
#include <string>

class HttpResponse
{
    public:
        HttpResponse();
        HttpResponse(const HttpResponse& other);
        HttpResponse& operator=(const HttpResponse& other);
        ~HttpResponse();

        void setStatusLine(const std::string& httpVersion, int statusCode);
        void setHttpHeader(const std::string& key, const std::string& value);
        void setMessageBody(const std::string& messageBody);

        std::string serialize() const;

        static HttpResponse buildErrorPage(int statusCode);

    private:
        std::string httpVersion;
        int statusCode;
        std::string reasonPhrase;
        std::map<std::string, std::string> httpHeaders;
        std::string messageBody;

        static std::string getReasonPhrase(int statusCode);
};

#endif

// https://www.ibm.com/docs/en/cics-ts/6.x?topic=protocol-http-responses
// https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
