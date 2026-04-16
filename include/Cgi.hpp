#ifndef CGI_HPP
# define CGI_HPP

# include <vector>

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

#endif

// https://www.ibm.com/docs/es/netcoolomnibus/8.1.0?topic=scripts-environment-variables-in-cgi-script
