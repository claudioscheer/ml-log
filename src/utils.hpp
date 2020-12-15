#ifndef ML_LOG_UTILS
#define ML_LOG_UTILS

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace ml_log {

struct Config {
    std::string applicationName;
    std::string redisHost;
    int redisPort;
    int redisDatabaseIndex;
};

Config loadConfig() {
    // TODO: Cache the file loaded. Avoid parsing the file every time this
    // function is called.
    //
    std::filesystem::path filePath = __FILE__;
    filePath = filePath.remove_filename();
    for (int i = 0; i < 4; i++) {
        filePath = filePath.parent_path();
    }
    filePath /= "ml-log.conf";

    Config config;
    std::fstream fileStream;
    fileStream.open(filePath);

    std::string line;
    while (std::getline(fileStream, line)) {
        std::istringstream lineStream(line);
        std::string key;
        if (std::getline(lineStream, key, '=')) {
            std::string value;
            if (std::getline(lineStream, value)) {
                if (key == "applicationName") {
                    config.applicationName = value;
                } else if (key == "redisHost") {
                    config.redisHost = value;
                } else if (key == "redisPort") {
                    config.redisPort = std::stoi(value);
                } else if (key == "redisDatabaseIndex") {
                    config.redisDatabaseIndex = std::stoi(value);
                }
            }
        }
    }

    return config;
}

} // namespace ml_log

#endif
