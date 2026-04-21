#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <cstddef> // size_t
# include <string> // string

class Config
{
    public:
        size_t getClientMaxBodySize() const;
        std::string getRoot() const;
        std::string getUploadPath() const;
        std::string getCgiExtension() const;
        bool isAutoindex() const;

    private:
        size_t clientMaxBodySize;
        std::string root;
        std::string uploadPath;
        std::string cgiExtension;
        bool autoindex;
};

#endif // CONFIG_HPP
