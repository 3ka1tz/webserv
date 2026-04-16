#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <cstddef>
# include <string>

struct ServerConfig {};

struct LocationConfig
{
    std::string root;
    std::string uploadPath;
    std::string cgiExtension;
    size_t clientMaxBodySize;
    bool autoindex;
    
    std::string getRoot() const;
    std::string getUploadPath() const;
    bool isCgi(const std::string& path) const;
    size_t getClientMaxBodySize() const;
    bool isAutoindexEnabled() const;
};

class Config
{
    public:


    private:
        ServerConfig serverConfig;
        LocationConfig locationConfig;
};

#endif
