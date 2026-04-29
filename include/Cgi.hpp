#ifndef CGI_HPP
# define CGI_HPP

# include <map>
# include <string>
# include <vector>

# include <sys/types.h>

# include "Request.hpp"
# include "Response.hpp"

class Cgi
{
    public:
        ~Cgi();

        static std::string getInterpreter(const std::string& scriptPath);
        static Response handleCgi(const Request& req, const std::string& scriptPath);

    private:
        Cgi();
        Cgi(const Cgi& other);
        Cgi& operator=(const Cgi& other);

        static void appendHeadersToEnv(const std::map<std::string, std::string>& headers, std::vector<std::string>& env);
        static std::vector<std::string> buildEnv(const Request& req, const std::string& scriptPath);
        static void createPipes(int inPipe[2], int outPipe[2]);
        static pid_t spawnChild(const std::string& scriptPath, const std::string& interpreterPath, const std::vector<std::string>& env, int inPipe[2], int outPipe[2]);
        static void writeBodyToChild(int writeFd, const Request& req);
        static std::string readChildOutput(int readFd);
        static Response parseCgiOutput(const std::string& raw);
};

#endif

// https://en.wikipedia.org/wiki/Common_Gateway_Interface
// https://www.ibm.com/docs/en/i/7.6.0?topic=functionality-cgi
// https://www.ibm.com/docs/en/netcoolomnibus/8.1.0?topic=tools-creating-registering-cgi-scripts
