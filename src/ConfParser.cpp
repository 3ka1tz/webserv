#include <sstream>

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
