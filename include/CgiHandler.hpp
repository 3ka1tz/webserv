#ifndef CGI_HANDLER_HPP
# define CGI_HANDLER_HPP

# include <vector>

# include "HttpRequest.hpp"
# include "HttpResponse.hpp"

class CgiHandler
{
    public:
        ~CgiHandler();

        HttpResponse handleCgi(const HttpRequest& req, const std::string& scriptPath);

    private:
        CgiHandler();
        CgiHandler(const CgiHandler& other);
        CgiHandler& operator=(const CgiHandler& other);

        std::vector<std::string> buildEnv(const HttpRequest& req, const std::string& scriptPath);
        void appendHttpHeadersToEnv(const std::map<std::string, std::string>& headers, std::vector<std::string>& env);
        pid_t spawnChild(int inPipe[2], int outPipe[2], const std::vector<std::string>& env, const std::string& scriptPath);
        void createPipes(int inPipe[2], int outPipe[2]);
        std::string getInterpreter(const std::string& scriptPath);
        void writeBodyToChild(int writeFd, const HttpRequest& req);
        std::string readChildOutput(int readFd);
        HttpResponse parseCgiOutput(const std::string& raw);
};

#endif

// https://www.ibm.com/docs/es/netcoolomnibus/8.1.0?topic=scripts-environment-variables-in-cgi-script
