#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <cstddef>
# include <string>

class Config
{
    public:
        size_t getClientMaxBodySize() const;
        std::string getRoot() const;
        std::string getUploadPath() const;
        std::string getCgiExtension() const;
        bool isAutoindex() const;

        void setRoot(const std::string& root);
        void setCgiExtension(const std::string& cgiExtension);

        bool isCgi(const std::string& path) const;

    private:
        size_t clientMaxBodySize;
        std::string root;
        std::string uploadPath;
        std::string cgiExtension;
        bool autoindex;
};

#endif
