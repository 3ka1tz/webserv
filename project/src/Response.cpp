#include "../include/Response.hpp"

#include <fstream>
#include <sstream>
#include <string>

std::string intToString(int status_code)
{
    std::ostringstream oss;
    oss << status_code;
    return oss.str();
}

void loadErrorPage(Response& res)
{
    std::string path = "./www/error_pages/" + intToString(res.status_code) + ".html";

    std::ifstream file(path.c_str());
    if (!file)
    {
        res.body = "<h1>Error " + intToString(res.status_code) + "<h1>";
        return;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    res.body = buffer.str();
}
