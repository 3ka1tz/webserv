#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <map>
# include <string>

class Response
{
    public:
        Response();
        ~Response();

        int getStatusCode() const;
        void setStatusCode(int statusCode);

        const std::string& getReasonPhrase(int statusCode) const;
        void setReasonPhrase(int statusCode);

        const std::string& getHeaderValue(const std::string& key) const;
        void setHeaderValue(const std::string& key, const std::string& value);

        const std::string& getBody() const;
        void setBody(const std::string& body);

        std::string serialize() const;

        static Response buildErrorPage(int statusCode);

    private:
        const std::string httpVersion;
        int statusCode;
        std::string reasonPhrase;
        std::map<std::string, std::string> headers;
        std::string body;
};

#endif

// https://en.wikipedia.org/wiki/HTTP#Response
// https://www.ibm.com/docs/en/cics-ts/6.x?topic=protocol-http-responses
