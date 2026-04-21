#ifndef CGI_HPP
# define CGI_HPP

# include <sys/types.h> // pid_t

# include <map> // map
# include <string> // string
# include <vector> // vector

# include "Request.hpp"
# include "Response.hpp"

class Cgi
{
    public:
        ~Cgi();

        static Response handleCgi(const Request& req, const std::string& scriptPath);

    private:
        Cgi();
        Cgi(const Cgi& other);
        Cgi& operator=(const Cgi& other);

        static std::vector<std::string> buildEnv(const Request& req, const std::string& scriptPath);
        static void appendHttpHeadersToEnv(const std::map<std::string, std::string>& headers, std::vector<std::string>& env);
        static pid_t spawnChild(int inPipe[2], int outPipe[2], const std::vector<std::string>& env, const std::string& scriptPath);
        static void createPipes(int inPipe[2], int outPipe[2]);
        static std::string getInterpreter(const std::string& scriptPath);
        static void writeBodyToChild(int writeFd, const Request& req);
        static std::string readChildOutput(int readFd);
        static Response parseCgiOutput(const std::string& raw);
};

#endif // CGI_HPP

// https://en.wikipedia.org/wiki/Common_Gateway_Interface
// https://www.ibm.com/docs/en/i/7.6.0?topic=functionality-cgi
// https://www.ibm.com/docs/en/netcoolomnibus/8.1.0?topic=tools-creating-registering-cgi-scripts
