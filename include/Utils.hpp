#ifndef UTILS_HPP
# define UTILS_HPP

# include <string>

std::string fileToString(const std::string& path);
std::string getFilename(const std::string& path);
std::string getExtension(const std::string& path);

#endif
