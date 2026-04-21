#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <cstddef> // size_t
# include <string> // string

class Config
{
    public:
        std::string getRoot() const;
        std::string getUploadPath() const;
        bool isCgi(const std::string& path) const;
        size_t getClientMaxBodySize() const;
        bool isAutoindexEnabled() const;

    private:
        std::string root;
        std::string uploadPath;
        std::string cgiExtension;
        size_t clientMaxBodySize;
        bool autoindex;
};

#endif // CONFIG_HPP
