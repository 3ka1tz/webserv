#ifndef HTTP_REQUEST_HPP
# define HTTP_REQUEST_HPP

# include <string>

class HttpRequest
{
    public:
        HttpRequest();
        HttpRequest(const HttpRequest& other);
        HttpRequest& operator=(const HttpRequest& other);
        ~HttpRequest();

        std::string getMethod() const;
        std::string getBody() const;
        std::string getQuery() const;
        std::string getPath() const;

    private:
        std::string method;
        std::string body;
        std::string query;
        std::string path;
};

#endif
