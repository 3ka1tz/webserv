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
        const std::string& getBody() const;

        void setMethod(const std::string& method);
        void setUri(const std::string& uri);
        void setPath(const std::string& path);
        void setQuery(const std::string& query);
        void setBody(const std::string& body);

        bool containsHeader(const std::string& key) const;
        std::string getHeader(const std::string& key) const;
        const std::map<std::string, std::string>& getHeaders() const;
        void setHeaderValue(const std::string& key, const std::string& value);

    private:
        std::string method;
        std::string uri;
        std::string path;
        std::string query;
        std::map<std::string, std::string> headers;
        std::string body;
};

#endif

// https://en.wikipedia.org/wiki/HTTP#Request
