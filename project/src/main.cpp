#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        std::cerr << "Usage 1: " << argv[0] << '\n';
        std::cerr << "Usage 2: " << argv[0] << " [configuration file]\n";
        return 1;
    }

    std::string conf = (argc == 1) ? "../conf/default.conf" : argv[1];
    std::cout << "Using " << conf << " as configuration file.\n";

    //if (!isConfValid(conf))
        //return 1;
}
