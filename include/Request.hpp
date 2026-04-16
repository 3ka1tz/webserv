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
        
        bool containsHeader(const std::string& name) const;
        std::string getHeaderValue(const std::string& name) const;

        const std::map<std::string, std::string>& getHeaders() const;

    private:
        std::string method;
        std::string uri;
        std::string path;
        std::string query;
        std::string body;

        std::map<std::string, std::string> headers; 
};

#endif
