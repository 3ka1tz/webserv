#include <iostream>

#include "../include/Methods.hpp"
#include "../include/Request.hpp"
#include "../include/Response.hpp"

int main()
{
    Config conf;
    conf.setRoot("./www"); 
    conf.setCgiExtension(".py");

    Methods methods(conf);

    try
    {
        Request req;
        req.setMethod("GET");
        req.setUri("/cgi-bin/script.py");
        req.setPath("/cgi-bin/script.py");
        req.setQuery("user=admin");
        req.setHeaderValue("Host", "localhost");
        req.setHeaderValue("Content-Type", "text/plain");
        req.setHeaderValue("Content-Length", "10");
        req.setBody("Testing...");

        Response res = methods.handleMethod(req);

        std::cout << res.getBody() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
