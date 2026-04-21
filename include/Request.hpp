#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <map>
# include <string>

class Request
{
    public:
        Request();
        Request(const Request& other);
        Request& operator=(const Request& other);
        ~Request();

        const std::string& getMethod() const;
        const std::string& getUri() const;
        const std::string& getPath() const;
        const std::string& getQuery() const;
        const std::string& getMessageBody() const;

        void setMethod(const std::string& method);
        void setUri(const std::string& uri);
        void setPath(const std::string& path);
        void setQuery(const std::string& query);
        void setMessageBody(const std::string& messageBody);

        bool containsHeader(const std::string& name) const;
        std::string getHttpHeader(const std::string& name) const;
        const std::map<std::string, std::string>& getHeaders() const;

    private:
        std::string method;
        std::string uri;
        std::string path;
        std::string query;
        std::map<std::string, std::string> httpHeaders;
        std::string messageBody;

        std::map<std::string, std::string> headers; 
};

#endif

// https://en.wikipedia.org/wiki/HTTP#Request
