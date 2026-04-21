#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <map> // map
# include <string> // string

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
        void setBody(const std::string& messageBody);

        bool containsHeader(const std::string& key) const;
        std::string getHeader(const std::string& key) const;
        const std::map<std::string, std::string>& getHeaders() const;
        void setHeader(const std::string& key, const std::string& value);

    private:
        std::string method;
        std::string uri;
        std::string path;
        std::string query;
        std::map<std::string, std::string> headers;
        std::string body;
};

#endif // REQUEST_HPP

// https://en.wikipedia.org/wiki/HTTP#Request
