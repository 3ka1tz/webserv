#ifndef HTTP_REQUEST_HPP
# define HTTP_REQUEST_HPP

# include <string>
# include <map>

class HttpRequest
{
    public:
        HttpRequest();
        HttpRequest(const HttpRequest& other);
        HttpRequest& operator=(const HttpRequest& other);
        ~HttpRequest();

        const std::string& getMethod() const;
        const std::string& getPath() const;
        const std::string& getQuery() const;
        const std::string& getBody() const;
        
        bool containsHeader(const std::string& name) const;
        std::string getHeaderValue(const std::string& name) const;

        const std::map<std::string, std::string>& getHeaders() const;

    private:
        std::string method;
        std::string path;
        std::string query;
        std::string body;

        std::map<std::string, std::string> headers; 
};

#endif
