#include "../include/Utils.hpp"

#include <sstream>

std::string fileToString(std::ifstream& file)
{
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
