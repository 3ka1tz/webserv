#ifndef CGI_HANDLER_HPP
# define CGI_HANDLER_HPP

# include "HttpRequest.hpp"
# include "HttpResponse.hpp"
# include "ServerConfig.hpp"

class CgiHandler
{
    public:
        CgiHandler(const HttpRequest& req, const LocationConfig& loc);
        CgiHandler(const CgiHandler& other);
        CgiHandler& operator=(const CgiHandler& other);
        ~CgiHandler();

        HttpResponse handleCgi(const HttpRequest& req, const std::string& scriptPath);

    private:
        std::vector<std::string> buildEnv(const HttpRequest& req, const std::string& scriptPath);
        std::vector<const char*> buildArgs(const std::string& scriptPath);
        void createPipes(int inPipe[2], int outPipe[2]);
        pid_t spawnChild(int inPipe[2], int outPipe[2], const std::vector<std::string>& env, const std::vector<const char*>& args);
        void writeBodyToChild(int writeFd, const HttpRequest& req);
        std::string readChildOutput(int readFd);
        HttpResponse parseCgiOutput(const std::string& raw);

        const char* PYTHON_INTERPRETER;
};

#endif

// https://www.ibm.com/docs/es/netcoolomnibus/8.1.0?topic=scripts-environment-variables-in-cgi-script
