#include "../include/CgiHandler.hpp"

#include <sys/wait.h>

#include <sstream>
#include <stdexcept>

#include "../include/Utils.hpp"

CgiHandler::~CgiHandler() {}

HttpResponse CgiHandler::handleCgi(const HttpRequest& req, const std::string& scriptPath)
{
    std::vector<std::string> env = buildEnv(req, scriptPath);

    int inPipe[2];
    int outPipe[2];
    createPipes(inPipe, outPipe);

    pid_t pid = spawnChild(inPipe, outPipe, env, scriptPath);

    writeBodyToChild(inPipe[1], req);

    std::string rawOutput = readChildOutput(outPipe[0]);

    int status;
    waitpid(pid, &status, 0);

    return parseCgiOutput(rawOutput);
}

std::vector<std::string> CgiHandler::buildEnv(const HttpRequest& req, const std::string& scriptPath)
{
    std::vector<std::string> env;

    env.push_back("GATEWAY_INTERFACE=CGI/1.1");
    env.push_back("SERVER_PROTOCOL=HTTP/1.1");

    env.push_back("REQUEST_METHOD=" + req.getMethod());
    env.push_back("QUERY_STRING=" + req.getQuery());

    env.push_back("SCRIPT_NAME=" + req.getPath());
    env.push_back("SCRIPT_FILENAME=" + scriptPath);

    // env.push_back("SERVER_NAME=" + req.getHost());
    // env.push_back("SERVER_PORT=" + req.getPort());

    // env.push_back("REMOTE_ADDR=" + req.getClientIP());

    if (req.containsHeader("Content-Type"))
        env.push_back("CONTENT_TYPE=" + req.getHeaderValue("Content-Type"));

    if (req.containsHeader("Content-Length"))
        env.push_back("CONTENT_LENGTH=" + req.getHeaderValue("Content-Length"));

    appendHttpHeadersToEnv(req.getHeaders(), env);

    env.push_back("REDIRECT_STATUS=200");

    return env;
}

void CgiHandler::appendHttpHeadersToEnv(const std::map<std::string, std::string>& headers, std::vector<std::string>& env)
{
    for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it)
    {
        std::string key = it->first;
        std::string value = it->second;

        for (size_t i = 0; i < key.size(); ++i)
        {
            if (key[i] == '-')
                key[i] = '_';
            else
                key[i] = std::toupper(key[i]);
        }

        env.push_back("HTTP_" + key + "=" + value);
    }
}

std::string CgiHandler::getInterpreter(const std::string& path)
{
    static std::map<std::string, std::string> interpreters;

    if (interpreters.empty())
    {
        interpreters[".sh"]  = "/bin/bash";
        interpreters[".pl"]  = "/usr/bin/perl";
        interpreters[".py"]  = "/usr/bin/python3";
        interpreters[".php"] = "/usr/bin/php-cgi";
    }

    std::string ext = getExtension(path);

    std::map<std::string, std::string>::const_iterator it = interpreters.find(ext);
    if (it != interpreters.end())
        return it->second;

    return "";
}

void CgiHandler::createPipes(int inPipe[2], int outPipe[2])
{
    if (pipe(inPipe) == -1)
        throw std::runtime_error("Failed to create input pipe");

    if (pipe(outPipe) == -1)
    {
        close(inPipe[0]);
        close(inPipe[1]);
        throw std::runtime_error("Failed to create output pipe");
    }
}

pid_t CgiHandler::spawnChild(int inPipe[2], int outPipe[2], const std::vector<std::string>& env, const std::string& scriptPath)
{
    pid_t pid = fork();
    if (pid < 0)
        throw std::runtime_error("Failed to fork for CGI");

    if (pid == 0)
    {
        dup2(inPipe[0], STDIN_FILENO);
        close(inPipe[0]);
        close(inPipe[1]);

        dup2(outPipe[1], STDOUT_FILENO);
        close(outPipe[0]);
        close(outPipe[1]);

        size_t slash = scriptPath.find_last_of('/');
        if (slash != std::string::npos)
        {
            std::string dir = scriptPath.substr(0, slash);
            chdir(dir.c_str());
        }

        std::string interp = getInterpreter(scriptPath);
        const char* interpreter = interp.c_str();

        std::vector<char*> argv;
        argv.reserve(3);
        argv.push_back(const_cast<char*>(interpreter));
        argv.push_back(const_cast<char*>(scriptPath.c_str()));
        argv.push_back(NULL);

        std::vector<char*> envp;
        for (size_t i = 0; i < env.size(); ++i)
            envp.push_back(const_cast<char*>(env[i].c_str()));
        envp.push_back(NULL);

        execve(interpreter, argv.data(), envp.data());

        perror("execve");
        exit(1);
    }

    close(inPipe[0]);
    close(outPipe[1]);

    return pid;
}

void CgiHandler::writeBodyToChild(int writeFd, const HttpRequest& req)
{
    if (req.getMethod() == "POST")
    {
        const std::string& body = req.getBody();
        size_t bodySize = body.size();
        size_t totalWritten = 0;

        while (totalWritten < bodySize)
        {
            ssize_t writtenNow = write(writeFd, body.c_str() + totalWritten, bodySize - totalWritten);

            if (writtenNow <= 0)
                break;

            totalWritten += writtenNow;
        }
    }

    close(writeFd);
}

std::string CgiHandler::readChildOutput(int readFd)
{
    std::string output;
    char buffer[4096];

    while (true)
    {
        ssize_t bytesRead = read(readFd, buffer, sizeof(buffer));

        if (bytesRead < 0)
            break;

        if (bytesRead == 0)
            break;

        output.append(buffer, bytesRead);
    }

    close(readFd);
    return output;
}

HttpResponse CgiHandler::parseCgiOutput(const std::string& raw)
{
    HttpResponse res;
    size_t pos = raw.find("\r\n\r\n");
    size_t sepLen = 4;

    if (pos == std::string::npos)
    {
        pos = raw.find("\n\n");
        sepLen = 2;
    }

    if (pos == std::string::npos)
    {
        res.setStatusCode(200);
        res.setMessageBody(raw);
        return res;
    }

    std::string headerPart = raw.substr(0, pos);
    std::string bodyPart = raw.substr(pos + sepLen);

    std::istringstream headerStream(headerPart);
    std::string line;
    bool statusSet = false;

    while (std::getline(headerStream, line))
    {
        if (!line.empty() && line[line.size() - 1] == '\r')
            line.erase(line.size() - 1);

        if (line.empty())
            continue;

        if (line.find("Status:") == 0)
        {
            int code = atoi(line.substr(7).c_str());
            res.setStatusCode(code);
            statusSet = true;
            continue;
        }

        size_t colon = line.find(':');
        if (colon != std::string::npos)
        {
            std::string key = line.substr(0, colon);
            std::string value = line.substr(colon + 1);

            while (!value.empty() && value[0] == ' ')
                value.erase(0, 1);

            res.setHttpHeader(key, value);
        }
    }

    if (!statusSet)
        res.setStatusCode(200);

    res.setMessageBody(bodyPart);
    return res;
}
