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
        req.setHeader("Host", "localhost");
        req.setHeader("Content-Type", "text/plain");
        req.setHeader("Content-Length", "10");
        req.setBody("Testing...");

        Response res = methods.handleMethod(req);

        std::cout << res.getbody() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}
