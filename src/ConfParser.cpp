#include <sstream>

#include "../include/Tokenizer.hpp"
#include "../include/Utils.hpp"

bool isConfValid(const char* conf)
{
    if (!conf)
        return false;

    std::istringstream iss(conf);
    std::string token;

    while (iss >> token)
    {
        if (token.empty())
            return 0;
    }

    return true;
}

bool parseServerBlock(const std::string& conf_file_content)
{
    std::string token = getNextToken();
    if (token != "server")
        return false;

    token = getNextToken();
    if (token != "{")
        return false;

    while (true)
    {
        token = getNextToken();

        if (token.empty())
            return false;

        if (token == "}")
            break;
    }
}

bool parseConf(std::ifstream& conf_file)
{
    std::string conf_file_content = fileToString(conf_file);
    parseServerBlock(conf_file_content);
}
