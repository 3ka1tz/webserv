#include <iostream> // cerr, cout, endl

#include "../include/Cgi.hpp"
#include "../include/Request.hpp"
#include "../include/Response.hpp"

int main()
{
    std::string scriptPath = "www/cgi-bin/script.py";

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

        Response res = Cgi::handleCgi(req, scriptPath);

        std::cout << res.getMessageBody() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
