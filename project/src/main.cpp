#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        std::cerr << "Usage: " << argv[0] << " [configuration file]\n"
                  << "If no file is provided, ../conf/default.conf is used.\n";
        return 1;
    }

    std::string conf = argc == 1 ? "../conf/default.conf" : argv[1];
    if (!isConfValid(conf))
        return 1;

    
}
