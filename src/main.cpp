#include <iostream> // cerr, cout, endl

#include "../include/Cgi.hpp"
#include "../include/Request.hpp"
#include "../include/Response.hpp"

int main()
{
    try
    {
        Request req;

        req.setMethod("GET");
        req.setPath("/cgi-bin/script.py");
        req.setQuery("user=admin");
        req.setHeader("Host", "localhost");
        req.setHeader("Content-Type", "text/plain");
        req.setHeader("Content-Length", "22");
        req.setBody("Testing GET method...");

        std::string scriptPath = "www/cgi-bin/script.py";

        Response res = Cgi::handleCgi(req, scriptPath);

        std::cout << "CGI output:" << std::endl;
        std::cout << "Status: " << res.getStatusCode() << std::endl;
        std::cout << "Body: " << res.getMessageBody() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
