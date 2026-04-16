#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <map>
# include <string>

class Response
{
    public:
        Response();
        Response(const Response& other);
        Response& operator=(const Response& other);
        ~Response();

        void setStatusCode(int statusCode);
        void setHttpHeader(const std::string& key, const std::string& value);
        void setMessageBody(const std::string& messageBody);

        std::string serialize() const;

        static Response buildErrorPage(int statusCode);

    private:
        const std::string httpVersion;
        int statusCode;
        std::map<std::string, std::string> httpHeaders;
        std::string messageBody;

        static const char* getReasonPhrase(int statusCode);
};

#endif

// https://www.ibm.com/docs/en/cics-ts/6.x?topic=protocol-http-responses
// https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
