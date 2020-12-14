#include <filesystem>
#include <iostream>
#include <map>
#include <string>

namespace ml_log {

std::map<std::string, std::string> loadConfig() {
    std::map<std::string, std::string> configs;

    std::filesystem::path filePath = __FILE__;
    // TODO: Search for a config file into build directory.
    std::cout << filePath.parent_path() << std::endl;

    return configs;
}

} // namespace ml_log
